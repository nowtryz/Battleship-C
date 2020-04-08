#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/**
 * description
 */
bool parseCoords(char* chain, tinyint* x, tinyint* y);
int checkCell(Player* player, tinyint x, tinyint y);
bool checkBoats(Boat boats[]);
char getMapChar(Player* player, Player* target, int x, int y);
char getActionsChar(Player* player, Player* target, int x, int y);
void scanflush();
void fillStorage();

#endif
