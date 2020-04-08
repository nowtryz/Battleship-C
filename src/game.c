#include "game.h"
#include "constants.h"
#include "place.h"

void game(tinyint player_count)
{
	GameState state = newGameState(player_count);

	place(&state);

	printf("\n\nLa partie commence !\n====================\n\n");

	do{
		state.turn++;

		if(triggerNewTurn(0, &state)){
			printf("\n\nLe joueur 1 gagne la partie !\n");

			state.win = 1;
		} else if(state.nplayers > 1 && triggerNewTurn(1, &state)){
			printf("\n\nLe joueur 2 gagne la partie !\n");

			state.win = 1;
		} /*else if(nplayers == 1 && triggerAIturn(&state)) {
			printf("L'IA gagne la partie !\n");

			win = 1;
		}*/
	} while(state.win != 1);
}

bool triggerNewTurn(tinyint player_index, GameState* state)
{
	tinyint coords[2] = {0};
    Player* target = &state->players[(player_index + 1)%2];;
    Player* player = &state->players[player_index];
	Boat* attack;

	printf("Joueur %d : à votre tour de jouer >\n", player->id);

	//Trigger scan if allowed
	if(state->turn % 3 == 1)
	{
		printf("	Vous pouvez scanner une case avant de jouer votre tour, vous aurez de nouveau acces à votre carte avant de jouer\n");
		disp(player, true);
		scan(player, target);
	}

	//Trigger attack
	disp(player, true);
	asktargetedcell(player, &coords[0], &coords[1]);
	attack = target->map[coords[0]][coords[1]];

	//Check attack result
	if(attack == NULL){
		player->actions[coords[0]][coords[1]] = FAILED;

		printf("\n\n	A l'eau ! c'est loupé.\n");
	} else {
		player->actions[coords[0]][coords[1]] = TOUCHED;
		attack->cells -= 1;

		if(attack->cells > 0){
			printf("\n\n	Vous avez touché un bateau !\n");
		} else {
			printf("\n\n	Vous avez coulé un %s !\n", BOATNAME(attack));
		}
	}

	//pause
	getch();

	//returns victory conditions
	return !checkBoats(target);
}

void scan(Player* player, Player* target)
{
	char cell[3] = "A1";
	int valid = 1, x, y;
	Boat* scan;

	do{


		printf("\n\n	Coordonnées à scanner (A-J1-10) :\n");
		scanf(" %s", cell);

		parseCoords(cell, &x, &y);

		if(player->scans[x][y] == true)
		{
			printf("\n	Cette case a déjà été scannée !\n\n");
			valid = false;
		}
		if(!checkCell(player, x, y))
		{
			printf("\n	Cette case a déjà été attaquée ou est hors de la grille !\n\n");
			valid = false;
		}
	} while(!valid);

	player->scans[x][y] = true;

	scan = target->map[x][y];

	if(scan == NULL) printf("	Il n'y a rien sur cette case\n");
	else printf("	Vous avez touvé un %s !\n", BOATNAME(scan));
}

void asktargetedcell(Player* player, tinyint* x, tinyint* y)
{
	char cell[2] = "A1";
	int valid = 1;

	do{
		if(!valid) printf("\n	Cette case a déjà été attaquée !\n\n");

		printf("\n\n	Coordonnées à attaquer (A-J1-10) :\n");
		scanf(" %s", cell);

		parseCoords(cell, x, y);

		valid = checkCell(player,*x, *y);
	} while(!valid);
}
