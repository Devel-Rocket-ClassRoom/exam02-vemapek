#include "MapSystem.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void MapSystem::Init(Player* player)
{
    CurrentPlayer = player;
    PlayerX = 19;
    PlayerY = 0;
}

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
        if (input == 'w' || input == 'W') dy = -1;
        else if (input == 's' || input == 'S') dy = 1;
        else if (input == 'a' || input == 'A') dx = -1;
        else if (input == 'd' || input == 'D') dx = 1;
        else if (input == 'b' || input == 'B')
        {
            OpenBag();
            continue;
        }

        Move(dx, dy);
        CheckEncounter();
        if (CurrentPlayer->GameClear) break;
    }
}

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
    cout << "[ . 마을 | ~ 풀숲 | # 동굴 | w 물가 ]" << endl;
}

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

void MapSystem::CheckEncounter()
{
    Zone zone = GetCurrentZone();
    if (zone.EncounterRate == 0) return;

    if (rand() % 100 < zone.EncounterRate)
    {
        int idx = rand() % zone.WildCount;
        Creature* wild = DataManager::CreateCreature(zone.WildCreatures[idx]);

        cout << "\n야생 " << wild->Name << " 이(가) 나타났다!" << endl;
        Battle.StartBattle(CurrentPlayer, wild);

        // 포션 드롭 (쓰러뜨렸을 때만)
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
            // 5% 없음
        }

        if (!Battle.GetIsCaught())
            delete wild;
    }
}

Zone MapSystem::GetCurrentZone()
{
    Zone zone;
    switch (MapGrid[PlayerY][PlayerX])
    {
    case ZoneType::Town:
        zone.Name = "마을";
        zone.Type = ZoneType::Town;
        zone.EncounterRate = 0;
        zone.WildCount = 0;
        break;

    case ZoneType::Grass:
        zone.Name = "풀숲";
        zone.Type = ZoneType::Grass;
        zone.EncounterRate = 30;
        zone.WildCreatures[0] = "정상해씨";
        zone.WildCreatures[1] = "풀리프";
        zone.WildCreatures[2] = "두꺼비집";
        zone.WildCreatures[3] = "독침불";
        zone.WildCount = 4;
        break;
    case ZoneType::Cave:
        zone.Name = "동굴";
        zone.Type = ZoneType::Cave;
        zone.EncounterRate = 40;
        zone.WildCreatures[0] = "바위리";
        zone.WildCreatures[1] = "롱바위";
        zone.WildCreatures[2] = "불크린";
        zone.WildCreatures[3] = "독침불";
        zone.WildCount = 4;
        break;
    case ZoneType::Water:
        zone.Name = "물가";
        zone.Type = ZoneType::Water;
        zone.EncounterRate = 35;
        zone.WildCreatures[0] = "비카츄";
        zone.WildCreatures[1] = "물래두지";
        zone.WildCreatures[2] = "전어킹";
        zone.WildCreatures[3] = "두꺼비집";
        zone.WildCount = 4;
        break;
    }
    return zone;
}

void MapSystem::OpenPokedex()
{
    cout << "\n=== 도감 ===" << endl;
    cout << "수집: " << CurrentPlayer->PokedexCount << "/10" << endl;
    cout << endl;

    string names[10] = {
    "독침불", "불크린", "비카츄", "물래두지", "바위리",
    "롱바위", "정상해씨", "풀리프", "두꺼비집", "전어킹"
    };
    for (int i = 0; i < 10; i++)
    {
        if (CurrentPlayer->Pokedex[i])
            cout << i + 1 << ". " << names[i] << " O" << endl;
        else
            cout << i + 1 << ". ???" << endl;
    }

}

void MapSystem::OpenBag()
{
    cout << "\n=== 가방 ===" << endl;
    cout << "1. 아이템 사용  2. 도감" << endl;

    int MenuInput;
    cin >> MenuInput;


    if (MenuInput == 1)
    {
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
    }
    else if (MenuInput == 2)
    {
        OpenPokedex();
        return;
    }

    // 아이템 목록
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

    // 아이템 사용
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

    // 어느 짭캣몬에게 쓸지
    cout << "어느 짭캣몬에게 쓸까?" << endl;
    for (int i = 0; i < CurrentPlayer->OwnedSize; i++)
    {
        cout << i + 1 << ". " << CurrentPlayer->Owned[i]->Name
            << " HP: " << CurrentPlayer->Owned[i]->CurrentHp
            << "/" << CurrentPlayer->Owned[i]->MaxHp << endl;
    }
    int targetInput;
    cin >> targetInput;

    Creature* target = CurrentPlayer->Owned[targetInput - 1];
    if (item.HealAmount == -1)
        target->CurrentHp = target->MaxHp;
    else
        target->CurrentHp = min(target->CurrentHp + item.HealAmount, target->MaxHp);

    item.Count--;
    cout << target->Name << " 에게 " << item.Name << " 사용!" << endl;
    cout << "HP: " << target->CurrentHp << "/" << target->MaxHp << endl;
}