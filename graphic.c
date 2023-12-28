int nextMove, turnSw = 0;

typedef enum gameScreen {starting = 0, game, ending} gameScreen;

Vector2 wallStartPoint = {50, 100};
Vector2 wallEndPoint = {50, 100};

void invalidInput() {
    Sound Error = LoadSound("resources/errorsound.wav");
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

    BeginDrawing();

    if (! turnSw)
        DrawText(TextFormat("%s's Turn To Move,", gameState.player1Name), 60, 10, 30, ColorAlpha(MAROON, 0.3));
    else
        DrawText(TextFormat("%s's Turn To Move,", gameState.player2Name), 60, 10, 30, ColorAlpha(DARKGREEN, 0.3));

    DrawText("The Arrow Keys In This Game Are w,d,s,a (Lowercase Or Uppercase).You May Use Them To Move Your Piece.\n "
             "If You Wish To Place a wall, Press 'space' And Then Use The Arrow Keys To Reach Your Intended location.",
             60, 50, 13, ColorAlpha(GRAY, 0.7));

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

    DrawText(TextFormat("Player %i Won!", winner), 220, 400, 50, WHITE);

    EndDrawing();
}

void drawStating() {

    BeginDrawing();

    ClearBackground(ColorAlpha(LIGHTGRAY, 0.7));

    DrawText("Use  'l'  or  'L'  to confirm your input and  'e'  or  'E'  to erase it.", 20, 120, 20, ColorAlpha(GRAY, 1));

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
                    DrawText("Press 'l' or 'L' To Begin!", 115, 650, 20, ColorAlpha(GRAY, 1));
                }
            }
        }
    }

    EndDrawing();

}

void getString(struct stringInStartingScreen *s) {

    while (nextMove > 0) {

        if (nextMove == 'l' || nextMove == 'L') (*s).isSet = 1;

        else if (nextMove >= (*s).validValueS && nextMove <= (*s).validValueE && (*s).realLength < (*s).validLength) {
            (*s).value[(*s).realLength] = (char) nextMove;
            (*s).value[(*s).realLength + 1] = '\0';
            (*s).realLength++;
        }

        else if (nextMove == 'e' || nextMove == 'E') {
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
    int screenHeight = 800;

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
                else { //User Is Done Typing Board Size And Will Now Start Typing The Number Of walls For Each Player.
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

                                if (nextMove == 'l' || nextMove == 'L')
                                    currentScreen = game;
                            }
                        }
                    }
                }
                drawStating();
                break;
            case game:

                PlayerSize = (screenWidth - 100) / gameState.size;
                Vector2 Player1 = {gameState.player1Pos.x * PlayerSize + PlayerSize / 2 + 50,
                                   gameState.player1Pos.y * PlayerSize + PlayerSize / 2 + 100};
                Vector2 Player2 = {gameState.player2Pos.x * PlayerSize + PlayerSize / 2 + 50,
                                   gameState.player2Pos.y * PlayerSize + PlayerSize / 2 + 100};

                if (!whoWins()) {
                    nextMove = GetCharPressed();

                    if (!turnSw)
                        if (nextMove == ' ') {
                            if (gameState.player1UsedWallNo == gameState.player1WallNo) {
                                invalidInput();
                            } else {
                                setWallPos(PlayerSize);

                                gameState.player1WallList[gameState.player1UsedWallNo].x =
                                        (wallStartPoint.x - 50) / PlayerSize;
                                gameState.player1WallList[gameState.player1UsedWallNo].y =
                                        (wallStartPoint.y - 100) / PlayerSize;

                                if (wallStartPoint.x != wallEndPoint.x)
                                    gameState.player1WallList[gameState.player1UsedWallNo].dir = 'h';
                                else gameState.player1WallList[gameState.player1UsedWallNo].dir = 'v';

                                blockCell(gameState.player1WallList[gameState.player1UsedWallNo]);

                                gameState.player1UsedWallNo++;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                                turnSw = 1;
                            }
                        } else
                            nextMoveProcess(&turnSw, &gameState.player1Pos);
                    else if (nextMove == ' ') {
                        if (gameState.player2UsedWallNo == gameState.player2WallNo);
                        else {
                            setWallPos(PlayerSize);

                            gameState.player2WallList[gameState.player2UsedWallNo].x = (wallStartPoint.x - 50) / PlayerSize;
                            gameState.player2WallList[gameState.player2UsedWallNo].y = (wallStartPoint.y - 100) / PlayerSize;

                            if (wallStartPoint.x != wallEndPoint.x)
                                gameState.player2WallList[gameState.player2UsedWallNo].dir = 'h';
                            else gameState.player2WallList[gameState.player2UsedWallNo].dir = 'v';

                            blockCell(gameState.player2WallList[gameState.player2UsedWallNo]);

                            gameState.player2UsedWallNo++;

                            wallStartPoint.x = 50, wallStartPoint.y = 100;
                            wallEndPoint.x = 50, wallEndPoint.y = 100;

                            turnSw = 0;
                        }
                    } else
                        nextMoveProcess(&turnSw, &gameState.player2Pos);
                    drawBoard(PlayerSize);
                }
                else
                    drawEnding(whoWins());
                break;
        }

    }
    CloseAudioDevice();
    CloseWindow();

}