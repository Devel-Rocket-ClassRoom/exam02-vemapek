#pragma once
#include "Creature.h"

class DataManager
{
public:
    static Creature* CreateCreature(const string& name);
    static int GetCreatureIndex(const string& name);

private:
    // 공용기 세팅
    static void SetFireball(Skill& skill);
    static void SetWaterCannon(Skill& skill);
    static void SetStoneToss(Skill& skill);
    static void SetLeafBlade(Skill& skill);
    static void Set10000Volts(Skill& skill);

    // 짭캣몬별 세팅
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