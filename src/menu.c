#include "menu.h"

tinyint menu(){
    tinyint choice = 0;
    bool ok = false;

    do{
        printf("  1. Nouvelle partie\n");
        printf("  2. Quitter\n\n");
        printf(">");
        scanf(" %d", &choice);

        switch (choice) {
        case 1:
            ok = true;
            break;
        case 2:
            return 0;
            break;
        default:
            printf("\nWrong choice fucker\n\n");
            ok=0;
            break;
        }
    } while(ok == false);

    //setup the game
    do{
        printf("  1. Un joueur\n");
        printf("  2. Deux joueurs\n");
        printf(">");
        scanf(" %d", &choice);

        switch (choice) {
        case 1:
        case 2:
            return choice;
        default:
            printf("\nWrong choice fucker\n\n");
            break;
        }
    } while(true);

    return 0;
}