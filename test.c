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

int load_table(int table[SIZE][SIZE], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    for (int i = 0; i < SIZE; i++) {
         for (int j = 0; j < SIZE; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (fscanf(file, "%d", &table[i][j]) != 1) {
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
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
            if (table[i][j] == 1) {
                printf("O ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    return 0;
}

int main() {
    system("color 0A");
    int table[SIZE][SIZE] = {0};
    int new_table[SIZE][SIZE] = {0};
    printf("Choose an option:\n1. Random table\n2. Load table from file\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        random_table(table);
    } else {
        load_table(table, "glide.txt");
    }
    while(1) {
        system("cls");
        print_table(table);
        game(table, new_table);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                table[i][j] = new_table[i][j];
                new_table[i][j] = 0;
            }
        }
        Sleep(100);
    }
    return 0;
}

