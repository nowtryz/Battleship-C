#include "types.h"
#include "constants.h"

GameState newGameState(tinyint nplayers) {
    Player players[2] = {newPlayerSate(1), newPlayerSate(2)};

    GameState state = {
        .nplayers = nplayers,
        .win = 0,
        .turn = 0,
        .players = players,
    };

    return state;
}

Player newPlayerSate(tinyint id) {
    bool scans[10][10] = {{{ false }}};
    action actions[10][10] = {{{ NONE }}};
    Boat* map[10][10] = {{{ NULL }}};
    Boat boats[BOATCOUNT] = INITIALBOATS;

    Player state = {
        .id = id,
        .scans = scans,
        .actions = actions,
        .map = map,
        .boats = boats,
    };

    return state;
}