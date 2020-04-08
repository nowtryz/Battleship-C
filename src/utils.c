#include "utils.h" // also include types.h
#include "constants.h"

bool parseCoords(char* chain, tinyint* x, tinyint* y)
{
    // test 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    if(chain[1] >= '0' && chain[2] != '0' && chain[1] <= '9') *x = chain[1] - '1';
    // test 10
    else if (chain[1] == '1' && chain[2] == '0') *x = 9;
    else return false;

	if     (chain[0] >= 'A' && chain[0] <= 'J') *y = chain[0] - 'A';
	else if(chain[0] >= 'a' && chain[0] <= 'j') *y = chain[0] - 'a';
	else return false;

	return true;
}

bool checkBoats(Boat boats[])
{
    Boat boat;
    foreach(boat, boats) {
        if (boat.cells > 0) return true;
    }
	//return (player->boats[CARRIER].cells > 0 
	//	|| boats[player][CRUISER].cells > 0 
	//	|| boats[player][SUBMARINE].cells > 0 
	//	|| boats[player][PATROLBOAT].cells > 0);
}

int checkCell(Player* player, tinyint x, tinyint y)
{
	return (x >= 0 
		&& y >= 0
		&& x < 10
		&& y < 10
		&& player->actions[x][y] == NONE);
}

char getMapChar(Player* player, Player* target, int x, int y)
{
	action action = target->actions[x][y];
	Boat* boat = player->map[x][y];

	if(action != NONE) return action;
	if(boat != NULL) return BOATSIZE(boat) + '0';

	return NONE;
}

char getActionsChar(Player* player, Player* target, int x, int y)
{
	action action = player->actions[x][y];
	bool scan = player->scans[x][y];
	Boat* boat = scan == true ? target->map[x][y] : NULL;

	if(action != NONE) return action;
	if(scan == true)
	{
		if(boat != NULL) return BOATSIZE(boat) + '0';
		else             return SCANNED;
	}

	return NONE;
}

void scanflush()
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

//flemme du dimanche...
void fillStorage(GameState* state)
{
	Boat boat = {0, 5};
    Player* player;
	int i, j, x, y;

	for(i=0; i<2; i++)
	{
        player = &state->players[i];
        //player->boats = INITIALBOATS;
		for(x=0; x<10; x++)
		{
			for(y=0; y<10; y++)
			{
				player->actions[x][y] = NONE;
				player->map[x][y] = NULL;
				player->scans[x][y] = false;
			}
		}
	}
}
