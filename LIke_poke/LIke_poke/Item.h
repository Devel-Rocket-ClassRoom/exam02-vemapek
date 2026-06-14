#pragma once
#include <string>
using namespace std;

struct Item
{
    string Name;
    int HealAmount;  // -1이면 풀회복
    int Count;
};

struct Bag
{
    Item Items[3] = {
        {"소회복 포션", 150, 3},   // 100 회복
        {"중회복 포션", 250, 2},   // 250 회복
        {"풀회복 포션", -1,  1},   // 풀회복
    };
};