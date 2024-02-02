#include <stdio.h>

void otrisovka(int width, int heigth, int raketka_1, int raketka_2, int myachX, int myachY, int score_left,
               int score_right);
int raketka_1c(char vvod, int raketka_1, int heigth);
int raketka_2c(char vvod, int raketka_2, int heigth);
int moveBall_1(int myachY, int myach_dirY, int heigth);
int moveBall_2(int myachX, int myach_dirX, int width, int raketka_1, int raketka_2, int myachY);

int main() {
    char vvod;
    int width = 80, heigth = 25;
    int raketka_1 = (heigth / 2) + 1;
    int raketka_2 = (heigth / 2) + 1;
    int myachX = (width / 2);
    int myachY = (heigth / 2) + 1;
    int score_left = 0, score_right = 0;
    int myach_dirY = 1, myach_dirX = 1;
    printf("\033[H\033[J");
    for (int i = 1; i > 0;) {
        otrisovka(width, heigth, raketka_1, raketka_2, myachX, myachY, score_left, score_right);
        scanf("%c", &vvod);

        raketka_1 = raketka_1c(vvod, raketka_1, heigth);
        raketka_2 = raketka_2c(vvod, raketka_2, heigth);

        myach_dirY = moveBall_1(myachY, myach_dirY, heigth);
        myach_dirX = moveBall_2(myachX, myach_dirX, width, raketka_1, raketka_2, myachY);

        if (myachX == width - 1) {
            score_left += 1;
            raketka_1 = (heigth / 2) + 1;
            raketka_2 = (heigth / 2) + 1;
            myachX = (width / 2);
            myachY = (heigth / 2);
        } else if (myachX == 2) {
            score_right += 1;
            raketka_1 = (heigth / 2) + 1;
            raketka_2 = (heigth / 2) + 1;
            myachX = (width / 2);
            myachY = (heigth / 2);
        }

        if (score_left >= 21 || score_right >= 21 || vvod == 'q') {
            if (score_left >= 21) {
                printf("Левый игрок победил");
            } else if (score_right >= 21) {
                printf("Правый игрок победил");
            }
            break;
        }

        myachY += myach_dirY;
        myachX += myach_dirX;
        printf("\033[H\033[J");
    }
    return 0;
}

void otrisovka(int width, int heigth, int raketka_1, int raketka_2, int myachX, int myachY, int score_left,
               int score_right) {
    for (int i = 1; i <= heigth; i++) {
        for (int j = 1; j <= width; j++) {
            if (i == myachY && j == myachX) {
                printf("*");
            } else if ((j == width / 2 && i != 4) || (j == width / 2 && i == 4 && score_left < 10) ||
                       (i == 4 && score_left >= 10 && j == (width / 2) - 1)) {
                printf("|");
            } else if (j == 2 && (raketka_1 == i + 1 || raketka_1 == i || raketka_1 == i - 1)) {
                printf("}");
            } else if (j == width - 1 && (raketka_2 == i + 1 || raketka_2 == i || raketka_2 == i - 1)) {
                printf("{");
            } else if (i == 4 && j == 33) {
                printf("%d", score_left);
            } else if ((i == 4 && j == 47 && score_left < 10) || (i == 4 && j == 46 && score_left >= 10)) {
                printf("%d", score_right);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int raketka_1c(char vvod, int raketka_1, int heigth) {
    if (vvod == 'z' && raketka_1 < heigth - 1) {
        raketka_1 += 1;
    } else if (vvod == 'a' && raketka_1 > 2) {
        raketka_1 -= 1;
    }
    return raketka_1;
}

int raketka_2c(char vvod, int raketka_2, int heigth) {
    if (vvod == 'm' && raketka_2 < heigth - 1) {
        raketka_2 += 1;
    } else if (vvod == 'k' && raketka_2 > 2) {
        raketka_2 -= 1;
    }
    return raketka_2;
}

int moveBall_1(int myachY, int myach_dirY, int heigth) {
    if ((myachY == heigth || myachY == 1)) {
        myach_dirY *= -1;
    }
    return myach_dirY;
}

int moveBall_2(int myachX, int myach_dirX, int width, int raketka_1, int raketka_2, int myachY) {
    if ((myachX == width - 2) &&
        (raketka_2 == myachY + 1 || raketka_2 + 1 == myachY + 1 || raketka_2 - 1 == myachY + 1)) {
        myach_dirX *= -1;
    } else if ((myachX == 3) &&
               (raketka_1 == myachY - 1 || raketka_1 + 1 == myachY - 1 || raketka_1 - 1 == myachY - 1)) {
        myach_dirX *= -1;
    }
    return myach_dirX;
}