
int nextMove, turnSw = 0, invalidInput = 0, moveSw = 0;

typedef enum gameScreen {starting = 0, game, ending} gameScreen;

Vector2 wallStartPoint = {50, 100};
Vector2 wallEndPoint = {50, 100};

void drawInvalid() {
    SetTargetFPS(2);
    Rectangle textBoxSize = {300, 425, 200, 50};
    DrawRectangleRec(textBoxSize, ColorAlpha(MAROON, 0.8));
    DrawText("Invalid Input!", textBoxSize.x + 22, textBoxSize.y + 12, 25, WHITE);

}

void nextMoveProcess(int *turn, struct position *player) {

    switch (nextMove) {
        case 'W':
        case 'w':
            if (! wallForEachCell[(*player).x][(*player).y][0])
                (*player).y--, (*turn) ^= 1;
            else
                invalidInput = 1;
            break;
        case 'S':
        case 's':
            if (! wallForEachCell[(*player).x][(*player).y][2])
                (*player).y++, (*turn) ^= 1;
            else
                invalidInput = 1;
            break;
        case 'A':
        case 'a':
            if (! wallForEachCell[(*player).x][(*player).y][3])
                (*player).x--, (*turn) ^= 1;
            else
                invalidInput = 1;
            break;
        case 'D':
        case 'd':
            if (! wallForEachCell[(*player).x][(*player).y][1])
                (*player).x++, (*turn) ^= 1;
            else
                invalidInput = 1;
            break;
    }

}

void drawBoard(int PlayerSize) {

    BeginDrawing();

    if (! turnSw)
        DrawText(TextFormat("%s's Turn To Move,", gameState.player1Name), 7, 5, 25, ColorAlpha(MAROON, 0.3));
    else
        DrawText(TextFormat("%s's Turn To Move,", gameState.player2Name), 7, 5, 25, ColorAlpha(DARKGREEN, 0.3));

    DrawText("The Arrow Keys In This Game Are w,d,s,a (Lowercase Or Uppercase). You May Use Them To Move Your \nPiece."
             "If You Wish To Place a wall, Press 'space'."
             " - Wall Movements Guide :\n"
             "Press The Mentioned Arrow Keys To Reach Your Intended Location. Press 'x' Or 'X' To Rotate The Wall.\n"
             "In Case Your Unstable Enough That You Have To Change Your Mind, You May Press 'space'.",
             5, 33, 13, ColorAlpha(GRAY, 0.7));

    DrawText("Remaining \nWalls :", 730, 7, 10, ColorAlpha(GRAY, 0.7));
    DrawText(TextFormat("%d", gameState.player1WallNo - gameState.player1UsedWallNo), 740, 40, 20, ColorAlpha(MAROON, 0.3));
    DrawText(TextFormat("%d", gameState.player2WallNo - gameState.player2UsedWallNo), 740, 62, 20, ColorAlpha(DARKGREEN, 0.3));

    Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2 + 50, gameState.player1Pos.y * PlayerSize + PlayerSize / 2 + 100};
    Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2 + 50, gameState.player2Pos.y * PlayerSize + PlayerSize / 2 + 100};

    ClearBackground(RAYWHITE);

    // Print Board :
    Rectangle boardCell = {50, 100, PlayerSize, PlayerSize};

    for (int i = 0; i < gameState.size; i++) {
        boardCell.x = 50;
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
        Vector2 wallStartPoint = {gameState.player1WallList[i].x * PlayerSize + 50, gameState.player1WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player1WallList[i].dir == 'V' || gameState.player1WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    //Print Player 2 walls :
    for (int i = 0; i < gameState.player2UsedWallNo; i++) {
        Vector2 wallStartPoint = {gameState.player2WallList[i].x * PlayerSize + 50, gameState.player2WallList[i].y * PlayerSize + 100};
        Vector2 wallEndPoint = wallStartPoint;
        if (gameState.player2WallList[i].dir == 'V' || gameState.player2WallList[i].dir == 'v')
            wallEndPoint.y += 2 * PlayerSize;
        else
            wallEndPoint.x += 2 * PlayerSize;
        DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
    }

    DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(BLUE, 0.2));

    if (invalidInput)
        drawInvalid();

    EndDrawing();
}

