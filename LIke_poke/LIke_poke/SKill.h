#pragma once
#include "Type.h"
#include <string>
using namespace std;

// 스킬 구조체 - 크리처가 사용하는 기술 데이터
struct Skill
{
    string Name;        // 스킬 이름
    Type SkillType;     // 스킬 타입 (상성 계산에 사용)
    int Damage;         // 기본 데미지 수치
    bool Ult;           // 필살기 여부 (true면 필살기)
};
