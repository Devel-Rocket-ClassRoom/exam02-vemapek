#pragma once
#include "Creature.h"
#include "Item.h"

class Player
{
public:
	string Name;
	Creature* Owned[10];
	Creature* Active;
	int OwnedSize;
	Bag PlayerBag;

	bool Pokedex[10] = { false };
	int PokedexCount = 0;
	bool GameClear = false;

};

