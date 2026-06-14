#include "MapSystem.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// 플레이어 초기화 및 시작 위치 설정 (오른쪽 상단 마을)
void MapSystem::Init(Player* player)
{
    CurrentPlayer = player;
    PlayerX = 19;
    PlayerY = 0;
}

// 메인 루프 - WASD 이동 / B 가방 / Q 종료
void MapSystem::Run()
{
    cout << "\n탐험을 시작한다!" << endl;
    cout << "W/A/S/D 로 이동, B 가방열기, Q 종료" << endl;

    char input;
    while (true)
    {
        PrintMap();
        cout << "\n이동 방향 입력(B 가방열기): ";
        cin >> input;

        if (input == 'q' || input == 'Q') break;

        int dx = 0, dy = 0;
        if      (input == 'w' || input == 'W') dy = -1;
        else if (input == 's' || input == 'S') dy =  1;
        else if (input == 'a' || input == 'A') dx = -1;
        else if (input == 'd' || input == 'D') dx =  1;
        else if (input == 'b' || input == 'B')
        {
            OpenBag();
            continue;
        }

        Move(dx, dy);
        CheckEncounter();

        // 10마리 수집 완료 시 게임 종료
        if (CurrentPlayer->GameClear) break;
    }
}

// 현재 맵 상태 콘솔 출력
// P = 플레이어 / . = 마을 / ~ = 풀숲 / # = 동굴 / W = 물가
void MapSystem::PrintMap()
{
    cout << "\n=== 맵 ===" << endl;
    for (int y = 0; y < MapHeight; y++)
    {
        for (int x = 0; x < MapWidth; x++)
        {
            if (x == PlayerX && y == PlayerY)
                cout << "P ";
            else
            {
                switch (MapGrid[y][x])
                {
                case ZoneType::Town:  cout << ". "; break;
                case ZoneType::Grass: cout << "~ "; break;
                case ZoneType::Cave:  cout << "# "; break;
                case ZoneType::Water: cout << "W "; break;
                }
            }
        }
        cout << endl;
    }
    cout << "[ . 마을 | ~ 풀숲 | # 동굴 | W 물가 ]" << endl;
}

// 플레이어 이동 처리 - 맵 범위 벗어나면 이동 불가
void MapSystem::Move(int dx, int dy)
{
    int newX = PlayerX + dx;
    int newY = PlayerY + dy;

    if (newX < 0 || newX >= MapWidth || newY < 0 || newY >= MapHeight)
    {
        cout << "더 이상 갈 수 없다!" << endl;
        return;
    }

    PlayerX = newX;
    PlayerY = newY;

    Zone zone = GetCurrentZone();
    cout << zone.Name << " 에 들어섰다." << endl;
}

// 야생 조우 판정 - 구역별 확률로 랜덤 크리처 등장 후 전투 실행
void MapSystem::CheckEncounter()
{
    Zone zone = GetCurrentZone();
    if (zone.EncounterRate == 0) return;  // 마을은 조우 없음

    if (rand() % 100 < zone.EncounterRate)
    {
        // 구역 내 등장 크리처 중 랜덤 선택
        int idx = rand() % zone.WildCount;
        Creature* wild = DataManager::CreateCreature(zone.WildCreatures[idx]);

        cout << "\n야생 " << wild->Name << " 이(가) 나타났다!" << endl;
        Battle.StartBattle(CurrentPlayer, wild);

        // 쓰러뜨렸을 때만 포션 드롭
        if (Battle.IsEnemyDefeated())
        {
            int drop = rand() % 100;
            if (drop < 60)        // 60% 소회복
            {
                int count = rand() % 5 + 1;  // 1~5개
                CurrentPlayer->PlayerBag.Items[0].Count += count;
                cout << "소회복 포션 x" << count << " 을 얻었다!" << endl;
            }
            else if (drop < 90)   // 30% 중회복
            {
                int count = rand() % 4 + 1;  // 1~4개
                CurrentPlayer->PlayerBag.Items[1].Count += count;
                cout << "중회복 포션 x" << count << " 을 얻었다!" << endl;
            }
            else if (drop < 95)   // 5% 풀회복
            {
                int count = rand() % 2 + 1;  // 1~2개
                CurrentPlayer->PlayerBag.Items[2].Count += count;
                cout << "풀회복 포션 x" << count << " 을 얻었다!" << endl;
            }
            // 5% 아무것도 안 드롭
        }

        // 포획하지 않은 경우에만 메모리 해제
        if (!Battle.GetIsCaught())
            delete wild;
    }
}

