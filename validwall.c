#include "aStar.c"

int wallCanGo(int PlayerSize, int xStart, int yStart, int xEnd) {
    xStart /= PlayerSize, yStart /= PlayerSize;
    xEnd /= PlayerSize;
    if (xStart != xEnd)
        return (xStart >= 0 && xStart <= gameState.size - 2 && yStart >= 1 && yStart <= gameState.size - 1);
    else
        return (xStart >= 1 && xStart <= gameState.size - 1 && yStart >= 0 && yStart<= gameState.size - 2);
}

int overLapWall(struct wall newWall) {
    int x = newWall.x, y = newWall.y;
    if (newWall.dir == 'v' || newWall.dir == 'V')
        return (wallForEachCell[x][y][3] || wallForEachCell[x][y + 1][3]);
    else
        return (wallForEachCell[x][y][0] || wallForEachCell[x + 1][y][0]);
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

void unBlockCell(struct wall w) {
    int x = w.x, y = w.y;

    if (w.dir == 'v' || w.dir == 'V') {
        wallForEachCell[x][y][3] = 0;
        wallForEachCell[x][y + 1][3] = 0;
        wallForEachCell[x - 1][y][1] = 0;
        wallForEachCell[x - 1][y + 1][1] = 0;
    }
    else {
        wallForEachCell[x][y][0] = 0;
        wallForEachCell[x + 1][y][0] = 0;
        wallForEachCell[x][y - 1][2] = 0;
        wallForEachCell[x + 1][y - 1][2] = 0;
    }
}

int validWall(int PlayerSize, Vector2 start, Vector2 end) {

    struct wall newWall;

    newWall.x = (start.x) / PlayerSize;
    newWall.y = (start.y) / PlayerSize;

    if (start.x != end.x)
        newWall.dir = 'h';
    else
        newWall.dir = 'v';

    if (overLapWall(newWall))
        return 0;

    blockCell(newWall);

    if (!aStarAlgorithm(gameState.player1Pos, gameState.size - 1)) {
        unBlockCell(newWall);
        return 0;
    }
    if (!aStarAlgorithm(gameState.player2Pos, 0)) {
        unBlockCell(newWall);
        return 0;
    }

    return 1;
}