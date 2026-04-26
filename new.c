#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    // 自动切换 UTF-8 并尝试开启颜色支持
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
    void init_terminal() {
        system("chcp 65001");
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
    }
#else
    #define CLEAR "clear"
    // Linux/macOS 通常不需要特殊初始化
    void init_terminal() { 
        // 留空或执行清理
    }
#endif
void generate_mines_and_counts(int data[10][10]);
void input(int data[10][10], char see[10][10], int *x, int *y, char *choice);
void print(int data[10][10], char see[10][10]);
void print_data(int data[10][10]);
void print_element(int value, char status);
void expand(int x, int y, int data[10][10], char see[10][10]);
int processing(int x, int y, char choice, int data[10][10], char see[10][10]);
int win_or_loss(int data[10][10], char see[10][10]);
void clear_screen() {
    system(CLEAR);
}

int main() {
// --- 开启 Windows ANSI 颜色支持的完整补丁 ---
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }    
    int data[10][10] = {{0}};
    char see[10][10];
    int i, j;

    #ifdef _WIN32
        SET_UTF8();
    #endif

    clear_screen();
    
    printf("扫雷游戏\n");
    printf("游戏操作提示: O=翻开格子; P=插旗（标记为雷）; #=取消插旗\n");
    printf("坐标范围为1 <= x <= 10; 1 <= y <= 10\n");
    
    generate_mines_and_counts(data);

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            see[i][j] = '#';
        }
    }

    win_or_loss(data, see);
    
    return 0;
}

void generate_mines_and_counts(int data[10][10]) {
    const int MineCount = 10;
    int placed = 0;
    
    srand(time(NULL));

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

void input(int data[10][10], char see[10][10], int *x, int *y, char *choice) {
    int x1, y1;
    int condition = 1;
    char choice1;
    
    printf("请输入坐标(x y)和操作(O、P、#)[示例: 1 1 O]:");

    do {
        if (scanf("%d %d %c", &x1, &y1, &choice1) != 3) {
            printf("输入格式错误，请重新输入！\n");
            while (getchar() != '\n'); // 清理缓冲区
            continue;
        }
        x1 = x1 - 1;
        y1 = y1 - 1;
        if (choice1 >= 'a' && choice1 <= 'z') {
            choice1 = choice1 - 'a' + 'A';
        }
        if (x1 < 0 || x1 >= 10 || y1 < 0 || y1 >= 10) {
            printf("坐标超出范围，请重新输入: ");
        }
        else if (choice1 != 'O' && choice1 != 'P' && choice1 != '#') {
            printf("操作无效，请重新输入: ");
        }
        else {
            condition = 0;
        }
    } while (condition);

    *x = x1;
    *y = y1;
    *choice = choice1;
}

void print(int data[10][10], char see[10][10]) {
    int i, j;
    
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
            print_element(data[i][j], see[i][j]);
            if (see[i][j] == 'O') {
                printf("%3d ", data[i][j]);
            }
            else {
                printf("%3c ", see[i][j]);
            }
        }
        printf("\n");
    }
}

void print_data(int data[10][10]) {
    int i, j;

    printf("--- 最终棋盘 ---");
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
            print_element(data[i][j], 0);
            if (data[i][j] == -1) {
                printf("%3c ", 'M');
            }
            else {
                printf("%3d ", data[i][j]);
            }
        }
        printf("\n");
    }
}

void print_element(int value, char status) {
    if (status == 'P') { // 插旗显示黄色
        printf("\033[33m %2c \033[0m", 'P');
    } else if (status == '#') { // 未翻开显示灰色或默认
        printf(" %2c ", '#');
    } else if (status == 'O') { // 已翻开
        if (value == -1) { // 地雷：红底白字
            printf("\033[41;37m  M \033[0m");
        } else if (value == 0) { // 0不显示数字，显示点或空格更美观
            printf("  . ");
        } else {
            // 根据数字显示不同颜色
            switch(value) {
                case 1: printf("\033[34m %2d \033[0m", value); break; // 蓝
                case 2: printf("\033[32m %2d \033[0m", value); break; // 绿
                case 3: printf("\033[31m %2d \033[0m", value); break; // 红
                case 4: printf("\033[35m %2d \033[0m", value); break; // 紫
                default: printf("\033[36m %2d \033[0m", value); break; // 青
            }
        }
    }
}

void expand(int x, int y, int data[10][10], char see[10][10]) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10 || see[x][y] == 'O' || see[x][y] == 'P') return;
    
    see[x][y] = 'O';
    if (data[x][y] == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                expand(x + dr, y + dc, data, see);
            }
        }
    }
}

int processing(int x, int y, char choice, int data[10][10], char see[10][10]) {
    if (choice == 'P') {
        if (see[x][y] == '#') {
            see[x][y] = 'P';
            printf("插旗成功\n");
        }
        else if (see[x][y] == 'P' || see[x][y] == 'O') {
            printf("该格子已标记，请重新输入\n");
        }
        return 1;
    } else if (choice == '#') {
        if (see[x][y] == 'P') {
            see[x][y] = '#';
            printf("取消标记成功\n");
        }
        else if (see[x][y] == 'O' || see[x][y] == '#') {
            printf("只有已插旗(P)才能取消标记，请重新输入\n");
        }
        return 1;
    } else if (choice == 'O') {
        if (data[x][y] == -1) {
            return -1;
        }
        else if (see[x][y] == 'O' || see[x][y] == 'P') {
            printf("该格子已翻开或已插旗(P)，请重新输入\n");
        }
        else {
            expand(x, y, data, see);
        }
        return 1;
    }
    return 1;
}

int win_or_loss(int data[10][10], char see[10][10]) {
    int GameStatus = 1;
    int win_loss = 0;
    int i, j, x, y;
    int count;
    char choice;

    while (GameStatus == 1) {
        count = 0;
        print(data, see);
        input(data, see, &x, &y, &choice);

        GameStatus = processing(x, y, choice, data, see);

        if (GameStatus == -1) {
            printf("很遗憾，你输了！\n");
            print_data(data);
            break;
        }

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                if (see[i][j] == 'O') {
                    count++;
                    if (10*10 - count == 10) {
                        win_loss = 1;
                    }
                }
            }
        }
        if (win_loss == 1) {
            printf("恭喜你，你赢了！\n");
            break;
        }
    }
    return 0;
}