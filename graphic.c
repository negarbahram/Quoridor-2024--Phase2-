#include "structures.c"
#include "validwall.c"

int nextMove;

Vector2 wallStartPoint = {0, 0};
Vector2 wallEndPoint = {0, 0};


void invalidInput() {
    Sound Error = LoadSound("errorsound.mp3");
    PlaySound(Error);
}

void nextMoveProcess(int *turn, struct position *player) {

    switch (nextMove) {
        case 'W':
        case 'w':
            if (! wallForEachCell[(*player).x][(*player).y][0])
                (*player).y--, (*turn) ^= 1;
            else
                invalidInput();
            break;
        case 'S':
        case 's':
            if (! wallForEachCell[(*player).x][(*player).y][2])
                (*player).y++, (*turn) ^= 1;
            else
                invalidInput();
            break;
        case 'A':
        case 'a':
            if (! wallForEachCell[(*player).x][(*player).y][3])
                (*player).x--, (*turn) ^= 1;
            else
                invalidInput();
            break;
        case 'D':
        case 'd':
            if (! wallForEachCell[(*player).x][(*player).y][1])
                (*player).x++, (*turn) ^= 1;
            else
                invalidInput();
            break;
    }

}

void drawBoard(int PlayerSize) {

    Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2, gameState.player1Pos.y * PlayerSize + PlayerSize / 2};
    Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2, gameState.player2Pos.y * PlayerSize + PlayerSize / 2};

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

    DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(BLUE, 0.2));

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
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y - PlayerSize, wallEndPoint.x))
                    wallStartPoint.y -= PlayerSize, wallEndPoint.y -= PlayerSize;
                else
                    invalidInput();
                break;
            case 'S':
            case 's':
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y + PlayerSize, wallEndPoint.x))
                    wallStartPoint.y += PlayerSize, wallEndPoint.y += PlayerSize;
                else
                    invalidInput();
                break;
            case 'D':
            case 'd':
                if (wallCanGo(PlayerSize, wallStartPoint.x + PlayerSize, wallStartPoint.y, wallEndPoint.x + PlayerSize))
                    wallStartPoint.x += PlayerSize, wallEndPoint.x += PlayerSize;
                else
                    invalidInput();
                break;
            case 'A':
            case 'a':
                if (wallCanGo(PlayerSize, wallStartPoint.x - PlayerSize, wallStartPoint.y, wallEndPoint.x - PlayerSize))
                    wallStartPoint.x -= PlayerSize, wallEndPoint.x -= PlayerSize;
                else
                    invalidInput();
                break;
            case ' ':
                if (wallStartPoint.x != wallEndPoint.x) wallStartPoint.x += PlayerSize, wallStartPoint.y -= PlayerSize, wallEndPoint.x -= PlayerSize, wallEndPoint.y += PlayerSize;
                else wallStartPoint.x -= PlayerSize, wallStartPoint.y += PlayerSize, wallEndPoint.x += PlayerSize, wallEndPoint.y -= PlayerSize;
                break;
        }

        if (nextMove == 'l' || nextMove == 'L') {
            if (validWall(PlayerSize, wallStartPoint, wallEndPoint))
                break;
            else
                invalidInput();
        }

        drawBoard(PlayerSize);

    }
}

void blockCell(struct wall w) {
    int x = w.x, y = w.y;

    if (w.dir == 'v' || w.dir == 'V') {
        wallForEachCell[x][y][3] = 1;
        wallForEachCell[x][y + 1][3] = 1;
        wallForEachCell[x - 1][y][1] = 1;
        wallForEachCell[x - 1][y + 1][1] = 1;
    }
    else {
        wallForEachCell[x][y][0] = 1;
        wallForEachCell[x + 1][y][0] = 1;
        wallForEachCell[x][y - 1][2] = 1;
        wallForEachCell[x + 1][y - 1][2] = 1;
    }
}

void graphic() {

    int screenWidth = 800;
    int screenHeight = 800;
    int PlayerSize = screenWidth / gameState.size;

    screenWidth = PlayerSize * gameState.size;
    screenHeight = PlayerSize * gameState.size;

    Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2, gameState.player1Pos.y * PlayerSize + PlayerSize / 2};
    Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2, gameState.player2Pos.y * PlayerSize + PlayerSize / 2};

    InitWindow(screenWidth, screenHeight, "Quoridor");
    InitAudioDevice();

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

                    blockCell(gameState.player1WallList[gameState.player1UsedWallNo]);

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

                    blockCell(gameState.player2WallList[gameState.player2UsedWallNo]);

                    gameState.player2UsedWallNo++;

                    wallStartPoint.x = 0, wallStartPoint.y = 0;
                    wallEndPoint.x = 0, wallEndPoint.y = 0;

                    turnSw = 0;
                }
            }
            else
                nextMoveProcess(&turnSw, &gameState.player2Pos);

        Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2, gameState.player1Pos.y * PlayerSize + PlayerSize / 2};
        Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2, gameState.player2Pos.y * PlayerSize + PlayerSize / 2};

        drawBoard(PlayerSize);

    }

    CloseAudioDevice();
    CloseWindow();

}