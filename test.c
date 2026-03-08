#include <stdio.h>
#include <stdlib.h>

int main() {
    int table[20][20] = {0};
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            table[i][j] = rand() % 2;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}

