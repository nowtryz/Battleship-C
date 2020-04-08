#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h> // bool type
typedef char tinyint; // to only use a byte a coords range from 0 to 9

typedef struct Boat {
	int type;
	int cells;
} Boat;

typedef struct GameState {
	int nplayers;
	int win;
	int turn;
	Player* players;
} GameState;

typedef struct Player {
	tinyint id;
	bool** scans;
	char** actions;
	Boat*** map;
	Boat* boats;
} Player;

GameState newGameState(int nplayers);
Player newPlayer(tinyint id);


#endif
