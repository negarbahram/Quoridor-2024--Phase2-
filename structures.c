struct position {
    int x, y;
};

struct wall {
    char dir;
    int x, y;
};

struct game {
    int size;
    struct position player1Pos, player2Pos;
    int player1WallNo;
    int player1UsedWallNo;
    int player2WallNo;
    int player2UsedWallNo;
    struct wall player1WallList[100 + 10];
    struct wall player2WallList[100 + 10];
};