void setWallPos(int PlayerSize) {

    wallStartPoint.y += (gameState.size / 2) * PlayerSize;
    wallEndPoint.x += PlayerSize * 2;
    wallEndPoint.y += (gameState.size / 2) * PlayerSize;

    while (1) {

        nextMove = GetCharPressed();

        if (invalidInput) {
            invalidInput = 0;
            SetTargetFPS(10);
        }

        switch (nextMove) {
            case 'W':
            case 'w':
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y - PlayerSize, wallEndPoint.x))
                    wallStartPoint.y -= PlayerSize, wallEndPoint.y -= PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'S':
            case 's':
                if (wallCanGo(PlayerSize, wallStartPoint.x, wallStartPoint.y + PlayerSize, wallEndPoint.x))
                    wallStartPoint.y += PlayerSize, wallEndPoint.y += PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'D':
            case 'd':
                if (wallCanGo(PlayerSize, wallStartPoint.x + PlayerSize, wallStartPoint.y, wallEndPoint.x + PlayerSize))
                    wallStartPoint.x += PlayerSize, wallEndPoint.x += PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'A':
            case 'a':
                if (wallCanGo(PlayerSize, wallStartPoint.x - PlayerSize, wallStartPoint.y, wallEndPoint.x - PlayerSize))
                    wallStartPoint.x -= PlayerSize, wallEndPoint.x -= PlayerSize;
                else
                    invalidInput = 1;
                break;
            case 'X':
            case 'x':
                if (wallStartPoint.x != wallEndPoint.x) wallStartPoint.x += PlayerSize, wallStartPoint.y -= PlayerSize, wallEndPoint.x -= PlayerSize, wallEndPoint.y += PlayerSize;
                else wallStartPoint.x -= PlayerSize, wallStartPoint.y += PlayerSize, wallEndPoint.x += PlayerSize, wallEndPoint.y -= PlayerSize;
                break;
            case ' ':
                moveSw = 1;
                return;
        }

        if (nextMove == 'l' || nextMove == 'L') {

            if (validWall(PlayerSize, wallStartPoint, wallEndPoint))
                break;
            else
                invalidInput = 1;
        }

        drawBoard(PlayerSize);

    }
}

int whoWins() {
    if (gameState.player1Pos.y == gameState.size - 1)
        return 1;
    if (!gameState.player2Pos.y)
        return 2;
    return 0;
}

void drawEnding(int winner) {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.5));

    if (winner == 1)
        DrawText(TextFormat("%s Won!", gameState.player1Name), 220, 400, 50, WHITE);
    else
        DrawText(TextFormat("%s Won!", gameState.player2Name), 220, 400, 50, WHITE);

    EndDrawing();
}

void drawStarting() {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

    DrawText("Use  'L'  to confirm your input and  'E'  to erase it.", 20, 120, 20, ColorAlpha(GRAY, 1));

    DrawText("Please Enter The Size Of Your Board :", 20, 220, 25, WHITE);

    Rectangle textBoxSize = {525, 218, 50, 30};
    DrawRectangleRec(textBoxSize, WHITE);

    if (!size.isSet) {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(BLUE, 0.4));

        if (size.validLengthEx)
            DrawText("The Size Of The Board Should Be Less Than 100 Units!", 155, 260, 18, ColorAlpha(MAROON, 0.5));
    }
    else {
        if (size.realLength == 1)
            DrawText(size.value, (int) textBoxSize.x + 20, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));
        else
            DrawText(size.value, (int) textBoxSize.x + 13, (int) textBoxSize.y + 7, 20, ColorAlpha(GRAY, 0.7));

        DrawText("Please Enter The Number Of Walls For Each Player :", 20, 300, 25, WHITE);
        Rectangle textBoxWallNo = {700, 298, 50, 30};
        DrawRectangleRec(textBoxWallNo, WHITE);

        if (!wallNo.isSet) {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(BLUE, 0.4));

            if (wallNo.validLengthEx)
                DrawText("The Size Of The Board Should Be Less Than 100 Units!", 300, 340, 18, ColorAlpha(MAROON, 0.5));

        }
        else {
            if (wallNo.realLength == 1)
                DrawText(wallNo.value, (int) textBoxWallNo.x + 20, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));
            else
                DrawText(wallNo.value, (int) textBoxWallNo.x + 13, (int) textBoxWallNo.y + 7, 20, ColorAlpha(GRAY, 0.7));

            DrawText("Please Enter First Player's Name :", 20, 380, 25, WHITE);
            Rectangle textBoxPlayer1Name = {462, 378, 130, 30};
            DrawRectangleRec(textBoxPlayer1Name, WHITE);

            if (!player1Name.isSet) {
                DrawText(player1Name.value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                DrawText("Player's Name Should Only Contain Lowercase English Letters!", 100, 420, 18, ColorAlpha(DARKGREEN, 0.3));

                if (player1Name.validLengthEx)
                    DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 100, 460, 18, ColorAlpha(MAROON, 0.5));
            }
            else {
                DrawText(player1Name.value, (int) textBoxPlayer1Name.x + 13, (int) textBoxPlayer1Name.y + 7, 20, ColorAlpha(GRAY, 0.7));

                DrawText("Please Enter Second Player's Name :", 20, 460, 25, WHITE);
                Rectangle textBoxPlayer2Name = {490, 458, 130, 30};
                DrawRectangleRec(textBoxPlayer2Name, WHITE);

                if (!player2Name.isSet) {
                    DrawText(player2Name.value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20, ColorAlpha(BLUE, 0.4));
                    DrawText("Player's Name Should Only Contain Lowercase English Letters!!", 115, 500, 18, ColorAlpha(DARKGREEN, 0.3));

                    if (player2Name.validLengthEx)
                        DrawText("The Length Of The Player's Name Should Be Less Than 10 Characters!", 115, 540, 18, ColorAlpha(MAROON, 0.5));
                }
                else {
                    DrawText(player2Name.value, (int) textBoxPlayer2Name.x + 13, (int) textBoxPlayer2Name.y + 7, 20,
                             ColorAlpha(GRAY, 0.7));
                    DrawText("Press 'L' To Begin!", 115, 650, 20, ColorAlpha(GRAY, 1));
                }
            }
        }
    }

    EndDrawing();
}

