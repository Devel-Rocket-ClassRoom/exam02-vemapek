#pragma once
#include "Player.h"

// 전투 시스템 클래스 - 턴제 전투 전체를 관리
class BattleSystem
{
public:
    // 전투 시작 - 플레이어와 야생 크리처를 받아 전투 루프 실행
    void StartBattle(Player* player, Creature* enemy);

    // 포획 성공 여부 반환 - MapSystem에서 메모리 해제 여부 판단에 사용
    bool GetIsCaught() const { return IsCaught; }

    // 적 크리처를 쓰러뜨렸는지 반환 - 포션 드롭 판단에 사용
    bool IsEnemyDefeated() { return EnemyCreature->CurrentHp <= 0 && !IsCaught; }

private:
    void PlayerTurn();      // 플레이어 행동 처리
    void EnemyTurn();       // 적 행동 처리
    bool IsBattleOver();    // 전투 종료 조건 체크
    void Attack(Creature* attacker, Creature* target, int skillIndex); // 공격 처리
    void PrintBattleUI();   // 전투 UI 출력

    Player* CurrentPlayer;      // 현재 전투 중인 플레이어
    Creature* EnemyCreature;    // 현재 전투 중인 적 크리처

    int CatchAttempts;  // 남은 포획 시도 횟수
    bool IsEscaped;     // 도망 성공 여부
    bool IsCaught;      // 포획 성공 여부
};
