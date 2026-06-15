#pragma once
#include "Creature.h"

// 데이터 매니저 클래스 - 크리처 생성 및 데이터 관리
class DataManager
{
public:
    // 이름을 받아 해당 크리처를 동적 생성 후 반환
    static Creature* CreateCreature(const string& name);

    // 크리처 이름을 도감 인덱스(0~9)로 변환
    static int GetCreatureIndex(const string& name);

private:
    // 공용기 세팅 함수 (타입별 1개씩)
    static void SetFireball(Skill& skill);
    static void SetWaterCannon(Skill& skill);
    static void SetStoneToss(Skill& skill);
    static void SetLeafBlade(Skill& skill);
    static void Set10000Volts(Skill& skill);

    // 크리처별 데이터 세팅 함수
    static void SetDokchimsul(Creature& c);
    static void SetBulkeurin(Creature& c);
    static void SetBikatzu(Creature& c);
    static void SetMulraeduji(Creature& c);
    static void SetBawiri(Creature& c);
    static void SetRongBawi(Creature& c);
    static void SetJeongsangHaessi(Creature& c);
    static void SetPulrip(Creature& c);
    static void SetDukkeobi(Creature& c);
    static void SetJeonoking(Creature& c);
};
