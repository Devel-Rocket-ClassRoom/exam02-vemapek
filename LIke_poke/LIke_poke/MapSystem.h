#pragma once
#include "Player.h"
#include "BattleSystem.h"
#include "DataManager.h"
#include <string>
using namespace std;

// 구역 종류
enum class ZoneType { Town, Grass, Cave, Water };

// 구역 구조체 - 맵의 각 구역 정보
struct Zone
{
    string Name;                // 구역 이름
    ZoneType Type;              // 구역 종류
    int EncounterRate;          // 야생 조우 확률 (%)
    string WildCreatures[4];    // 이 구역에 출현하는 크리처 이름 목록
    int WildCount;              // 출현 크리처 종류 수
};

// 맵 시스템 클래스 - 20x20 맵 탐험 및 게임 루프 관리
class MapSystem
{
public:
    void Init(Player* player);  // 초기화 - 플레이어 설정 및 시작 위치 지정
    void Run();                 // 메인 루프 - 이동/가방/종료 입력 처리

private:
    void PrintMap();            // 맵 출력
    void Move(int dx, int dy);  // 플레이어 이동 처리
    void CheckEncounter();      // 야생 조우 판정 및 전투 실행
    Zone GetCurrentZone();      // 현재 위치의 구역 정보 반환
    void OpenBag();             // 가방 열기 (아이템 사용)
    void OpenPokedex();         // 도감 열기 (수집 현황 출력)

    Player* CurrentPlayer;  // 현재 플레이어 포인터
    BattleSystem Battle;    // 전투 시스템 인스턴스

    int PlayerX;  // 플레이어 X 좌표
    int PlayerY;  // 플레이어 Y 좌표

    static const int MapWidth = 20;
    static const int MapHeight = 20;

    // 20x20 맵 배열 - ZoneType으로 각 칸의 구역 종류 지정
    ZoneType MapGrid[MapHeight][MapWidth] = {
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Water,  ZoneType::Water,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Water,  ZoneType::Water,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Town },
        { ZoneType::Cave,  ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Grass },
        { ZoneType::Cave,  ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Grass, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Town, ZoneType::Town, ZoneType::Town, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Cave, ZoneType::Cave, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Water, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
        { ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Cave, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass, ZoneType::Grass },
    };
};
