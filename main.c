#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_mines_and_counts(int data[10][10]);
void input(int data[10][10], char see[10][10]);
int win_or_loss(int x, int y, char choice, int data[10][10], char see[10][10]);

int main() {
    int data[10][10] = {{0}};
    char see[10][10];
    int i, j;

    srand(time(NULL));
    
    generate_mines_and_counts(data);


    printf("扫雷游戏\n");
    printf("游戏操作提示: O=翻开格子; P=插旗（标记为雷）; #=取消插旗\n");
    printf("坐标范围为1 < x < 10; 1 < y < 10\n");

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            see[i][j] = '#';
        }
    }

    printf("    ");
    for (j = 0; j < 10; j++) {
        printf("%3d ", j + 1);
    }
    printf("\n");

    printf("    ");
    for (j = 0; j < 10; j++) {
        printf("----");
    }
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%3d |", i + 1);
        for (j = 0; j < 10; j++) {
            printf("%3c ", see[i][j]);
        }
        printf("\n");
    }

    printf("请输入坐标(x y)和操作(O、P、#)[示例: 1 1 O]:");

    input(data, see);

/*     do {
        scanf("%d %d %c", &x, &y, &choice);
        x = x - 1;
        y = y - 1;
        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            printf("坐标超出范围，请重新输入: ");
        }
        else {
            condition = 0;
        }
    } while (condition);

    flag = win_or_loss(x, y, choice, data, see);
 */


    printf("\n    ");
    for (j = 0; j < 10; j++) {
        printf("%3d ", j + 1);
    }
    printf("\n");

    printf("    ");
    for (j = 0; j < 10; j++) {
        printf("----");
    }
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%3d |", i + 1);
        for (j = 0; j < 10; j++) {
            if (data[i][j] == -1) {
                printf("  M ");
            }
            else {
                printf("%3d ", data[i][j]);
            }
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
        for (int c = 0; c < 10; c++) {
            if (data[r][c] == -1)
                continue;

            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int ni = r + dr;
                    int nj = c + dc;
                    if (ni >= 0 && ni < 10 && nj >= 0 && nj < 10) {
                        if (data[ni][nj] == -1) {
                            data[r][c]++;
                        }
                    }
                }
            }
        }
    }
}

void input(int data[10][10], char see[10][10]) {
    int x, y;
    int condition = 1;
    char choice;

    do {
        scanf("%d %d %c", &x, &y, &choice);
        x = x - 1;
        y = y - 1;
        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            printf("坐标超出范围，请重新输入: ");
        }
        else {
            condition = 0;
        }
    } while (condition);

    win_or_loss (x, y, choice, data, see);
}

int win_or_loss(int x, int y, char choice, int data[10][10], char see[10][10]) {
    int i, j;

    if (see[x][y] == '#') {
        if (choice == 'O') {
            if (data[x][y] == -1) {
                printf("Game Over\n");
                return 0;
            }
            else {
                see[x][y] = 'O';
                for (i = 0; i < 10; i++) {
                    for (j = 0; j < 10; j++) {
                        if (data[i][j] == 0) {
                            see[i][j] = 'O';
                            if (i == 0 && j == 0) {
                                see[i + 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i + 1][j + 1] = 'O';
                            }
                            else if (i == 0 && j == 9) {
                                see[i + 1][j] = 'O';
                                see[i][j - 1] = 'O';
                                see[i + 1][j - 1] = 'O';
                            }
                            else if (i == 9 && j == 0) {
                                see[i - 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i - 1][j + 1] = 'O';
                            }
                            else if (i == 9 && j == 9) {
                                see[i - 1][j] = 'O';
                                see[i][j - 1] = 'O';
                                see[i - 1][j - 1] = 'O';
                            }
                            else if (i == 0) {
                                see[i + 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i][j - 1] = 'O';
                                see[i + 1][j + 1] = 'O';
                                see[i + 1][j - 1] = 'O';
                            }
                            else if (i == 9) {
                                see[i - 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i][j - 1] = 'O';
                                see[i - 1][j + 1] = 'O';
                                see[i - 1][j - 1] = 'O';
                            }
                            else if (j == 0) {
                                see[i + 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i - 1][j] = 'O';
                                see[i + 1][j + 1] = 'O';
                                see[i - 1][j + 1] = 'O';
                            }
                            else if (j == 9) {
                                see[i + 1][j] = 'O';
                                see[i][j - 1] = 'O';
                                see[i - 1][j] = 'O';
                                see[i + 1][j - 1] = 'O';
                                see[i - 1][j - 1] = 'O';
                            }
                            else {
                                see[i + 1][j] = 'O';
                                see[i][j + 1] = 'O';
                                see[i][j - 1] = 'O';
                                see[i - 1][j] = 'O';
                                see[i + 1][j + 1] = 'O';
                                see[i + 1][j - 1] = 'O';
                                see[i - 1][j + 1] = 'O';
                                see[i - 1][j - 1] = 'O';
                            }
                        }
                    }
                }
            }
        }
    }
    else if (see[x][y] == 'O') {
        printf("这个地方已经翻开了\n");
        printf("请重新输入\n");

        input(data, see);
    }
}