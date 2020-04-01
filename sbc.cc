/*
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *		    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>

using namespace std;

struct Character
{
	string name;
	vector<int> stats;
	int lvl;

	bool isWorseThan(const Character &other) const
	{
		assert(other.stats.size() == stats.size());

		/* higher lvl is worse */
		if (lvl != other.lvl)
			return lvl > other.lvl;

		bool worse = false;
		for (int i = 0; i < (int)stats.size(); i++)
		{
			/* if some stat is higher, they are tied */
			if (stats[i] > other.stats[i])
				return false;
			/* if one is less, and the others are at most equal */
			if (stats[i] < other.stats[i])
				worse = true;
		}
		return worse;
	}
};

struct Game
{
	string name;
	string abbrev;
	vector<string> stats;
	vector<Character> classes;
};

static const vector<Game> GAMES = {
	{
		"Demon's Souls", "demon",
		{				"Vitality",	"Intelligence",	"Endurance",	"Strength",	"Dexterity",	"Magic",	"Faith",	"Luck" },
		{
			{ "Knight",		{ 10,		11,		11,		14,		10,		10,		11,		7  },	4 },
			{ "Priest",		{ 13,		11,		12,		10,		8,		8,		13,		8  },	6 },
			{ "Thief",		{ 10,		13,		10,		9,		14,		10,		8,		15 },	9 },
			{ "Magician",		{ 9,		15,		10,		9,		11,		15,		6,		11 },	6 },
			{ "Temple Knight",	{ 11,		8,		13,		14,		12,		6,		13,		7  },	4 },
			{ "Soldier",		{ 14,		9,		12,		12,		11,		8,		10,		10 },	6 },
			{ "Wanderer",		{ 10,		10,		11,		11,		15,		9,		7,		13 },	6 },
			{ "Barbarian",		{ 15,		7,		13,		15,		9,		11,		8,		11 },	9 },
			{ "Royalty",		{ 8,		12,		8,		9,		12,		13,		12,		7  },	1 },
			{ "Hunter",		{ 12,		10,		13,		11,		12,		8,		8,		12 },	6 },
		}
	},
	{
		"Dark Souls", "dark",
		{				"Vitality",	"Attunement",	"Endurance",	"Strength",	"Dexterity",	"Resistance",	"Intelligence",	"Faith" },
		{
			{ "Warrior",		{ 11,		8,		12,		13,		13,		11,		9,		9  },	4 },
			{ "Knight",		{ 14,		10,		10,		11,		11,		10,		9,		11 },	5 },
			{ "Wanderer",		{ 10,		11,		10,		10,		14,		12,		11,		8  },	3 },
			{ "Thief",		{ 9,		11,		9,		9,		15,		10,		12,		11 },	5 },
			{ "Bandit",		{ 12,		8,		14,		14,		9,		11,		8,		10 },	4 },
			{ "Hunter",		{ 11,		9,		11,		12,		14,		11,		9,		9  },	4 },
			{ "Sorcerer",		{ 8,		15,		8,		9,		11,		8,		15,		8  },	3 },
			{ "Pyromancer",		{ 10,		12,		11,		12,		9,		12,		10,		8  },	1 },
			{ "Cleric",		{ 11,		11,		9,		12,		8,		11,		8,		14 },	2 },
			{ "Deprived",		{ 11,		11,		11,		11,		11,		11,		11,		11 },	6 },
		}
	},
	{
		"Dark Souls II", "dark2",
		{				"Vigor",	"Endurance",	"Vitality",	"Attunement",	"Strength",	"Dexterity",	"Adaptability",	"Intelligence",	"Faith" },
		{
			{ "Warrior",		{ 7,		6,		6,		5,		15,		11,		5,		5,		5  },	12 },
			{ "Knight",		{ 12,		6,		7,		4,		11,		8,		9,		3,		6  },	13 },
			{ "Swordsman",		{ 4,		8,		4,		6,		9,		16,		6,		7,		5  },	12 },
			{ "Bandit",		{ 9,		7,		11,		2,		9,		14,		3,		1,		8  },	11 },
			{ "Cleric",		{ 10,		3,		8,		10,		11,		5,		4,		4,		12 },	14 },
			{ "Sorcerer",		{ 5,		6,		5,		12,		3,		7,		8,		14,		4  },	11 },
			{ "Explorer",		{ 7,		6,		9,		7,		6,		6,		12,		5,		5  },	10 },
			{ "Deprived",		{ 6,		6,		6,		6,		6,		6,		6,		6,		6  },	1  },
		}
	},
	{
		"Dark Souls III", "dark3",
		{				"Vigor",	"Attunement",	"Endurance",	"Vitality",	"Strength",	"Dexterity",	"Intelligence",	"Faith",	"Luck" },
		{
			{ "Knight",		{ 12,		10,		11,		15,		13,		12,		9,		9,		7  },	9  },
			{ "Mercenary",		{ 11,		12,		11,		10,		10,		16,		10,		8,		9  },	8  },
			{ "Warrior",		{ 14,		6,		12,		11,		16,		9,		8,		9,		11 },	7  },
			{ "Herald",		{ 12,		10,		9,		12,		12,		11,		8,		13,		11 },	9  },
			{ "Thief",		{ 10,		11,		10,		9,		9,		13,		10,		8,		14 },	5  },
			{ "Assassin",		{ 10,		14,		11,		10,		10,		14,		11,		9,		10 },	10 },
			{ "Sorcerer",		{ 9,		16,		9,		7,		7,		12,		16,		7,		12 },	6  },
			{ "Pyromancer",		{ 11,		12,		10,		8,		12,		9,		14,		14,		7  },	8  },
			{ "Cleric",		{ 10,		14,		9,		7,		12,		8,		7,		16,		13 },	7  },
			{ "Deprived",		{ 10,		10,		10,		10,		10,		10,		10,		10,		10 },	1  },
		}
	},
	{
		"Bloodborne", "blood",
		{				"Vitality",	"Endurance",	"Strength",	"Skill",	"Bloodtinge",	"Arcane" },
		{
			{ "Milquetoast",	{ 11,		10,		12,		10,		9,		8  },	10 },
			{ "Lone Survivor",	{ 14,		11,		11,		10,		7,		7  },	10 },
			{ "Troubled Childhood",	{ 9,		14,		9,		13,		6,		9  },	10 },
			{ "Violent Past",	{ 12,		11,		15,		9,		6,		7  },	10 },
			{ "Professional",	{ 9,		12,		9,		15,		7,		8  },	10 },
			{ "Military Veteran",	{ 10,		10,		14,		13,		7,		6  },	10 },
			{ "Noble Scion",	{ 7,		8,		9,		13,		14,		9  },	10 },
			{ "Cruel Fate",		{ 10,		12,		10,		9,		5,		14 },	10 },
			{ "Waste of Skin",	{ 10,		9,		10,		9,		7,		9  },	4  },
		}
	},
};

