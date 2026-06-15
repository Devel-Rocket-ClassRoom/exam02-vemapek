#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DataManager.h"
#include "MapSystem.h"
using namespace std;

int main()
{
    // 랜덤 시드 초기화 - 실행할 때마다 다른 랜덤값 생성
    srand((unsigned int)time(nullptr));

    cout << "============================" << endl;
    cout << "     짭캣몬 어드벤처!       " << endl;
    cout << "============================" << endl;

    // 플레이어 생성 및 이름 입력
    Player player;
    cout << "\n이름을 입력하세요: ";
    cin >> player.Name;
    player.OwnedSize = 0;

    // 시작 크리처 선택 (불/물/풀 중 1마리)
    cout << "\n시작 짭캣몬을 선택하세요!" << endl;
    cout << "1. 독침불 (불)\n2. 비카츄 (물)\n3. 정상해씨 (풀)" << endl;

    int choice;
    cin >> choice;

    string starterName;
    if      (choice == 1) starterName = "독침불";
    else if (choice == 2) starterName = "비카츄";
    else                  starterName = "정상해씨";

    // DataManager로 시작 크리처 생성 후 파티에 추가
    Creature* starter = DataManager::CreateCreature(starterName);
    player.Owned[0] = starter;
    player.OwnedSize = 1;
    player.Active = starter;  // 첫 크리처를 출전 크리처로 설정

    cout << "\n" << starterName << " 을(를) 선택했다!" << endl;
    
    //for (int i = 0; i < 9; i++)
    //    player.Pokedex[i] = true;
    //player.PokedexCount = 9;


    
    // 맵 탐험 시작
    MapSystem map;
    map.Init(&player);
    map.Run();

    cout << "\n게임 종료!" << endl;

    // 동적 생성한 크리처 메모리 해제
    for (int i = 0; i < player.OwnedSize; i++)
        delete player.Owned[i];

    return 0;
}
