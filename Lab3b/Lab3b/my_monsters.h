#pragma once
#include "my_monsters.h"
#include <vector>

namespace monster
{
	struct info_monster;
	void write_parameter(const info_monster&, const int);
	void write_monsters(const std::vector<info_monster>&);
	std::vector<info_monster> monsters_generator(long);
}