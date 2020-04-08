#include "menu.h"
#include "game.h"
#include "place.h"

int main()
{
	tinyint nplayers;

	do {
		nplayers = menu();
		if (nplayers == 0) {
			return 0;
		}

		game(nplayers);
	} while (nplayers != 0);
	
	return 0;
}