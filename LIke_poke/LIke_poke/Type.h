#pragma once

enum class Type { Fire, Water, Rock, Grass, Electric};


float GetTypeMultiplier(Type attackType, Type defenseType);