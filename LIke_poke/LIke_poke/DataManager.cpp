#include "DataManager.h"

// ===== 공용기 세팅 함수 =====
// 각 타입별 공용기 데이터를 스킬에 세팅

void DataManager::SetFireball(Skill& skill)
{
    skill.Name = "파이어볼";
    skill.SkillType = Type::Fire;
    skill.Damage = 20;
    skill.Ult = false;
}
void DataManager::SetWaterCannon(Skill& skill)
{
    skill.Name = "물대포";
    skill.SkillType = Type::Water;
    skill.Damage = 20;
    skill.Ult = false;
}
void DataManager::SetStoneToss(Skill& skill)
{
    skill.Name = "돌 던지기";
    skill.SkillType = Type::Rock;
    skill.Damage = 20;
    skill.Ult = false;
}
void DataManager::SetLeafBlade(Skill& skill)
{
    skill.Name = "씨 뱉기";
    skill.SkillType = Type::Grass;
    skill.Damage = 20;
    skill.Ult = false;
}
void DataManager::Set10000Volts(Skill& skill)
{
    skill.Name = "1만볼트";
    skill.SkillType = Type::Electric;
    skill.Damage = 20;
    skill.Ult = false;
}

// ===== 크리처별 데이터 세팅 함수 =====
// Skills[0] = 공용기 / Skills[1] = 전용기 / Skills[2] = 필살기

void DataManager::SetDokchimsul(Creature& c)
{
    c.Name = "독침불";
    c.CreatureType = Type::Fire;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 14;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetFireball(c.Skills[0]);           // 공용기
    c.Skills[1].Name = "불꽃놀이";
    c.Skills[1].SkillType = Type::Fire;
    c.Skills[1].Damage = 50;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "팔척염곡옥";   // 필살기
    c.Skills[2].SkillType = Type::Fire;
    c.Skills[2].Damage = 160;
    c.Skills[2].Ult = true;
}
void DataManager::SetBulkeurin(Creature& c)
{
    c.Name = "불크린";
    c.CreatureType = Type::Fire;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 14;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetFireball(c.Skills[0]);
    c.Skills[1].Name = "불주먹";
    c.Skills[1].SkillType = Type::Fire;
    c.Skills[1].Damage = 50;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "명구";
    c.Skills[2].SkillType = Type::Fire;
    c.Skills[2].Damage = 150;
    c.Skills[2].Ult = true;
}
void DataManager::SetBikatzu(Creature& c)
{
    c.Name = "비카츄";
    c.CreatureType = Type::Water;
    c.MaxHp = 400; c.CurrentHp = 400;
    c.Attack = 12;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetWaterCannon(c.Skills[0]);
    c.Skills[1].Name = "산성비";
    c.Skills[1].SkillType = Type::Water;
    c.Skills[1].Damage = 45;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "비틀린 소용돌이";
    c.Skills[2].SkillType = Type::Water;
    c.Skills[2].Damage = 150;
    c.Skills[2].Ult = true;
}
void DataManager::SetMulraeduji(Creature& c)
{
    c.Name = "물래두지";
    c.CreatureType = Type::Water;
    c.MaxHp = 400; c.CurrentHp = 400;
    c.Attack = 12;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetWaterCannon(c.Skills[0]);
    c.Skills[1].Name = "물레방아";
    c.Skills[1].SkillType = Type::Water;
    c.Skills[1].Damage = 45;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "대격류 윤회격";
    c.Skills[2].SkillType = Type::Water;
    c.Skills[2].Damage = 170;
    c.Skills[2].Ult = true;
}
void DataManager::SetBawiri(Creature& c)
{
    c.Name = "바위리";
    c.CreatureType = Type::Rock;
    c.MaxHp = 450; c.CurrentHp = 450;
    c.Attack = 10;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetStoneToss(c.Skills[0]);
    c.Skills[1].Name = "짱돌던지기";
    c.Skills[1].SkillType = Type::Rock;
    c.Skills[1].Damage = 40;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "큰 돌 던지기";
    c.Skills[2].SkillType = Type::Rock;
    c.Skills[2].Damage = 130;
    c.Skills[2].Ult = true;
}
void DataManager::SetRongBawi(Creature& c)
{
    c.Name = "롱바위";
    c.CreatureType = Type::Rock;
    c.MaxHp = 450; c.CurrentHp = 450;
    c.Attack = 10;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetStoneToss(c.Skills[0]);
    c.Skills[1].Name = "쇄암난무";
    c.Skills[1].SkillType = Type::Rock;
    c.Skills[1].Damage = 45;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "암룡포식진";
    c.Skills[2].SkillType = Type::Rock;
    c.Skills[2].Damage = 250;
    c.Skills[2].Ult = true;
}
void DataManager::SetJeongsangHaessi(Creature& c)
{
    c.Name = "정상해씨";
    c.CreatureType = Type::Grass;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 11;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetLeafBlade(c.Skills[0]);
    c.Skills[1].Name = "몸통박치기";
    c.Skills[1].SkillType = Type::Grass;
    c.Skills[1].Damage = 45;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "요화기생";
    c.Skills[2].SkillType = Type::Grass;
    c.Skills[2].Damage = 150;
    c.Skills[2].Ult = true;
}
void DataManager::SetPulrip(Creature& c)
{
    c.Name = "풀리프";
    c.CreatureType = Type::Grass;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 11;
    c.MaxMp = 30; c.CurrentMp = 30;
    SetLeafBlade(c.Skills[0]);
    c.Skills[1].Name = "잎날가르기";
    c.Skills[1].SkillType = Type::Grass;
    c.Skills[1].Damage = 50;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "만극산화";
    c.Skills[2].SkillType = Type::Grass;
    c.Skills[2].Damage = 150;
    c.Skills[2].Ult = true;
}
void DataManager::SetDukkeobi(Creature& c)
{
    c.Name = "두꺼비집";
    c.CreatureType = Type::Electric;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 14;
    c.MaxMp = 30; c.CurrentMp = 30;
    Set10000Volts(c.Skills[0]);
    c.Skills[1].Name = "암전";
    c.Skills[1].SkillType = Type::Electric;
    c.Skills[1].Damage = 50;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "합선";
    c.Skills[2].SkillType = Type::Electric;
    c.Skills[2].Damage = 170;
    c.Skills[2].Ult = true;
}
void DataManager::SetJeonoking(Creature& c)
{
    c.Name = "전어킹";
    c.CreatureType = Type::Electric;
    c.MaxHp = 350; c.CurrentHp = 350;
    c.Attack = 14;
    c.MaxMp = 30; c.CurrentMp = 30;
    Set10000Volts(c.Skills[0]);
    c.Skills[1].Name = "펄떡거리기";
    c.Skills[1].SkillType = Type::Electric;
    c.Skills[1].Damage = 50;
    c.Skills[1].Ult = false;
    c.Skills[2].Name = "1000만볼트";
    c.Skills[2].SkillType = Type::Electric;
    c.Skills[2].Damage = 170;
    c.Skills[2].Ult = true;
}

