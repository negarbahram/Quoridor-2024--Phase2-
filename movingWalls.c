#include "Astar.c"

void moveWalls() {

    int screenWidth = 800;
    int screenHeight = 800;
    int PlayerSize = screenWidth / gameState.size;

    InitWindow(screenWidth, screenHeight, "Quoridor");

    Vector2 wallStartPoint = {0, PlayerSize};
    Vector2 wallEndPoint = {PlayerSize * 2, PlayerSize};

    Vector2 Player1 = {gameState.player1Pos.y * PlayerSize + PlayerSize / 2, gameState.player1Pos.x * PlayerSize + PlayerSize / 2};
    Vector2 Player2 = {gameState.player2Pos.y * PlayerSize + PlayerSize / 2, gameState.player2Pos.x * PlayerSize + PlayerSize / 2};

    SetTargetFPS(10);

    while(!WindowShouldClose()) {

        int key = GetCharPressed();

        switch (key) {
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
                if (wallStartPoint.x != wallEndPoint.x) wallStartPoint.x += PlayerSize, wallStartPoint.y += PlayerSize, wallEndPoint.x -= PlayerSize, wallEndPoint.y -= PlayerSize;
                else wallStartPoint.x -= PlayerSize, wallStartPoint.y -= PlayerSize, wallEndPoint.x += PlayerSize, wallEndPoint.y += PlayerSize;
                break;
            case 'B':
            case 'b':
                CloseWindow();
                return;
        }

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
            Vector2 wallStartPoint = {gameState.player1WallList[i].y * PlayerSize, gameState.player1WallList[i].x * PlayerSize};
            Vector2 wallEndPoint = wallStartPoint;
            if (gameState.player1WallList[i].dir == 'V' || gameState.player1WallList[i].dir == 'v')
                wallEndPoint.y += 2 * PlayerSize;
            else
                wallEndPoint.x += 2 * PlayerSize;
            DrawLineEx(wallStartPoint, wallEndPoint, PlayerSize / 8, ColorAlpha(GRAY, 0.7));
        }

        //Print Player 2 walls :
        for (int i = 0; i < gameState.player2UsedWallNo; i++) {
            Vector2 wallStartPoint = {gameState.player2WallList[i].y * PlayerSize, gameState.player2WallList[i].x * PlayerSize};
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

//    CloseWindow();
}