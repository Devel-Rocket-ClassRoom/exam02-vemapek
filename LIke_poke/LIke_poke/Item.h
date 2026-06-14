#pragma once
#include <string>
using namespace std;

// 아이템 구조체 - 회복 아이템 데이터
struct Item
{
    string Name;    // 아이템 이름
    int HealAmount; // 회복량 (-1이면 풀회복)
    int Count;      // 보유 개수
};

// 가방 구조체 - 소회복/중회복/풀회복 3종 고정 슬롯
struct Bag
{
    Item Items[3] = {
        {"소회복 포션", 150, 3},   // 150HP 회복, 3개
        {"중회복 포션", 220, 2},   // 220HP 회복, 2개
        {"풀회복 포션", -1,  1},   // 풀회복, 1개
    };
};
