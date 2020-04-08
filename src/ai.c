#include "ai.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//radomize
static int random(int max) {
    srand(time(NULL)); //init rand()
    return rand()%max;
}


static void randomCoords(int * coords) {
    coords[X] = random(9);
    coords[Y] = random(9);
}

//lastHit queu setup
typedef enum State { None, Touched, Sunk } State;
typedef enum Unknown { X, Y, RESULT } Unknown;
static State lastHit[2][3];


void placeAIboat(Boat* boat)
{
    int weakcoord, strocoord, dir;
    int x,y;
    bool valid = false;

    do
    {
      weakcoord = random(10 - BOATSIZE(boat));
      strocoord = random(10);
      dir       = random(2);

      if(dir == 0 && checkBoatPlace(1, boat, weakcoord, strocoord, RIGHT))
      {
          placeBoat(1, boat, weakcoord, strocoord, RIGHT);
      }
      else if (checkBoatPlace(1, boat, strocoord, weakcoord, DOWN))
      {
          placeBoat(1, boat, strocoord, weakcoord, DOWN);
      }
    } while(!valid);


    //debug
    printf(
      "%s placé en (%d,%d) direction %s\n", 
      BOATNAME(boat), dir == 0 ? weakcoord : strocoord, 
      dir == 0 ? strocoord : weakcoord, 
      dir == 0 ? "droite" : "bas"
    );
}

void registerAIboats(Player* ai)
{
  Boat boat;
  foreach(boat, ai->boats) {
      if (boat.cells > 0) return true;
  }

	// placeAIboat(player, CARRIER);
	// placeAIboat(player, CRUISER);
	// placeAIboat(player, SUBMARINE);
	// placeAIboat(player, PATROLBOAT);
}


static void push(int *coords, State res){
  if(res == None) {

    lastHit[0][X] = coords[X];
    lastHit[0][Y] = coords[Y];
    lastHit[0][RESULT] = res;

  } else if (res == TOUCHED) {

    lastHit[1][X] = lastHit[0][X];
    lastHit[1][Y] = lastHit[0][Y];
    lastHit[1][RESULT] = lastHit[0][RESULT];

    lastHit[0][X] = coords[X];
    lastHit[0][Y] = coords[Y];
    lastHit[0][RESULT] = res;

  } else if (res == Sunk) {

    lastHit[1][X] = 0;
    lastHit[1][Y] = 0;
    lastHit[1][RESULT] = 0;

    lastHit[0][X] = 0;
    lastHit[0][Y] = 0;
    lastHit[0][RESULT] = 0;

  }
}

static void getTarget(tinyint coords[], Player* ai) {
  static int dir=0, nhited=0;
  int i;

  if (lastHit[0][RESULT] == Sunk) {

    nhited=0;

  } else if (lastHit[0][RESULT] == Touched) {

    //touched last turn
    nhited++;

  } else if (lastHit[0][RESULT] == None && lastHit[1][RESULT] == Touched) {

    //ai found a boat last turn, trying cells around
    dir = (dir+1)%4;

  } else if (lastHit[0][RESULT] == None && nhited>1){

    //end of the boat, turn back
    dir = (dir+2)%4;

    //reset coords at the first hit
    if ( lastHit[0][X] == lastHit[1][X]) {

      if (dir == 0){
        for (i=coords[X]; i< 10; i++) {
           if (ai->actions[coords[i]][coords[Y]] == NONE){
             coords[X] = i;
             break;
           }
        }
      } else if (dir == 2) {
        for (i=coords[X]; i>0; i--) {
           if (ai->actions[coords[i]][coords[Y]] == NONE){
             coords[X] = i;
             break;
           }
        }
      }

    } else if ( lastHit[0][Y] == lastHit[1][Y]) {

      if (dir == 1){
        for (i=coords[Y]; i< 10; i++) {
           if (ai->actions[coords[X]][coords[i]] == NONE){
             coords[Y] = i;
             break;
           }
        }
      } else if (dir == 3) {
        for (i=coords[Y]; i>0; i--) {
           if (ai->actions[coords[X]][coords[i]] == NONE){
             coords[Y] = i;
             break;
           }
        }
      }

    }

  } else {

    randomCoords(coords);
    return;
  }

  switch (dir) { //TODO: check played cells
    case 0: //right
      if (coords[Y]+1 > 0)
        coords[Y]++;
      break;
    case 1: //down
      if (coords[X]+1 > 0)
        coords[X]++;
      break;
    case 2: //left
      if (coords[Y]-1 > 0)
        coords[Y]--;
      break;
    case 3: //up
      if (coords[X]-1 > 0)
        coords[X]--;
      break;
    default:
      printf("AI fucked up... $dir not found\n");
  }

  return;
}

bool triggerAIturn(GameState* state)
{
  Player* ai = &state->players[1];
  Player* target = &state->players[0];
  tinyint coords[2] = {0};
  direction dir = 0;
  Boat* attack;

  dir = random(4);

  getTarget(coords, ai); //TODO : check played cells
  printf("L'IA attaque la case %d%d\n", coords[0], coords[1]);

  attack = target->map[coords[X]][coords[Y]];

	if(attack == NULL){
		ai->map[coords[X]][coords[Y]] = FAILED;
    push(coords, FAILED);
	} else {
		ai->actions[coords[X]][coords[Y]] = TOUCHED;
		attack->cells -= 1;

		if(attack->cells > 0){
			printf("\n	Bateau touché !\n");
      push(coords, TOUCHED);
		} else {
			printf("\n %s coulé !\n", BOATNAME(attack));
      push(coords, Sunk);
		}
	}

	return !checkBoats(target);
}
