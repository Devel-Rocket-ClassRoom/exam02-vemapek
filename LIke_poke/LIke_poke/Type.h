#pragma once

//크리처와 스킬의 속성 정의
enum class Type { Fire, Water, Rock, Grass, Electric };

// 공격 타입과 방어 타입을 받아 데미지 배율 반환
// 반환값: 2.0 (효과적) / 1.0 (보통) / 0.5 (비효과적)
float GetTypeMultiplier(Type attackType, Type defenseType);
