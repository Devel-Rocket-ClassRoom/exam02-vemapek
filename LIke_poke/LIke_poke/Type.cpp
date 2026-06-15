#include "Type.h"

// 행 = 공격타입, 열 = 방어타입
// Fire / Water / Rock / Grass / Electric 순서
static float TypeChart[5][5] = {
    //        Fire   Water  Rock   Grass  Electric
    /* Fire */    { 1.0f, 0.5f,  0.5f,  2.0f,  1.0f },
    /* Water */   { 2.0f, 1.0f,  2.0f,  0.5f,  1.0f },
    /* Rock */    { 1.0f, 0.5f,  1.0f,  1.0f,  1.0f },
    /* Grass */   { 0.5f, 2.0f,  1.0f,  1.0f,  1.0f },
    /* Electric */{ 1.0f, 2.0f,  1.0f,  0.5f,  0.5f },
};

// 공격 타입과 방어 타입을 인덱스로 변환해 상성 배율 반환
float GetTypeMultiplier(Type attackType, Type defenseType)
{
    // enum class를 int로 캐스팅해 배열 인덱스로 사용
    int atk = static_cast<int>(attackType);
    int def = static_cast<int>(defenseType);

    return TypeChart[atk][def];
}