static const unordered_map<string_view, const Game *> GAMES_MAP = []()
{
	unordered_map<string_view, const Game *> ret;
	for (const Game &i: GAMES)
		ret[i.abbrev] = &i;
	return ret;
}();

Character levelUp(const Character &c, vector<int> stats)
{
	assert(c.stats.size() == stats.size());

	Character ret(c);

	for (int i = 0; i < (int)c.stats.size(); i++)
	{
		int diff = stats[i] - c.stats[i];
		if (diff > 0)
		{
			ret.stats[i] += diff;
			ret.lvl      += diff;
		}
	}
	return ret;
}

void usage()
{
	cout << "usage: " << "sbc" << " <game> <stats>" << endl;
	for (const Game &game: GAMES)
	{
		cout << "\t" << game.name << ":\t" << game.abbrev;
		for (const string &stat: game.stats)
			cout << " <" << stat << ">";
		cout << endl;
	}
	exit(EXIT_FAILURE);
}

int parseInt(const string &str)
{
	size_t end;
	int n = stoi(str, &end);
	if (n < numeric_limits<int>::min() || n > numeric_limits<int>::max() || end != str.length())
		usage();
	return n;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		usage();

	auto it = GAMES_MAP.find(argv[1]);
	if (it == GAMES_MAP.end())
		usage();

	const Game *game = it->second;

	if (argc != 2 + (int)game->stats.size())
		usage();

	vector<int> desired;
	for (int i = 0; i < (int)game->stats.size(); i++)
		desired.push_back(parseInt(argv[2 + i]));

	vector<Character> candidates;
	for (const Character &base: game->classes)
		candidates.emplace_back(levelUp(base, desired));

	vector<Character> results;
	for (const Character &c1: candidates)
	{
		bool isBad = false;
		for (const Character &c2: candidates)
		{
			if (c1.isWorseThan(c2))
			{
				isBad = true;
				break;
			}
		}
		if (!isBad)
			results.emplace_back(c1);
	}

	for (const Character &c: results)
		cout << c.name << " " << c.lvl << endl;

	return 0;
}
