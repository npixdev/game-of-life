#include <stdio.h>
#include <stdlib.h>

int random_table(int table[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            table[i][j] = rand() % 2;
        }
    }
    return 0;
}

int game(int table[20][20], int new_table[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            int count = 0;
            for (int di = -1; di < 2; di++) {
                for (int dj = -1; dj <2; dj++) {
                    if (di == 0 && dj == 0) {
                        continue;
                    }
                    if (table[i+di][j+dj] == 1) {
                        count++;
                    }
                }
            }
            if (table[i][j] == 1 && count == 2  || count ==3) {
                new_table[i][j] = 1;
            } else if (table[i][j] == 1 && count <2 || count > 3) {
                new_table[i][j] == 0;
            } else if (table[i][j] == 0 && count == 3) {
                new_table[i][j] = 1;
            }
        }
    }
}

int print_table(int table[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    int table[20][20] = {0};
    int new_table[20][20] = {0};
    random_table(table);
    game(table, new_table);
    print_table(new_table);
    return 0;
}

