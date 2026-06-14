#pragma once
#include "Type.h"
#include <string>
using namespace std;

struct Skill
{
	string Name;
	Type SkillType;
	int Damage;
	bool Ult;
};