// 현재 플레이어 위치 기준 구역 정보 반환
Zone MapSystem::GetCurrentZone()
{
    Zone zone;
    switch (MapGrid[PlayerY][PlayerX])
    {
    case ZoneType::Town:
        zone.Name = "마을";
        zone.Type = ZoneType::Town;
        zone.EncounterRate = 0;     // 마을은 조우 없음
        zone.WildCount = 0;
        break;
    case ZoneType::Grass:
        zone.Name = "풀숲";
        zone.Type = ZoneType::Grass;
        zone.EncounterRate = 30;    // 30% 확률로 조우
        zone.WildCreatures[0] = "정상해씨";
        zone.WildCreatures[1] = "풀리프";
        zone.WildCreatures[2] = "두꺼비집";
        zone.WildCreatures[3] = "독침불";
        zone.WildCount = 4;
        break;
    case ZoneType::Cave:
        zone.Name = "동굴";
        zone.Type = ZoneType::Cave;
        zone.EncounterRate = 40;    // 40% 확률로 조우
        zone.WildCreatures[0] = "바위리";
        zone.WildCreatures[1] = "롱바위";
        zone.WildCreatures[2] = "불크린";
        zone.WildCreatures[3] = "독침불";
        zone.WildCount = 4;
        break;
    case ZoneType::Water:
        zone.Name = "물가";
        zone.Type = ZoneType::Water;
        zone.EncounterRate = 35;    // 35% 확률로 조우
        zone.WildCreatures[0] = "비카츄";
        zone.WildCreatures[1] = "물래두지";
        zone.WildCreatures[2] = "전어킹";
        zone.WildCreatures[3] = "두꺼비집";
        zone.WildCount = 4;
        break;
    }
    return zone;
}

// 가방 열기 - 아이템 사용 또는 도감 확인
void MapSystem::OpenBag()
{
    cout << "\n=== 가방 ===" << endl;
    cout << "1. 아이템 사용  2. 도감" << endl;

    int menuInput;
    cin >> menuInput;

    if (menuInput == 2)
    {
        OpenPokedex();
        return;
    }

    // 파티 목록 출력
    cout << "\n[ 파티 ]" << endl;
    for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
    {
        cout << i + 1 << ". " << CurrentPlayer->Owned[i]->Name
            << " HP: " << CurrentPlayer->Owned[i]->CurrentHp
            << "/" << CurrentPlayer->Owned[i]->MaxHp;
        if (CurrentPlayer->Owned[i] == CurrentPlayer->Active)
            cout << " (출전중)";
        cout << endl;
    }

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

    cout << "\n아이템 사용? (1~3 선택 / 0 닫기)" << endl;
    int input;
    cin >> input;
    if (input == 0) return;

    Item& item = CurrentPlayer->PlayerBag.Items[input - 1];
    if (item.Count <= 0)
    {
        cout << "아이템이 없다!" << endl;
        return;
    }

    // 어느 크리처에게 쓸지 선택
    cout << "어느 크리처에게 쓸까?" << endl;
    for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
    {
        cout << i + 1 << ". " << CurrentPlayer->Owned[i]->Name
            << " HP: " << CurrentPlayer->Owned[i]->CurrentHp
            << "/" << CurrentPlayer->Owned[i]->MaxHp << endl;
    }
    int targetInput;
    cin >> targetInput;

    Creature* target = CurrentPlayer->Owned[targetInput - 1];

    // 풀회복(-1)이면 최대 HP로, 아니면 HealAmount만큼 회복 (최대치 초과 불가)
    if (item.HealAmount == -1)
        target->CurrentHp = target->MaxHp;
    else
        target->CurrentHp = min(target->CurrentHp + item.HealAmount, target->MaxHp);

    item.Count--;
    cout << target->Name << " 에게 " << item.Name << " 사용!" << endl;
    cout << "HP: " << target->CurrentHp << "/" << target->MaxHp << endl;
}

// 도감 출력 - 포획한 크리처는 이름 표시, 미포획은 ???로 표시
void MapSystem::OpenPokedex()
{
    cout << "\n=== 도감 ===" << endl;
    cout << "수집: " << CurrentPlayer->PokedexCount << "/10" << endl;
    cout << endl;

    // 도감 인덱스 순서와 동일하게 출력
    string names[10] = {
        "독침불", "불크린", "비카츄", "물래두지", "바위리",
        "롱바위", "정상해씨", "풀리프", "두꺼비집", "전어킹"
    };

    for (int i = 0; i < 10; i++)
    {
        if (CurrentPlayer->Pokedex[i])
            cout << i + 1 << ". " << names[i] << " ✓" << endl;
        else
            cout << i + 1 << ". ???" << endl;
    }
}
