#include <stdio.h>
#include "raylib.h"
#include "graphic.c"

void getGame() {

    // Read Size Of The Board :
    scanf("%d", &gameState.size);

    // set Players' Starting Positions :
    gameState.player1Pos.x = 0;
    gameState.player1Pos.y = gameState.size / 2;
    gameState.player2Pos.x = gameState.size - 1;
    gameState.player2Pos.y = gameState.size / 2;

    // Read Player 1 Walls :
    printf("Please Enter The Player 1 Walls Number:\n");
    scanf("%d", &gameState.player1WallNo);
    gameState.player1UsedWallNo = 0;

    // Read Player 2 Walls :
    printf("Please Enter The Player 2 Walls Number:\n");
    scanf("%d", &gameState.player2WallNo);
    gameState.player2UsedWallNo = 0;

}

int NoOneHasWonYet() {
    if (gameState.player1Pos.x == gameState.size - 1)
        return 0;
    if (!gameState.player2Pos.x)
        return 0;
    return 1;
}

int main() {
    getGame();
    graphic();
    return 0;
}

