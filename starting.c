struct stringInStartingScreen size, wallNo, player1Name, player2Name;

void setWallaroundTheBoard() {

    memset(wallForEachCell, 0, sizeof wallForEachCell);

    for (int i = 0; i < gameState.size; i++) {
        wallForEachCell[i][0][0] = 1;
        wallForEachCell[i][gameState.size - 1][2] = 1;
        wallForEachCell[0][i][3] = 1;
        wallForEachCell[gameState.size - 1][i][1] = 1;
    }
}

void setNull(struct stringInStartingScreen *s) {
    (*s).realLength = 0, (*s).isSet = 0, (*s).validLengthEx = 0, (*s).value[0] = '\0';
}

void getReadyToRead() {

    setNull(&size); size.validLength = 2, size.validValueS = '0', size.validValueE = '9';
    setNull(&wallNo); wallNo.validLength = 2, wallNo.validValueS = '0', wallNo.validValueE = '9';
    setNull(&player1Name); player1Name.validLength = 10, player1Name.validValueS = 'a', player1Name.validValueE = 'z';
    setNull(&player2Name); player2Name.validLength = 10, player2Name.validValueS = 'a', player2Name.validValueE = 'z';

}

void getStarted(struct stringInStartingScreen size, struct stringInStartingScreen wallNo, struct stringInStartingScreen player1Name, struct stringInStartingScreen player2Name) {

    gameState.size = atoi(size.value);

    gameState.player1WallNo = atoi(wallNo.value);
    gameState.player2WallNo = atoi(wallNo.value);

    strcpy(gameState.player1Name, player1Name.value);
    strcpy(gameState.player2Name, player2Name.value);

    // set Players' Starting Positions :
    gameState.player1Pos.y = 0;
    gameState.player1Pos.x = gameState.size / 2;
    gameState.player2Pos.y = gameState.size - 1;
    gameState.player2Pos.x = gameState.size / 2;

    gameState.player1UsedWallNo = 0;

    gameState.player2UsedWallNo = 0;

    setWallaroundTheBoard();

}
