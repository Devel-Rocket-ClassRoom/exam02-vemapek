#pragma once
#include "Player.h"
#include "BattleSystem.h"
#include "DataManager.h"
#include <string>
using namespace std;

enum class ZoneType { Town, Grass, Cave, Water };

struct Zone
{
    string Name;
    ZoneType Type;
    int EncounterRate;
    string WildCreatures[4];
    int WildCount;
};

class MapSystem
{
public:
    void Init(Player* player);
    void Run();

private:
    void PrintMap();
    void Move(int dx, int dy);
    void CheckEncounter();
    Zone GetCurrentZone();
    void OpenBag();
    void OpenPokedex();

    Player* CurrentPlayer;
    BattleSystem Battle;

    int PlayerX;
    int PlayerY;

    static const int MapWidth = 20;
    static const int MapHeight = 20;

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