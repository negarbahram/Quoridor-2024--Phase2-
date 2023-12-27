#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int Mx = 1e4 + 10;

struct game gameState;
int wallForEachCell[100][100][5];


#include "raylib.h"
#include "graphic.c"

void getGame() {

    // Read Size Of The Board :
    scanf("%d", &gameState.size);

    // set Players' Starting Positions :
    gameState.player1Pos.y = 0;
    gameState.player1Pos.x = gameState.size / 2;
    gameState.player2Pos.y = gameState.size - 1;
    gameState.player2Pos.x = gameState.size / 2;

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

/*
 * up = 0
 * right = 1
 * down = 2
 * left = 3
 */

void setWallaroundTheBoard() {
    for (int i = 0; i < gameState.size; i++) {
        wallForEachCell[i][0][0] = 1;
        wallForEachCell[i][gameState.size - 1][2] = 1;
        wallForEachCell[0][i][3] = 1;
        wallForEachCell[gameState.size - 1][i][1] = 1;
    }
}

int main() {
    memset(wallForEachCell, 0, sizeof wallForEachCell);
    getGame();
    setWallaroundTheBoard();
    graphic();
    return 0;
}

