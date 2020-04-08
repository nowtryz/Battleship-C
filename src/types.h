#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h> // bool type
typedef char tinyint; // to only use a byte a coords range from 0 to 9
typedef char direction;
typedef char action;

typedef struct Boat {
	tinyint type;
	tinyint cells;
} Boat;

typedef struct GameState {
	tinyint nplayers;
	tinyint win;
	int turn;
	Player* players;
} GameState;

typedef struct Player {
	tinyint id;
	bool** scans;
	action** actions;
	Boat*** map;
	Boat* boats;
} Player;

GameState newGameState(tinyint nplayers);
Player newPlayer(tinyint id);


#endif
