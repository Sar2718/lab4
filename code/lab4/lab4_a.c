#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <time.h>

#define DELIM " \t"
#define PROMPT "> "


char *process(const char *);
int is_all_uniq(const char *word);

int main() {
    char *input = readline(PROMPT);
    while (input != NULL) {
        printf("Input: \"%s\"\n", input);
        clock_t start = clock();
        char *output = process(input);
        printf("Output: \"%s\"\n", output);
        clock_t end = clock();
        float t = (float)(end - start) / CLOCKS_PER_SEC;
        printf("Time: %f.\n\n", t);
        free(input);
        free(output);
        input = readline(PROMPT);
    }
    return 0;
}

char *process(const char *str) {
    char *s = strdup(str);
    int s_len = strlen(s);
    char *res = calloc(s_len + 1, sizeof(char));
    int len = 0;
    char *word = strtok(s, DELIM);
    while (word != NULL) {
        if (is_all_uniq(word)) {
            int w_len = strlen(word);
            memcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            ++len;
        }
        word = strtok(NULL, DELIM);
    }
    free(s);
    if (len > 0) {
        --len;
    }
    res[len] = '\0';
    res = realloc(res, (len + 1) * sizeof(char));
    return res;
}

int is_all_uniq(const char *word) {
    const int ASCII_RANGE = 256;

    int *bd = calloc(ASCII_RANGE, sizeof(int));
    if (bd == NULL) {
        printf("ERROR: Memory allocation failed!\n");
        return 0;
    }

    for (size_t i = 0; word[i] != '\0'; ++i) {
        unsigned char curr_char = (unsigned char)word[i];
        if (bd[curr_char]) {
            free(bd);
            return 1;
        }
        bd[curr_char] = 1;
    }

    free(bd);
    return 0;
}