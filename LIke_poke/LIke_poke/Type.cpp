#include "Type.h"


//타입별 상성
// 행 - 공격하는 쪽 타입 / 열 - 맞는 쪽 타입
// 불,물,바위,풀,전기 순서
static float TypeChart[5][5] =
{
	{1.0, 0.5, 0.5, 2.0, 1.0},
	{2.0, 1.0, 2.0, 0.5, 1.0},
	{1.0, 0.5, 1.0, 1.0, 1.0},
	{0.5, 2.0, 1.0, 1.0, 1.0},
	{1.0, 2.0, 1.0, 0.5, 0.5},
};

float GetTypeMultiplier(Type attackType, Type defenseType)
{
    int atk = static_cast<int>(attackType);
    int def = static_cast<int>(defenseType);

    return TypeChart[atk][def];
}