#include "BattleSystem.h"
#include <iostream>
#include "Creature.h"
#include "Type.h"
#include "DataManager.h"
#include "Player.h"

using namespace std;

// 전투 시작 함수 - 플레이어와 적 크리처를 받아 전투 루프 실행
void BattleSystem::StartBattle(Player* player, Creature* enemy)
{
    // 현재 전투에 참여하는 플레이어와 적 저장
    CurrentPlayer = player;
    EnemyCreature = enemy;

    // 전투 시작 시 초기화
    CatchAttempts = 5;   // 포획 시도 횟수 5회로 초기화
    IsEscaped = false;   // 도망 여부 초기화
    IsCaught = false;    // 포획 성공 여부 초기화

    // 파티 전체 MP 초기화
    for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
        CurrentPlayer->Owned[i]->CurrentMp = CurrentPlayer->Owned[i]->MaxMp;

    // 전투 종료 조건이 될 때까지 턴 반복
    while (!IsBattleOver())
    {
        PlayerTurn();

        if (IsBattleOver()) break;  // 플레이어 턴 후 종료 조건 재확인

        EnemyTurn();
    }
}

// 플레이어 턴 처리 - 싸우기/가방/포획/도망 4가지 행동 중 선택
void BattleSystem::PlayerTurn()
{
    PrintBattleUI();  // 전투 UI 출력
    cout << "1. 싸우기  2. 가방  3. 포획  4. 도망" << endl;

    int input = 0;
    cin >> input;

    switch (input)
    {
    case 1:
        // 스킬 목록 출력 후 선택한 스킬로 공격
        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << "." << CurrentPlayer->Active->Skills[i].Name << endl;
        }
        int Skillinput;
        cin >> Skillinput;
        Attack(CurrentPlayer->Active, EnemyCreature, Skillinput - 1);
        break;

    case 2:
    {
        cout << "\n1. 교체  2. 아이템 사용" << endl;
        int bagInput;
        cin >> bagInput;

        if (bagInput == 1)
        {
            // 파티 목록 출력 후 교체할 크리처 선택
            for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
            {
                cout << i + 1 << ". " << CurrentPlayer->Owned[i]->Name
                    << " HP: " << CurrentPlayer->Owned[i]->CurrentHp;
                if (CurrentPlayer->Owned[i] == CurrentPlayer->Active)
                    cout << " (출전중)";
                cout << endl;
            }
            int swapInput;
            cin >> swapInput;
            Creature* selected = CurrentPlayer->Owned[swapInput - 1];

            // 이미 출전 중이거나 쓰러진 크리처는 교체 불가
            if (selected == CurrentPlayer->Active)
            {
                cout << "이미 출전 중이야!" << endl;
                break;
            }
            if (selected->CurrentHp <= 0)
            {
                cout << "이미 쓰러진 크리처야!" << endl;
                break;
            }
            // Active 포인터를 선택한 크리처로 변경
            CurrentPlayer->Active = selected;
            cout << CurrentPlayer->Active->Name << " 나가!" << endl;
        }
        else if (bagInput == 2)
        {
            // 아이템 목록 출력
            cout << "\n[ 아이템 ]" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << i + 1 << ". " << CurrentPlayer->PlayerBag.Items[i].Name;
                if (CurrentPlayer->PlayerBag.Items[i].HealAmount == -1)
                    cout << " (풀회복)";
                else
                    cout << " (+" << CurrentPlayer->PlayerBag.Items[i].HealAmount << "HP)";
                cout << " x" << CurrentPlayer->PlayerBag.Items[i].Count << endl;
            }
            cout << "0. 취소" << endl;

            int itemInput;
            cin >> itemInput;
            if (itemInput == 0) break;

            Item& item = CurrentPlayer->PlayerBag.Items[itemInput - 1];
            if (item.Count <= 0)
            {
                cout << "아이템이 없다!" << endl;
                break;
            }

            // 전투 중 아이템은 출전 중인 크리처에게만 사용 가능
            Creature* target = CurrentPlayer->Active;
            if (item.HealAmount == -1)
                target->CurrentHp = target->MaxHp;        // 풀회복
            else
                target->CurrentHp = min(target->CurrentHp + item.HealAmount, target->MaxHp); // 부분 회복

            item.Count--;
            cout << target->Name << " 에게 " << item.Name << " 사용!" << endl;
            cout << "HP: " << target->CurrentHp << "/" << target->MaxHp << endl;
        }
        break;
    }

    case 3:
    {
        // 포획 시도 횟수 체크
        if (CatchAttempts <= 0)
        {
            cout << "포획 시도 횟수를 다 썼다!" << endl;
            break;
        }
        // 적 체력 30% 이하일 때만 포획 가능
        if (EnemyCreature->CurrentHp > EnemyCreature->MaxHp * 0.3f)
        {
            cout << "적 체력이 너무 많다!" << endl;
            break;
        }
        CatchAttempts--;

        // 현재 HP 비율에 따라 포획 성공률 차등 적용
        int CatchRate = 0;
        float HpRatio = (float)EnemyCreature->CurrentHp / EnemyCreature->MaxHp;
        if (HpRatio <= 0.1f)
            CatchRate = 35;  // HP 10% 이하: 35%
        else if (HpRatio <= 0.2f)
            CatchRate = 30;  // HP 20% 이하: 30%
        else if (HpRatio <= 0.3f)
            CatchRate = 20;  // HP 30% 이하: 20%

        if (rand() % 100 < CatchRate)
        {
            cout << "포획 성공!" << endl;
            IsCaught = true;

            // 도감에 등록 (처음 잡는 경우만)
            int idx = DataManager::GetCreatureIndex(EnemyCreature->Name);
            if (idx != -1 && !CurrentPlayer->Pokedex[idx])
            {
                CurrentPlayer->Pokedex[idx] = true;
                CurrentPlayer->PokedexCount++;
                cout << EnemyCreature->Name << " 도감 등록!" << endl;
            }

            // 10마리 전부 수집 시 엔딩
            if (CurrentPlayer->PokedexCount >= 10)
            {
                cout << "\n==============================" << endl;
                cout << "  축하합니다! 도감 완성!" << endl;
                cout << "  10마리를 모두 수집했습니다!" << endl;
                cout << "==============================" << endl;
                cin.ignore();
                cin.get();


                CurrentPlayer->GameClear = true;
            }

            // 엔딩이 아닐 때만 파티에 추가
            if (!CurrentPlayer->GameClear)
            {
                if (CurrentPlayer->OwnedSize < 10)
                {
                    EnemyCreature->CurrentHp = EnemyCreature->MaxHp;  // 체력 회복 후 추가
                    CurrentPlayer->Owned[CurrentPlayer->OwnedSize] = EnemyCreature;
                    CurrentPlayer->OwnedSize++;
                    cout << EnemyCreature->Name << " 을(를) 파티에 추가했다!" << endl;
                }
                else
                {
                    cout << "파티가 가득 찼다! (최대 10마리)" << endl;
                }
            }
        }
        else
            cout << "포획 실패! 남은 횟수: " << CatchAttempts << endl;
    }
        break;

    case 4:
        // 50% 확률로 도망 성공
        if (rand() % 100 < 50)
        {
            cout << "도망쳤다" << endl;
            IsEscaped = true;  // 도망 성공 시 전투 종료 플래그 설정
        }
        else
        {
            cout << "도망치지 못했다" << endl;
        }
        break;
    }
}

