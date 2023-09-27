#include <stdio.h>
#include <string.h>


#define WORDS_LEN 1024
#define DIVISION 5
#define ABS(v) ((v) >= 0 ? (v) : -(v))
#define PLUS_MINUS(v) ((v) >= 0 ? ('+') : ('-'))



void get_words(char words[]) {
    printf("words to bf > ");
    scanf("%32[^\n]%*[^\n]", words); // 1024文字超えた場合は*で捨てる
    scanf("%*c");
}

char puls_minus(int num) {
    return ((num) >= 0 ? ('+') : ('-'));
}


void diff2bf(short int diff, short int divisor) {
    // ++++[>++<-]>---. # ++++: quotient, ++: divisor, ---: remainder

    int quotient = diff / divisor;
    int remainder = diff % divisor;


    for (int i = 0; i < divisor; i++) {
        printf("+");
    }


    printf("[>");

    for (int i = 0; i < ABS(quotient); i++) {
        printf("%c", puls_minus(quotient));
    }

    printf("<-]>");
    for (int i = 0; i < ABS(remainder); i++) {
        printf("%c", puls_minus(remainder));
    }

    printf(".<\n");
}


void words2diff(char words[], short int len) {
    int prev_ascii = 0;
    for (int i = 0; i < len; i++) {
        int diff = words[i] - prev_ascii;
        diff2bf(diff, DIVISION);
        prev_ascii = words[i];
    }
}

int main(void) {

    char words[WORDS_LEN] = {0};

    get_words(words);

    words2diff(words, strlen(words));
}