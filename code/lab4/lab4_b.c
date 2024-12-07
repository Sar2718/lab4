#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/mystring/mystring.h"

#define DELIM " \t"
#define PROMPT "> "


char *process(const char *);
int is_all_uniq(const char *word);

int main() {
    char *input = get_str(PROMPT);
    while (input != NULL) {
        printf("Input: \"%s\"\n", input);
        clock_t start = clock();
        char *output = process(input);
        clock_t end = clock();
        float t = (float)(end - start) / CLOCKS_PER_SEC;
        printf("Output: \"%s\"\n\n", output);
        printf("Time: %f.\n\n", t);
        free(input);
        free(output);
        input = get_str(PROMPT);
    }
    return 0;
}

char *process(const char *str) {
    char *s = my_strdup(str);
    int s_len = my_strlen(s);
    char *res = calloc(s_len + 1, sizeof(char));
    int len = 0;
    char *word = my_strtok(s, DELIM);
    while (word != NULL) {
        if (is_all_uniq(word)) {
            int w_len = my_strlen(word);
            my_memcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            ++len;
        }
        word = my_strtok(NULL, DELIM);
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