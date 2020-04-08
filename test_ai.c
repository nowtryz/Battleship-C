#include "src/ai.h"
#include "src/types.h"

int main(int argc, char const *argv[]) {
    GameState state = newGameState(1);
    triggerAIturn(&state);
    return 0;
}
