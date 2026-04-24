#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_number(int data[10][10]);

int main() {
    int data[10][10] = {{0}};
    char see[10][10] = {{0}};

    get_random_number(data);
    return 0;
}

int get_random_number(int data[10][10]) {
    int i, j = 0;
    const int Mine =10;
    int count, count2;
    int ir[Mine] = {0};
    int jr[Mine] = {0};

    for (count = 0; count < Mine; count++) {
        //i和j是0~9的随机数
        i = rand() % 10;
        j = rand() % 10;

        if (count == 0) {
            data[i][j] = -1;
        }
        else {
            for (count2 = 0; count2 < count; count2++) {
                if (ir[count2] == i && jr[count2] == j) {
                    count--;
                }
                data[i][j] = -1;
            }
        }
    }
    for (count = 0; count < Mine; count++) {
        for (count2 = 0; count2 < Mine; count2++) {
            if (data[count][count2] == -1) {
                continue;
            }
            else {
                if (count == 0 && count2 == 0) {
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count == 0 && count2 == 9) {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count == 9 && count2 == 0) {
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count == 9 && count2 == 9) {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count == 0) {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count == 9) {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count2 == 0) {
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else if (count2 == 9) {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
                else {
                    if (data[count][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count - 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 - 1] == -1) {
                        data[count][count2] += 1;
                    }
                    if (data[count + 1][count2 + 1] == -1) {
                        data[count][count2] += 1;
                    }
                }
            }
        }
    }
}