void getString(struct stringInStartingScreen *s) {

    // Write and save string while the player is typing
    while (nextMove > 0) {

        if (nextMove == 'L'&& (*s).realLength) (*s).isSet = 1;

        else if (nextMove >= (*s).validValueS && nextMove <= (*s).validValueE && (*s).realLength < (*s).validLength) {
            (*s).value[(*s).realLength] = (char) nextMove;
            (*s).value[(*s).realLength + 1] = '\0';
            (*s).realLength++;
        }

        else if (nextMove == 'E') {
            (*s).realLength--;
            if ((*s).realLength < 0) (*s).realLength = 0;
            (*s).value[(*s).realLength] = '\0';
            if ((*s).validLengthEx) (*s).validLengthEx = 0;
        }

        else if ((*s).realLength == (*s).validLength)
            (*s).validLengthEx = 1;

        nextMove = GetCharPressed();
    }
}

void graphic() {

    //DrawScreen Related Values :
    int PlayerSize;
    int screenWidth = 800;
    int screenHeight = 810;

    //Setting Input Data To Null Before Reading Them :
    getReadyToRead();

    //Set Default Screen To The Starting Screen :
    gameScreen currentScreen = starting;

    InitWindow(screenWidth, screenHeight, "Quoridor");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        //Update Data And Draw Screen:
        switch (currentScreen) {
            case starting:
                nextMove = GetCharPressed();

                //Read and Save Board Size, Number Of Walls For Each Player And Their Names :
                if (!size.isSet) //User Is Not Done Typing Board Size.
                    getString(&size);
                else { //User Is Done Typing Board Size And Will Now Start Typing The Number Of Walls For Each Player.
                    if (!wallNo.isSet)
                        getString(&wallNo);
                    else {
                        if (!player1Name.isSet)
                            getString(&player1Name);
                        else {
                            if (!player2Name.isSet)
                                getString(&player2Name);
                            else {
                                getStarted(size, wallNo, player1Name, player2Name);

                                // Starting The Real Game :
                                if (nextMove == 'L')
                                    currentScreen = game;
                            }
                        }
                    }
                }
                drawStarting();
                break;

            case game:

                PlayerSize = (screenWidth - 100) / gameState.size;

                if (!whoWins()) {
                    nextMove = GetCharPressed();

                    if (invalidInput) {
                        invalidInput = 0;
                        SetTargetFPS(10);
                    }

                    if (!turnSw) {
                        if (nextMove == ' ') {
                            if (gameState.player1UsedWallNo == gameState.player1WallNo) {
                                invalidInput = 1;
                            } else {
                                setWallPos(PlayerSize);

                                if (!moveSw) {
                                    gameState.player1WallList[gameState.player1UsedWallNo].x =
                                            (wallStartPoint.x - 50) / PlayerSize;
                                    gameState.player1WallList[gameState.player1UsedWallNo].y =
                                            (wallStartPoint.y - 100) / PlayerSize;

                                    if (wallStartPoint.x != wallEndPoint.x)
                                        gameState.player1WallList[gameState.player1UsedWallNo].dir = 'h';
                                    else gameState.player1WallList[gameState.player1UsedWallNo].dir = 'v';

                                    blockCell(gameState.player1WallList[gameState.player1UsedWallNo]);

                                    gameState.player1UsedWallNo++;
                                    turnSw = 1;
                                } else
                                    moveSw = 0;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                            }
                        } else
                            nextMoveProcess(&turnSw, &gameState.player1Pos);
                    }
                    else {
                        if (nextMove == ' ') {
                            if (gameState.player2UsedWallNo == gameState.player2WallNo)
                                invalidInput = 1;
                            else {
                                setWallPos(PlayerSize);

                                if (!moveSw) {
                                    gameState.player2WallList[gameState.player2UsedWallNo].x =
                                            (wallStartPoint.x - 50) / PlayerSize;
                                    gameState.player2WallList[gameState.player2UsedWallNo].y =
                                            (wallStartPoint.y - 100) / PlayerSize;

                                    if (wallStartPoint.x != wallEndPoint.x)
                                        gameState.player2WallList[gameState.player2UsedWallNo].dir = 'h';
                                    else gameState.player2WallList[gameState.player2UsedWallNo].dir = 'v';

                                    blockCell(gameState.player2WallList[gameState.player2UsedWallNo]);

                                    gameState.player2UsedWallNo++;
                                    turnSw = 0;
                                } else
                                    moveSw = 0;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                            }
                        } else
                            nextMoveProcess(&turnSw, &gameState.player2Pos);
                    }
                    drawBoard(PlayerSize);
                }
                else
                    drawEnding(whoWins());
                break;
        }

    }

    CloseWindow();

}