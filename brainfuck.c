/*!
 * @file brainfuck.c
 * @author EaGitro
 * @brief a interpreter of brainfu*k
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright © 2023 EaGitro
 * 
 */


#include <stdio.h>
#include <string.h>

#define FIELD_LEN 1024
#define SOURCE_LEN 1024
#define STACK_SIZE 256


typedef struct {
    int stack[STACK_SIZE]; /* the initial value is 0 */
    int top_index;         /* the initial value is -1  */
} _Bracket_stack;


/* -- start prototypes -- */

int executor(const char source[], const int source_len, const int debug_mode);                     /* execute the source string */
int read_source(char src[], const int src_len);                                                    /* read source code */
void push(_Bracket_stack *p_stack, const int pushed_item);                                         /* push */
int pop(_Bracket_stack *p_stack);                                                                  /* pop. (return index or err)  */
int search_right_squarebracket(const char source[], const int source_index, const int source_len); /* search the pair of the '['.  */


/* -- end prototypes -- */




void push(_Bracket_stack *p_stack, const int pushed_item) {
    p_stack->stack[++p_stack->top_index] = pushed_item;
}



int pop(_Bracket_stack *p_stack) {
    if (p_stack->top_index <= -1) {
        return -16; /* MISSING_LEFT_BRACKET_ERR */
    } else {
        int ret = p_stack->stack[p_stack->top_index];
        p_stack->stack[p_stack->top_index--] = 0;
        return ret;
    }
}


int search_right_squarebracket(const char source[], const int source_index, const int source_len) {
    int index_jump_to = 0;

    int find_targeted_bracket = 0; /* if find "]", then +=1. if find "[", then -=1. "find_targeted_bracket = 1" shows the targeted bracket is found. */

    /* --- */
    // printf("search_right_squarebracket:\n");
    /* --- */

    for (int index_searching = source_index + 1; index_searching < source_len; index_searching++) {

        /* --- */
        // printf("searching index: %d / charactor: %c \n", index_searching, source[index_searching]);
        /* --- */

        switch (source[index_searching]) {
            case ']':
                find_targeted_bracket++;
                /* --- */
                // printf("find ]. find_targeted_bracket: %d\n", find_targeted_bracket);
                /* --- */

                break;

            case '[':
                find_targeted_bracket--;

                /* --- */
                // printf("find [. find_targeted_bracket: %d\n", find_targeted_bracket);
                /* --- */

                break;
        }

        if (find_targeted_bracket == 1) {
            return index_searching;
        }
    }

    return -1; /* MISSING_RIGHT_BRACKET_ERR */
}




/**
 * @brief the main body of brainfuck
 * 
 * @param source 
 * @param source_len 
 * @param debug_mode
 */
int executor(const char source[], const int source_len, const int debug_mode) {

    char field_arr[FIELD_LEN] = {0};
    int field_index = 0;

    int source_index = 0;

    _Bracket_stack left_bracket_stack = {{0}, -1};


    unsigned int action_count = 0;




    for (source_index; source_index < source_len; source_index++) {


        if (debug_mode) {
            printf("\nsource %*dth: %c\n", 4, source_index, source[source_index]); // debug statement
            printf("input/output : ");
        }


        switch (source[source_index]) {
            case '>':
                field_index++;
                if (field_index > FIELD_LEN) {
                    return 1; /* FIELD_RANGE_ERR */
                }
                break;

            case '<':
                field_index--;
                if (field_index < 0) {
                    return 1; /* FIELD_RANGE_ERR */
                }
                break;

            case '+':
                field_arr[field_index]++;
                break;

            case '-':
                field_arr[field_index]--;
                break;

            case '.':
                putchar(field_arr[field_index]);
                break;

            case ',':
                field_arr[field_index] = getchar();
                break;

            case '[': {
                if (field_arr[field_index] == 0) { /* if field_arr[field_index] == 0, jump to ']'  */

                    int right_squarebracket_index = search_right_squarebracket(source, source_index, source_len);

                    if (right_squarebracket_index == -1) {
                        return 2; /* MISSING_RIGHT_bracket_ERR */
                    } else {
                        source_index = right_squarebracket_index; /* jump to ']'   */
                    }

                } else {
                    push(&left_bracket_stack, source_index);
                }

            } break;

            case ']': {
                int left_squarebracket_index = pop(&left_bracket_stack);

                if (left_squarebracket_index == -16) {
                    return 3; /* MISSING_LEFT_BRACKET_ERR */
                } else {
                    source_index = left_squarebracket_index - 1; /* jump to just before '[' */
                }
            } break;





            default:
                break;
        }




        if (debug_mode) {
            printf("\n");
            printf("index: %*d / value: %*d\n", 4, field_index, 4, field_arr[field_index]); // debug statement
            printf("---\n");

            /* braket stack */
            printf("bracket stack:  ");
            for (int i = 0; i <= left_bracket_stack.top_index; i++) {
                printf("%d ", left_bracket_stack.stack[i]);
            }
            printf("\n");

            /* top index */
            // printf("top index of bracket stack: %d\n", left_bracket_stack.top_index);

            /* top 10 of field array */
            printf("top 10 of field array:  ");
            for (int i = 0; i <= 10; i++) {
                printf("%d ", field_arr[i]);
            }
            printf("\n");

            /* action count */
            printf("action count: %d\n", ++action_count);

            printf("---\n");
        }
    }
}


int read_source(char src[], const int src_len) {

    char file_name[32] = {0};
    printf("file name > ");
    scanf("%32[^\n]%*[^\n]", file_name); // 1024文字超えた場合は*で捨てる
    scanf("%*c");                        // 最後に改行が残っているためそれも捨てる


    FILE *fp = NULL;
    char c;

    //	読み込みモードでファイルを開く
    fp = fopen(file_name, "r");

    int i = 0;
    if (fp) {
        //	EOFまでファイルから文字を1文字ずつ読み込む

        int flag = 1; /* Do not read the charactor where is from '#' to '\n'.   (To comment out, Use '#') */

        while ((c = fgetc(fp)) != EOF) {

            if (c == '#') {
                flag = 0;
            } else if (c == '\n') {
                flag = 1;
            }

            if (flag == 1) {
                src[i] = c;
                i++;
            }
        }
        printf("Your code is: \n%s\n", src);
        // printf("src[0]: %c\n", src[0]);
        return 0;
    } else {
        printf("Some errer occured when opening the file!\n");
        return 1;
    }



    fclose(fp);
}




int main(void) {

    char source[SOURCE_LEN] = {0};

    /* ----- enter source ----- */

    if (read_source(source, SOURCE_LEN) == 1) {
        return 1;
    }


    /* ----- end of enter source ----- */

    /* -- if debug -- */

    char y[2] = "\0";
    int debug_mode = 0;


    printf("debug mode ? (Y/n) > ");
    scanf("%1[^\n]%*c", y); // 1文字超えた場合は*で捨てる

    if (y[0] == 'Y') {
        debug_mode = 1;
    }

    /* -- end of if debug -- */


    int r = executor(source, strlen(source), debug_mode);

    if (r == 1) {
        printf("FIELD_RANGE_ERR\n");
    } else if (r == 2) {
        printf("MISSING_RIGHT_BRACKET_ERR\n");
    } else if (r == 3) {
        printf("MISSING_LEFT_BRACKET_ERR\n");
    }
}
