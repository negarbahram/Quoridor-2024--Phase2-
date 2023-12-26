struct game gameState;
int visit[100 + 5][100 + 5];
int wallForEachCell[100][100][5];

void dfs(int x, int y) {
    visit[x][y] = 1;
    if (x > 0)
        if (!wallForEachCell[x][y][0] && !visit[x - 1][y]) dfs(x - 1, y);
    if (x < gameState.size - 1)
        if (!wallForEachCell[x][y][2] && !visit[x + 1][y]) dfs(x + 1, y);
    if (y > 0)
        if (!wallForEachCell[x][y][3] && !visit[x][y - 1]) dfs(x, y - 1);
    if (y < gameState.size - 1)
        if (!wallForEachCell[x][y][1] && !visit[x][y + 1]) dfs(x, y + 1);
}

int checkHavingPath() {

    //------------- player1 check
    for (int i = 0; i < gameState.size; i++)
        for (int j = 0; j < gameState.size; j++)
            visit[i][j] = 0;

    dfs(gameState.player1Pos.x, gameState.player1Pos.y);

    int swForPlayer1Path = 0;

    for (int i = 0; i < gameState.size; i++)
        if (visit[gameState.size - 1][i]) swForPlayer1Path = 1;

    //---------------- player2 check

    for (int i = 0; i < gameState.size; i++)
        for (int j = 0; j < gameState.size; j++)
            visit[i][j] = 0;

    dfs(gameState.player2Pos.x, gameState.player2Pos.y);

    int swForPlayer2Path = 0;

    for (int i = 0; i < gameState.size; i++)
        if (visit[gameState.size - 1][i]) swForPlayer2Path = 1;

    return swForPlayer1Path && swForPlayer2Path;
}