#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // strlen 함수 사용을 위한 헤더

void drawHangman0() {
    printf("\n");
    printf(" +---+\n |   |\n     |\n     |\n     |\n     |\n=========\n");
}

void drawHangman1() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n     |\n     |\n     |\n=========\n");
}

void drawHangman2() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n |   |\n     |\n     |\n=========\n");
}

void drawHangman3() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n/|   |\n     |\n     |\n=========\n");
}

void drawHangman4() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n/|\\  |\n     |\n     |\n=========\n");
}

void drawHangman5() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n/|\\  |\n/    |\n     |\n=========\n");
}

void drawHangman6() {
    printf("\n");
    printf(" +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |\n=========\n"); 
}

void drawHangman(int num) {
    if (num == 6) {
        drawHangman6();
    }
    else if (num == 5) {
        drawHangman5();
    }
    else if (num == 4) {
        drawHangman4();
    }
    else if (num == 3) {
        drawHangman3();
    }
    else if (num == 2) {
        drawHangman2();
    }
    else if (num == 1) {
        drawHangman1();
    }
    else {
        drawHangman0();
    }
}

void initHangman(char word[100]) {
    int N, range;
    FILE* fp = fopen("words.txt", "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(fp, "%d", &N);
    range = rand() % N;
    for (int j = 0; j <= range; j++) {
        fscanf(fp, "%s", word);
    }
    fclose(fp);
}

int checkAnswer(char answer[100], char guess[100], char alphabet) {
    int check = 0;
    int length = strlen(answer);
    for (int i = 0; i < length; i++) {
        if (answer[i] == alphabet) {
            guess[i] = alphabet;
            check = 1;
        }
    }
    return check;
}

int main() {
    char answer[100];
    char guess[100];
    char alphabet, enter;
    int answer_len;
    int trials; // 틀린 개수
    int endgame = 0;
    int correct;

    srand(time(NULL));
    initHangman(answer);

    answer_len = strlen(answer);
    for (int i = 0; i < answer_len; i++) {
        guess[i] = '_';
    }

    trials = 6;

    while (trials != 0 && endgame == 0) {
        printf("---------------------------------\n");
        drawHangman(trials);
        printf("Word: ");
        for (int i = 0; i < answer_len; i++) {
            printf("%c", guess[i]);
        }
        printf("\n");

        printf("Enter an alphabet: ");
        scanf(" %c", &alphabet);
        correct = checkAnswer(answer, guess, alphabet);

        if (correct == 0) {
            trials--;
        }

        endgame = 1;
        for (int i = 0; i < answer_len; i++) {
            if (guess[i] == '_') {
                endgame = 0;
            }
        }
    }

    printf("---------------------------------\n");
    drawHangman(trials);
    printf("\n");
    printf("Your Guess = %s\n", guess);
    printf("Answer = %s\n\n", answer);

    if (trials > 0) {
        printf("You win!\n");
    }
    else {
        printf("You lose!\n");
    }

    return 0;
}
