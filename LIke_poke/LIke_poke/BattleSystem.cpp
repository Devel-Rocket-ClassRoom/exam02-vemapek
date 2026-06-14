#include "BattleSystem.h"
#include <iostream>
#include "Creature.h"
#include "Type.h"
#include "DataManager.h"
#include "Player.h"

using namespace std;

void BattleSystem::StartBattle(Player* player, Creature* enemy)
{
	CurrentPlayer = player;
	EnemyCreature = enemy;
	CatchAttempts = 5;
	IsEscaped = false;
	IsCaught = false;

	for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
		CurrentPlayer->Owned[i]->CurrentMp = CurrentPlayer->Owned[i]->MaxMp;


	while (!IsBattleOver())
	{
		PlayerTurn();

		if (IsBattleOver()) break;  

		EnemyTurn();
	}
}

void BattleSystem::PlayerTurn()
{
	PrintBattleUI();
	cout << "1. 싸우기  2. 가방  3. 포획  4. 도망" << endl;

	int  input = 0;
	cin >> input;

	switch (input)
	{
	case 1:
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

			// 아이템 사용 (전투 중이니까 Active에게만)
			Creature* target = CurrentPlayer->Active;
			if (item.HealAmount == -1)
				target->CurrentHp = target->MaxHp;
			else
				target->CurrentHp = min(target->CurrentHp + item.HealAmount, target->MaxHp);

			item.Count--;
			cout << target->Name << " 에게 " << item.Name << " 사용!" << endl;
			cout << "HP: " << target->CurrentHp << "/" << target->MaxHp << endl;
		}
		break;
	}
	case 3:
	{


		if (CatchAttempts <= 0)
		{
			cout << "포획 시도 횟수를 다 썼다!" << endl;
			break;
		}
		if (EnemyCreature->CurrentHp > EnemyCreature->MaxHp * 0.3f)
		{
			cout << "적 체력이 너무 많다!" << endl;
			break;
		}
		CatchAttempts--;

		int CatchRate = 0;
		float HpRatio = (float)EnemyCreature->CurrentHp / EnemyCreature->MaxHp;

		if (HpRatio <= 0.1f)
			CatchRate = 35;
		else if (HpRatio <= 0.2f)
			CatchRate = 30;
		else if (HpRatio <= 0.3f)
			CatchRate = 20;

		if (rand() % 100 < CatchRate)
		{
			cout << "포획 성공!" << endl;
			IsCaught = true;

			// 도감 등록
			int idx = DataManager::GetCreatureIndex(EnemyCreature->Name);
			if (idx != -1 && !CurrentPlayer->Pokedex[idx])
			{
				CurrentPlayer->Pokedex[idx] = true;
				CurrentPlayer->PokedexCount++;
				cout << EnemyCreature->Name << " 도감 등록!" << endl;
			}
			// 엔딩 체크
			if (CurrentPlayer->PokedexCount >= 10)
			{
				cout << "\n==============================" << endl;
				cout << "  축하합니다! 도감 완성!" << endl;
				cout << "  10마리를 모두 수집했습니다!" << endl;
				cout << "==============================" << endl;
				CurrentPlayer->GameClear = true;
			}


			if (!CurrentPlayer->GameClear)
			{
				if (CurrentPlayer->OwnedSize < 10)
				{
					EnemyCreature->CurrentHp = EnemyCreature->MaxHp;
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
		if (rand()%100 < 50)
		{
			cout << "도망쳤다" << endl;
			IsEscaped = true;
		}
		else
		{
			cout << "도망치지 못했다" << endl;
		}
		break;
	
		
	}
}

void BattleSystem::EnemyTurn()
{
	if (EnemyCreature->CurrentHp <= 0) return;

	int skillIndex = 0;
	int roll = rand() % 100;

	if (roll < 50)
		skillIndex = 0;  // 공용기 50%
	else if (roll < 95)
		skillIndex = 1;  // 전용기 45%
	else
		skillIndex = 2;  // 필살기 5%

	cout << EnemyCreature->Name << " 의 "
		<< EnemyCreature->Skills[skillIndex].Name << "!" << endl;

	Attack(EnemyCreature, CurrentPlayer->Active, skillIndex);
}

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

void BattleSystem::Attack(Creature* attacker, Creature* target, int skillIndex)
{
	Skill& skill = attacker->Skills[skillIndex];

	if (skillIndex == 1 && attacker == CurrentPlayer->Active)
	{
		if (attacker->CurrentMp < 10)
		{
			cout << "마나가 부족하다!" << endl;
			return;
		}
		attacker->CurrentMp -= 10;
	}
	if (skillIndex == 2 && attacker == CurrentPlayer->Active)
	{
		if (rand() % 100 >= 30)
		{
			cout << skill.Name << " 발동 실패!" << endl;
			return;
		}
		cout << "필살기 발동!" << endl;
	}

	
	float multiplier = GetTypeMultiplier(skill.SkillType, target->CreatureType);
	int damage = (int)(skill.Damage * multiplier * ((float)attacker->Attack / 10.0f));
	if (damage < 1) damage = 1;

	target->CurrentHp -= damage;
	if (target->CurrentHp < 0) target->CurrentHp = 0;

	cout << skill.Name << " 을(를) 사용했다!" << endl;
	if (multiplier >= 2.0f)
		cout << "효과가 굉장했다!" << endl;
	else if (multiplier <= 0.5f)
		cout << "효과가 별로인 것 같다..." << endl;
	cout << "데미지: " << damage << endl;
}

void BattleSystem::PrintBattleUI()
{
	cout << "\n========================================" << endl;
	cout << "  [적]  " << EnemyCreature->Name << endl;
	cout << "  HP: [";

	// 체력바
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
	
	cout << "  MP: [";
	int mpFilled = (int)((float)CurrentPlayer->Active->CurrentMp / CurrentPlayer->Active->MaxMp * barLength);
	for (int i = 0; i < mpFilled; i++)     cout << "■";
	for (int i = mpFilled; i < barLength; i++) cout << "□";
	cout << "] " << CurrentPlayer->Active->CurrentMp << "/" << CurrentPlayer->Active->MaxMp << endl;

	cout << "========================================" << endl;
}