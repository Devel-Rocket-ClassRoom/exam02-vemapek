#pragma once
#include "Skill.h"

// 크리처 클래스 - 짭캣몬 한 마리의 모든 데이터를 담는 클래스
class Creature
{
public:
    string Name;        // 크리처 이름
    Type CreatureType;  // 크리처 타입 (불/물/바위/풀/전기)
    int MaxHp;          // 최대 체력
    int CurrentHp;      // 현재 체력 (전투 중 감소)
    int Attack;         // 공격력 (데미지 계산에 사용)
    int MaxMp;          // 최대 마나
    int CurrentMp;      // 현재 마나 (전용기 사용 시 소모)
    Skill Skills[3];    // 스킬 배열 [0]공용기 / [1]전용기 / [2]필살기
};
