/**
 * description
 */
int parseCoords(char* chain, int* x, int* y)
{
	int result = 1;

	if(chain[2] == '0')
	{
		if(chain[1] == '1') *x = 9;
		else result = 0;
	} else {
		if(chain[1] > '0' && chain[1] <= '9') *x = chain[1] - '1';
		else result = 0;
	}

	if     (chain[0] >= 'A' && chain[0] <= 'Z') *y = chain[0] - 'A';
	else if(chain[0] >= 'a' && chain[0] <= 'z') *y = chain[0] - 'a';
	else result = 0;

	return result;
}

int checkCell(int player, int x, int y)
{
	return (x >= 0 
		&& y >= 0
		&& x < 10
		&& y < 10
		&& actions[player][x][y] == NONE);
}

int checkBoats(int player)
{
	return (boats[player][CARRIER].cells > 0 
		|| boats[player][CRUISER].cells > 0 
		|| boats[player][SUBMARINE].cells > 0 
		|| boats[player][TORPEDOBOAT].cells > 0);
}

char getMapChar(int player, int x, int y)
{
	int target = (player + 1) % 2;

	char action = actions[target][x][y];
	Boat* boat = map[player][x][y];

	if(action != NONE) return action;
	if(boat != NULL) return boatLength[boat->type] + '0';

	return NONE;
}

char getActionsChar(int player, int x, int y)
{
	int target = (player + 1) % 2;

	char action = actions[player][x][y];
	int scan = scans[player][x][y];
	Boat* boat = scans[player][x][y] == TRUE ? map[target][x][y] : NULL;

	if(action != NONE) return action;
	if(scan == TRUE)
	{
		if(boat != NULL) return boatLength[boat->type] + '0';
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
void fillStorage()
{
	Boat boat = {0, 5};
	int i, j, x, y;

	for(i=0; i<2; i++)
	{
		for(x=0; x<10; x++)
		{
			for(y=0; y<10; y++)
			{
				actions[i][x][y] = NONE;
				map[i][x][y] = NULL;
				scans[i][x][y] = FALSE;
			}
		}
	}
	
	for(j=0; j < 4; j++)
	{
		boat.type = j;
		boat.cells = boatLength[j];
		boats[0][j] = boat;
		boats[1][j] = boat;
	}
}