#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define SIZE 20

int random_table(int table[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            table[i][j] = rand() % 2;
        }
    }
    return 0;
}

int game(int table[SIZE][SIZE], int new_table[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int count = 0;
            for (int di = -1; di < 2; di++) {
                for (int dj = -1; dj <2; dj++) {
                    if (di == 0 && dj == 0) {
                        continue;
                    }
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
                        if (table[ni][nj] == 1) {
                            count++;
                        }
                    }
                }
            }
            if (table[i][j] == 1 && (count == 2  || count ==3)) {
                new_table[i][j] = 1;
            } else if (table[i][j] == 1 && (count <2 || count > 3)) {
                new_table[i][j] = 0;
            } else if (table[i][j] == 0 && count == 3) {
                new_table[i][j] = 1;
            }
        }
    }
}

int print_table(int table[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    int table[SIZE][SIZE] = {0};
    int new_table[SIZE][SIZE] = {0};
    random_table(table);
    while (1) {
        system("cls");
        game(table, new_table);
        print_table(new_table);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                table[i][j] = new_table[i][j];
            }
            for (int j = 0; j < SIZE; j++) {
                new_table[i][j] = 0;
            }
        }
        Sleep(1000);
    }
    return 0;
}

