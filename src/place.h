#ifndef PLACE_H
#define PLACE_H

void placeBoat(Player* player, Boat* boat, tinyint x, tinyint y, direction dir);
bool checkBoatPlace(Player* player, Boat* boat, tinyint x, tinyint y, direction dir);
void askBoatPlace(Player* player, Boat* boat);
void registerPlayerBoats(Player* player);
void place(GameState* state);

#endif
