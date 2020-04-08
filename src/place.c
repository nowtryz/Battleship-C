#include "constants.h"


void placeBoat(Player* player, Boat* boat, tinyint x, tinyint y, direction dir)
{
	tinyint i;

	if(dir == LEFT)
	{
		x -= BOATSIZE(boat);
		x++;
		dir = RIGHT;
	}

	if(dir == UP)
	{
		y -= BOATSIZE(boat);
		y++;
		dir = DOWN;
	}

	if(dir == RIGHT)
	{
		for(i = x; i < x + BOATSIZE(boat); i++)
		{
			player->map[i][y] = boat;
		}
	}

	if(dir == DOWN)
	{
		for(i = y; i < y + BOATSIZE(boat); i++)
		{
			player->map[x][i] = &boat;
		}
	}
}


bool checkBoatPlace(Player* player, Boat* boat, tinyint x, tinyint y, direction dir)
{
	tinyint i;

	if(dir == LEFT)
	{
		x -= BOATSIZE(boat);
		x++;
		dir = RIGHT;
	}

	if(dir == UP)
	{
		y -= BOATSIZE(boat);
		y++;
		dir = DOWN;
	}

	if(dir == RIGHT)
	{
		for(i = x; i < x + BOATSIZE(boat); i++)
		{
			return checkCell(player, i, y) && player->map[i][y] == NULL;
		}
	}

	if(dir == DOWN)
	{
		for(i = y; i < y + BOATSIZE(boat); i++)
		{
			return checkCell(player, x, i) && player->map[x][i] == NULL;
		}
	}

	return false;
}


void askBoatPlace(Player* player, Boat* boat)
{
	char cell[4] = "A1";
	direction dir;
	tinyint coords[2] = {0};
	bool valid = true;

	do{
		if (!valid) {
			printf("Impossible\n");
		}

		scanflush();

		printf("\nVeuillez entrer les coordonnées puis la direction de votre %s\n", BOATNAME(boat));
		printf("	Coordonnées (A-J1-10) : ");
		scanf(" %s", cell);
		printf("	Direction (fleches directionnelles puis entrer) : ");
		scanf(" %c", &dir);

		valid=(parseCoords(cell, &coords[0], &coords[1]) 
			&& checkCell(player, coords[0], coords[1]) 
			&& checkBoatPlace(player, boat, coords[0], coords[1], dir));
	} while (!valid);

	placeBoat(player, boat, coords[0], coords[1], dir);
	disp(player, false);
}

void registerPlayerBoats(Player* player)
{
	system("clear");

	printf("\n\n\nJoueur %d : placez vos bateaux >\n", player->id);

	Boat boat;
    foreach(boat, player->boats) {
        if (boat.cells > 0) return true;
    }

	// askBoatPlace(player, CARRIER);
	// askBoatPlace(player, CRUISER);
	// askBoatPlace(player, SUBMARINE);
	// askBoatPlace(player, PATROLBOAT);
}

void place(GameState* state)
{
	registerPlayerBoats(&state->players[0]);
	if(state->nplayers > 1)
	{
		getchar();//PAUSE
		registerPlayerBoats(&state->players[1]);
	}
	//else registerAIboats(&state->players[1]);//azpeo'riazeori
}
