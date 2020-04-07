static int turn = 0;

void asktargetedcell(int player, int* x, int* y)
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

int scan(int player, int target)
{
	char cell[2] = "A1";
	int valid = 1, x, y;
	Boat* scan;

	do{


		printf("\n\n	Coordonnées à scanner (A-J1-10) :\n");
		scanf(" %s", cell);

		parseCoords(cell, &x, &y);

		if(scans[player][x][y] == TRUE)
		{
			printf("\n	Cette case a déjà été scannée !\n\n");
			valid = FALSE;
		}
		if(!checkCell(player, x, y))
		{
			printf("\n	Cette case a déjà été attaquée ou est hors de la grille !\n\n");
			valid = FALSE;
		}
	} while(!valid);

	scans[player][x][y] = TRUE;

	scan = map[target][x][y];

	if(scan == NULL) printf("	Il n'y a rien sur cette case\n");
	else printf("	Vous avez touvé un %s !\n", boatNames[scan->type]);
}

int triggerNewTurn(int player)
{
	
	int coords[2] = {0}, target = (player + 1)%2;
	Boat* attack;

	printf("Joueur %d : à votre tour de jouer >\n", (player + 1));

	//Trigger scan if allowed
	if(turn % 3 == 1)
	{
		printf("	Vous pouvez scanner une case avant de jouer votre tour, vous aurez de nouveau acces à votre carte avant de jouer\n");
		disp(player, TRUE);
		scan(player, target);
	}

	//Trigger attack
	disp(player, TRUE);
	asktargetedcell(player, &coords[0], &coords[1]);
	attack = map[target][coords[0]][coords[1]];

	//Check attack result
	if(attack == NULL){
		actions[player][coords[0]][coords[1]] = FAILED;

		printf("\n\n	A l'eau ! c'est loupé.\n");
	} else {
		actions[player][coords[0]][coords[1]] = TOUCHED;
		attack->cells -= 1;

		if(attack->cells > 0){
			printf("\n\n	Vous avez touché un bateau !\n");
		} else {
			printf("\n\n	Vous avez coulé un %s !\n", boatNames[attack->type]);
		}
	}

	//pause
	getch();

	//returns victory conditions
	return !checkBoats(target);
}

void game()
{
	int win = 0;

	turn = 0;

	printf("\n\nLa partie commence !\n====================\n\n");

	do{
		turn++;

		if(triggerNewTurn(0)){
			printf("\n\nLe joueur 1 gagne la partie !\n");

			win = 1;
		} else if(nplayers > 1 && triggerNewTurn(1)){
			printf("\n\nLe joueur 2 gagne la partie !\n");

			win = 1;
		} /*else if(nplayers == 1 && triggerAIturn()) {
			printf("L'IA gagne la partie !\n");

			win = 1;
		}*/
	} while(win != 1);

	main();
}