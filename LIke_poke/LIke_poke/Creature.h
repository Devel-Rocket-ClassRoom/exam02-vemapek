#pragma once
#include "Skill.h"

class Creature
{
public:
    string Name;
    Type CreatureType;
    int MaxHp;
    int CurrentHp;
    int Attack;
    int MaxMp;     
    int CurrentMp;  
    Skill Skills[3];
};
