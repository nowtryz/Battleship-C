#ifndef GAME_H
#define GAME_H

#include "types.h"

void game(tinyint player_count);
bool triggerNewTurn(int player_index, GameState* state);
void scan(Player* player, Player* target);
void asktargetedcell(Player* player, tinyint* x, tinyint* y);

#endif
