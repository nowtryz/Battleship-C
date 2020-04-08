#ifndef AI_H
#define AI_H

#include "types.h"
#include "constants.h"

void placeAIboat(Boat* boat);
void registerAIboats(Player* ai);
bool triggerAIturn(GameState* state);


static int random(int max);
static void randomCoords(int * coords);
static void push(int *coords, char res);
static void getTarget(tinyint coords[], Player* ai);

#endif
