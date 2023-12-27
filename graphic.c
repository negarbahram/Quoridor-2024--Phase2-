#include "structures.c"
//#include "Astar.c"

int nextMove;
struct game gameState;

Vector2 wallStartPoint = {0, 0};
Vector2 wallEndPoint = {0, 0};

void nextMoveProcess(int *turn, struct position *player) {

    switch (nextMove) {
        case 'W':
        case 'w':
            (*player).x--; break;
        case 'S':
        case 's':
            (*player).x++; break;
        case 'A':
        case 'a':
            (*player).y--; break;
        case 'D':
        case 'd':
            (*player).y++; break;
    }

    if (nextMove == 'w' || nextMove == 's' || nextMove == 'a' || nextMove == 'd' || nextMove == 'W' || nextMove == 'S' || nextMove == 'A' || nextMove == 'D')
        (*turn) ^= 1;
}

void drawBoard(int PlayerSize) {

    Vector2 Player1 = {gameState.player1Pos.y * PlayerSize + PlayerSize / 2, gameState.player1Pos.x * PlayerSize + PlayerSize / 2};
    Vector2 Player2 = {gameState.player2Pos.y * PlayerSize + PlayerSize / 2, gameState.player2Pos.x * PlayerSize + PlayerSize / 2};

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Print Board :
    Rectangle boardCell = {0, 0, PlayerSize, PlayerSize};

    for (int i = 0; i < gameState.size; i++) {
        boardCell.x = 0;
        for (int j = 0; j < gameState.size; j++) {
            DrawRectangleLinesEx(boardCell, 1, LIGHTGRAY);
            boardCell.x += PlayerSize;
        }
        boardCell.y += PlayerSize;
    }

    // Print Players :
    DrawCircleV(Player1, 5 * PlayerSize / 12, ColorAlpha(MAROON, 0.3));
    DrawCircleV(Player2, 5 * PlayerSize / 12, ColorAlpha(DARKGREEN, 0.3));

    // Print Player 1 walls :
    for (int i = 0; i < gameState.player1UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player1WallList[i].x * PlayerSize, gameState.player1WallList[i].y * PlayerSize};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player1WallList[i].dir == 'V' || gameState.player1WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    //Print Player 2 walls :
    for (int i = 0; i < gameState.player2UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player2WallList[i].x * PlayerSize, gameState.player2WallList[i].y * PlayerSize};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player2WallList[i].dir == 'V' || gameState.player2WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));

    EndDrawing();
}

void setWallPos(int PlayerSize) {

    wallStartPoint.y += PlayerSize;
    wallEndPoint.x += PlayerSize * 2;
    wallEndPoint.y += PlayerSize;

    while (1) {

        nextMove = GetCharPressed();

        switch (nextMove) {
            case 'W':
            case 'w':
                wallStartPoint.y -= PlayerSize, wallEndPoint.y -= PlayerSize; break;
            case 'S':
            case 's':
                wallStartPoint.y += PlayerSize, wallEndPoint.y += PlayerSize; break;
            case 'D':
            case 'd':
                wallStartPoint.x += PlayerSize, wallEndPoint.x += PlayerSize; break;
            case 'A':
            case 'a':
                wallStartPoint.x -= PlayerSize, wallEndPoint.x -= PlayerSize; break;
            case ' ':
                if (wallStartPoint.x != wallEndPoint.x) wallStartPoint.x += PlayerSize, wallStartPoint.y -= PlayerSize, wallEndPoint.x -= PlayerSize, wallEndPoint.y += PlayerSize;
                else wallStartPoint.x -= PlayerSize, wallStartPoint.y += PlayerSize, wallEndPoint.x += PlayerSize, wallEndPoint.y -= PlayerSize;
                break;
        }

        if (nextMove == 'b') {
            /*if (validWall()) {
                    //
            }
            else {
                    //
            }*/
            break;
        }

        drawBoard(PlayerSize);

    }
}

void graphic() {

    int screenWidth = 800;
    int screenHeight = 800;
    int PlayerSize = screenWidth / gameState.size;

    Vector2 Player1 = {gameState.player1Pos.y * PlayerSize + PlayerSize / 2, gameState.player1Pos.x * PlayerSize + PlayerSize / 2};
    Vector2 Player2 = {gameState.player2Pos.y * PlayerSize + PlayerSize / 2, gameState.player2Pos.x * PlayerSize + PlayerSize / 2};

    InitWindow(screenWidth, screenHeight, "Quoridor");

    int turnSw = 0;

    while (!WindowShouldClose()) {

        nextMove = GetCharPressed();

        if (! turnSw)
            if (nextMove == ' ') {
                if (gameState.player1UsedWallNo == gameState.player1WallNo);
                else {
                    setWallPos(PlayerSize);

                    gameState.player1WallList[gameState.player1UsedWallNo].x = (wallStartPoint.x) / PlayerSize;
                    gameState.player1WallList[gameState.player1UsedWallNo].y = (wallStartPoint.y) / PlayerSize;

                    if (wallStartPoint.x != wallEndPoint.x)
                        gameState.player1WallList[gameState.player1UsedWallNo].dir = 'h';
                    else gameState.player1WallList[gameState.player1UsedWallNo].dir = 'v';

                    gameState.player1UsedWallNo++;

                    wallStartPoint.x = 0, wallStartPoint.y = 0;
                    wallEndPoint.x = 0, wallEndPoint.y = 0;

                    turnSw = 1;
                }
            }
            else
                nextMoveProcess(&turnSw, &gameState.player1Pos);
        else
            if (nextMove == ' ') {
                if (gameState.player2UsedWallNo == gameState.player2WallNo);
                else {
                    setWallPos(PlayerSize);

                    gameState.player2WallList[gameState.player2UsedWallNo].x = (wallStartPoint.x) / PlayerSize;
                    gameState.player2WallList[gameState.player2UsedWallNo].y = (wallStartPoint.y) /PlayerSize;

                    if (wallStartPoint.x != wallEndPoint.x)
                        gameState.player2WallList[gameState.player2UsedWallNo].dir = 'h';
                    else gameState.player2WallList[gameState.player2UsedWallNo].dir = 'v';

                    gameState.player2UsedWallNo++;

                    wallStartPoint.x = 0, wallStartPoint.y = 0;
                    wallEndPoint.x = 0, wallEndPoint.y = 0;

                    turnSw = 0;
                }
            }
            else
                nextMoveProcess(&turnSw, &gameState.player2Pos);

        Vector2 Player1 = {gameState.player1Pos.y * PlayerSize + PlayerSize / 2, gameState.player1Pos.x * PlayerSize + PlayerSize / 2};
        Vector2 Player2 = {gameState.player2Pos.y * PlayerSize + PlayerSize / 2, gameState.player2Pos.x * PlayerSize + PlayerSize / 2};

        drawBoard(PlayerSize);

        if (nextMove == 'Q') {
            CloseWindow();
            return;
        }

    }

   // CloseWindow();

}