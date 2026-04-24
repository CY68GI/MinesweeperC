#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_mines_and_counts(int data[10][10]);

int main() {
    int data[10][10] = {{0}};
    char see[10][10] = {{0}};

    srand(time(NULL));

    printf("Minesweeper game\n");

    generate_mines_and_counts(data);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (data[i][j] == -1)
                printf(" M ");
            else
                printf(" % d ", data[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void generate_mines_and_counts(int data[10][10]) {
    const int MineCount = 10;
    int placed = 0;

    while (placed < MineCount) {
        int i = rand() % 10;
        int j = rand() % 10;

        if (data[i][j] != -1)
        {
            data[i][j] = -1;
            placed++;
        }
    }

    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++)
        {
            if (data[r][c] == -1)
                continue;

            for (int dr = -1; dr <= 1; dr++)
            {
                for (int dc = -1; dc <= 1; dc++)
                {
                    int ni = r + dr;
                    int nj = c + dc;
                    if (ni >= 0 && ni < 10 && nj >= 0 && nj < 10)
                    {
                        if (data[ni][nj] == -1)
                        {
                            data[r][c]++;
                        }
                    }
                }
            }
        }
    }
}