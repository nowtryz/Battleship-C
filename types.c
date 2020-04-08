#include "types.h"
#include "constants.h"

GameState newGameState(int nplayers) {
    PlayerState players[2] = {newPlayerSate(), newPlayerSate()};

    GameState state = {
        .nplayers = nplayers,
        .win = 0,
        .turn = 0,
        .players = players,
    };

    return state;
}

PlayerState newPlayerSate() {
    bool scans[10][10] = {{{FALSE}}};
    char actions[10][10] = {{{NONE}}};
    Boat* map[10][10] = {{{NULL}}};
    Boat boats[BOATCOUNT] = INITIALBOATS;

    PlayerState state = {
        .scans = scans,
        .actions = actions,
        .map = map,
        .boats = boats,
    };

    return state;
}