// 적 턴 처리 - 공용기/전용기/필살기를 확률적으로 선택해 공격
void BattleSystem::EnemyTurn()
{
    if (EnemyCreature->CurrentHp <= 0) return;  // 이미 쓰러진 경우 행동 안 함

    int skillIndex = 0;
    int roll = rand() % 100;

    // 스킬 선택 확률: 공용기 50% / 전용기 45% / 필살기 5%
    if (roll < 50)
        skillIndex = 0;
    else if (roll < 95)
        skillIndex = 1;
    else
        skillIndex = 2;

    cout << EnemyCreature->Name << " 의 "
        << EnemyCreature->Skills[skillIndex].Name << "!" << endl;

    Attack(EnemyCreature, CurrentPlayer->Active, skillIndex);
}

// 전투 종료 조건 체크 - 아군 HP 0 / 적 HP 0 / 도망 / 포획 성공
bool BattleSystem::IsBattleOver()
{
    if (CurrentPlayer->Active->CurrentHp <= 0)
        return true;
    if (EnemyCreature->CurrentHp <= 0)
        return true;
    if (IsEscaped)
        return true;
    if (IsCaught)
        return true;

    return false;
}

// 공격 처리 - 타입 상성/공격력 반영해 데미지 계산 및 적용
void BattleSystem::Attack(Creature* attacker, Creature* target, int skillIndex)
{
    Skill& skill = attacker->Skills[skillIndex];

    // 전용기(1번)는 플레이어 크리처만 MP 10 소모
    if (skillIndex == 1 && attacker == CurrentPlayer->Active)
    {
        if (attacker->CurrentMp < 10)
        {
            cout << "마나가 부족하다!" << endl;
            return;
        }
        attacker->CurrentMp -= 10;
    }

    // 필살기(2번)는 플레이어 크리처만 30% 확률로 발동
    if (skillIndex == 2 && attacker == CurrentPlayer->Active)
    {
        if (rand() % 100 >= 30)
        {
            cout << skill.Name << " 발동 실패!" << endl;
            return;
        }
        cout << "필살기 발동!" << endl;
    }

    // 타입 상성 배율 계산 (0.5 / 1.0 / 2.0)
    float multiplier = GetTypeMultiplier(skill.SkillType, target->CreatureType);

    // 최종 데미지 = 스킬 데미지 * 상성 배율 * (공격력 / 10)
    int damage = (int)(skill.Damage * multiplier * ((float)attacker->Attack / 10.0f));
    if (damage < 1) damage = 1;  // 최소 데미지 1 보장

    target->CurrentHp -= damage;
    if (target->CurrentHp < 0) target->CurrentHp = 0;  // HP 음수 방지

    cout << skill.Name << " 을(를) 사용했다!" << endl;
    if (multiplier >= 2.0f)
        cout << "효과가 굉장했다!" << endl;
    else if (multiplier <= 0.5f)
        cout << "효과가 별로인 것 같다..." << endl;
    cout << "데미지: " << damage << endl;
}

