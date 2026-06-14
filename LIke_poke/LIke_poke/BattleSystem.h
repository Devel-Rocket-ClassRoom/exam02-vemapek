#pragma once
#include "Player.h"

class BattleSystem
{
public:
	void StartBattle(Player* player, Creature* enemy);
	bool GetIsCaught() const { return IsCaught; }
	bool IsEnemyDefeated() const { return EnemyCreature->CurrentHp <= 0 && !IsCaught; }

private:
	void PlayerTurn();
	void EnemyTurn();
	bool IsBattleOver();
	Player* CurrentPlayer;    // 현재 전투 중인 플레이어
	Creature* EnemyCreature;  // 현재 전투 중인 적
	int CatchAttempts;		
	bool IsEscaped;
	void Attack(Creature* attacker, Creature* target, int skillIndex);
	bool IsCaught;  // 포획 성공 여부
	void PrintBattleUI();
};

