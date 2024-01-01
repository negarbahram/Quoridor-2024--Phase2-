#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int Mx = 1e4 + 10;

struct game gameState;
int wallForEachCell[100][100][5];

#include "raylib.h"
#include "structures.c"
#include "starting.c"
#include "validwall.c"
#include "graphic.c"


int main() {

    graphic();

    return 0;
}