// 전투 UI 출력 - 적/아군 HP바, 아군 MP바 콘솔에 표시
void BattleSystem::PrintBattleUI()
{
    cout << "\n========================================" << endl;
    cout << "  [적]  " << EnemyCreature->Name << endl;
    cout << "  HP: [";

    // HP 비율에 따라 체력바 길이 계산 (최대 20칸)
    int barLength = 20;
    int filled = (int)((float)EnemyCreature->CurrentHp / EnemyCreature->MaxHp * barLength);
    for (int i = 0; i < filled; i++)    cout << "■";
    for (int i = filled; i < barLength; i++) cout << "□";
    cout << "] " << EnemyCreature->CurrentHp << "/" << EnemyCreature->MaxHp << endl;

    cout << "----------------------------------------" << endl;

    cout << "  [내꺼] " << CurrentPlayer->Active->Name << endl;
    cout << "  HP: [";

    filled = (int)((float)CurrentPlayer->Active->CurrentHp / CurrentPlayer->Active->MaxHp * barLength);
    for (int i = 0; i < filled; i++)    cout << "■";
    for (int i = filled; i < barLength; i++) cout << "□";
    cout << "] " << CurrentPlayer->Active->CurrentHp << "/" << CurrentPlayer->Active->MaxHp << endl;

    // MP바 출력
    cout << "  MP: [";
    int mpFilled = (int)((float)CurrentPlayer->Active->CurrentMp / CurrentPlayer->Active->MaxMp * barLength);
    for (int i = 0; i < mpFilled; i++)     cout << "■";
    for (int i = mpFilled; i < barLength; i++) cout << "□";
    cout << "] " << CurrentPlayer->Active->CurrentMp << "/" << CurrentPlayer->Active->MaxMp << endl;

    cout << "========================================" << endl;
}
