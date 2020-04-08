#include "display.h"
#include "constants.h"
#include "coloring.h"

void dispMap(Player* player){
    tinyint x, y;

    for (y=0; y<10; y++){
        for (x=0; x<10; x++){
            if(player->map[x][y] == NULL) printw("%c ", NONE);
            else printw("%c ", getMapChar(player, x, y));
        }
        printw("\n");
    }
    printw("\n\n");
}

void dispActions(Player* player){
    int x, y;
    
    for (y=0; y<10; y++){
        for (x=0; x<10; x++){
            printw("%c ", player->actions[x][y]);
        }
        printw("\n");
    }
    printw("\n\n");
}

void dispHeader()
{
    printw("          Votre adversaire :                              Vos bateaux :\n");
    printw("           \\ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|     \\ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10|\n");
    printw("          ---+---+---+---+---+---+---+---+---+---+---+    ---+---+---+---+---+---+---+---+---+---+---+\n");
}

void dispLineBreak()
{
    printw("          ---+---+---+---+---+---+---+---+---+---+---+    ---+---+---+---+---+---+---+---+---+---+---+\n");
}

void disp(Player* player, bool block)
{
    char c;
    int x, y;

    if(block) getchar();//PAUSE

    textcolor(LIGHTBLUE);

    printw("          Joueur %d :\n          ==========\n\n", player+1);

    dispHeader();

    for(y=0; y < 10; y++)
    {
        printw("           %c |", y + 'A');

        for(x=0; x < 10; x++)
        {
            c = getActionsChar(player, x, y);

            if(c == TOUCHED) textcolor(RED);
            if(c == FAILED)  textcolor(WHITE);
            if(c > '0' && c <= '9') textcolor(GREEN);

            printw(" %c ", c);

            textcolor(LIGHTBLUE);
            printw("|");
        }

        printw("     %c |", y + 'A');

        for(x=0; x < 10; x++)
        {
            c = getMapChar(player, x, y);

            if(c == TOUCHED)        textcolor(RED);
            if(c == FAILED)         textcolor(WHITE);
            if(c > '0' && c <= '9') textcolor(GREEN);

            printw(" %c ", c);

            textcolor(LIGHTBLUE);
            printw("|");
        }

        printw("\n");
        dispLineBreak();
    }
    

    refresh();
    getch();
    color_reset();
}