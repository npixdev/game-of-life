#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// Fonction pour allouer proprement un tableau 2D
int** allocate_table(int rows, int cols) {
    int** t = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        t[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) t[i][j] = 0;
    }
    return t;
}

// Libération de la mémoire (indispensable pour éviter les fuites)
void free_table(int** t, int rows) {
    for (int i = 0; i < rows; i++) free(t[i]);
    free(t);
}

void random_table(int** table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            table[i][j] = rand() % 2;
        }
    }
}

int load_table(int** table, int rows, int cols, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return -1;

    // On saute les deux premiers nombres (dimensions) qu'on a déjà lus dans le main
    int dummy;
    fscanf(file, "%d %d", &dummy, &dummy);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%d", &table[i][j]) != 1) {
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
    return 0;
}

void game(int** table, int** new_table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    
                    // Monde torique : les bords communiquent
                    int ni = (i + di + rows) % rows;
                    int nj = (j + dj + cols) % cols;

                    if (table[ni][nj] == 1) count++;
                }
            }
            
            // Règles de Conway
            if (table[i][j] == 1) {
                new_table[i][j] = (count == 2 || count == 3);
            } else {
                new_table[i][j] = (count == 3);
            }
        }
    }
}

void print_table(int** table, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(table[i][j] == 1 ? "%c%c" : "  ", 219, 219);
        }
        printf("\n");
    }
}

int main() {
    int rows = 20, cols = 20; // Valeurs par défaut
    int** table = NULL;
    int** new_table = NULL;

    printf("1. Random table\n2. Load from glide.txt\nChoice: ");
    int choice;
    if(scanf("%d", &choice) != 1) return 1;

    if (choice == 2) {
        FILE* file = fopen("glide.txt", "r");
        if (file) {
            fscanf(file, "%d %d", &rows, &cols);
            fclose(file);
        } else {
            printf("File not found, using default 20x20\n");
        }
    }

    table = allocate_table(rows, cols);
    new_table = allocate_table(rows, cols);

    if (choice == 1) random_table(table, rows, cols);
    else load_table(table, rows, cols, "glide.txt");

    system("cls");

    // Cache le curseur Windows
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    while (1) {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(consoleHandle, coord);
        
        print_table(table, rows, cols);
        game(table, new_table, rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][j] = new_table[i][j];
                new_table[i][j] = 0;
            }
        }
        Sleep(50);
    }

    free_table(table, rows);
    free_table(new_table, rows);
    return 0;
}