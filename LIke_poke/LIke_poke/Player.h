#pragma once
#include "Creature.h"
#include "Item.h"

// 플레이어 클래스 - 플레이어의 모든 상태 관리
class Player
{
public:
    string Name;            // 플레이어 이름
    Creature* Owned[10];    // 보유 크리처 배열 (최대 10마리)
    Creature* Active;       // 현재 필드에 출전 중인 크리처 포인터
    int OwnedSize;          // 현재 보유 크리처 수

    Bag PlayerBag;          // 플레이어 가방

    bool Pokedex[10] = { false };  // 도감 배열 (인덱스별 포획 여부)
    int PokedexCount = 0;          // 도감 등록 수
    bool GameClear = false;        // 10마리 수집 시 true로 변경
};