// 이름을 받아 해당 크리처를 동적 생성 후 반환
// new로 생성하므로 사용 후 delete 필요
Creature* DataManager::CreateCreature(const string& name)
{
    Creature* c = new Creature();

    if      (name == "독침불")   SetDokchimsul(*c);
    else if (name == "불크린")   SetBulkeurin(*c);
    else if (name == "비카츄")   SetBikatzu(*c);
    else if (name == "물래두지") SetMulraeduji(*c);
    else if (name == "바위리")   SetBawiri(*c);
    else if (name == "롱바위")   SetRongBawi(*c);
    else if (name == "정상해씨") SetJeongsangHaessi(*c);
    else if (name == "풀리프")   SetPulrip(*c);
    else if (name == "두꺼비집") SetDukkeobi(*c);
    else if (name == "전어킹")   SetJeonoking(*c);

    return c;
}

// 크리처 이름을 도감 인덱스(0~9)로 변환
// 도감 등록 시 Pokedex 배열의 인덱스로 사용
int DataManager::GetCreatureIndex(const string& name)
{
    if      (name == "독침불")   return 0;
    else if (name == "불크린")   return 1;
    else if (name == "비카츄")   return 2;
    else if (name == "물래두지") return 3;
    else if (name == "바위리")   return 4;
    else if (name == "롱바위")   return 5;
    else if (name == "정상해씨") return 6;
    else if (name == "풀리프")   return 7;
    else if (name == "두꺼비집") return 8;
    else if (name == "전어킹")   return 9;
    return -1;  // 없는 이름이면 -1 반환
}
