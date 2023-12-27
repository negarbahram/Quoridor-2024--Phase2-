struct game gameState;

int wallForEachCell[100][100][5];

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

    return 1;
}