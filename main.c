#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <limits.h>
#include "permutacao.h"
#include "permutacao.c"



int main() {
    int N = 12;
    Menu(N);
    return 0;
}