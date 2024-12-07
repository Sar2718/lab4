#include "mystring.h"

size_t my_strlen(const char *s) {
    size_t len = 0;
    while (*s) {
        ++s, ++len;
    }

    return len;
}

char *my_strdup(const char *s) {
    size_t len = my_strlen(s);

    char *dup = (char *)malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        dup[i] = s[i];
    }
    dup[len] = '\0';

    return dup;
}

void *my_memcpy(void *dest, const void *src, size_t count) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < count; i++) {
        d[i] = s[i];
    }

    return dest;
}

char *my_strtok(char *str, const char *delim) {
    static char *next_token;
    char *current_token;

    if (str != NULL) {
        next_token = str;
    }

    if (next_token == NULL) {
        return NULL;
    }

    while (*next_token && my_strchr(delim, *next_token)) {
        next_token++;
    }

    if (*next_token == '\0') {
        return NULL;
    }

    current_token = next_token;

    while (*next_token && !my_strchr(delim, *next_token)) {
        next_token++;
    }

    if (*next_token) {
        *next_token = '\0';
        next_token++;
    } else {
        next_token = NULL;
    }

    return current_token;
}

char *my_strchr(const char *str, int symbol) {
    char ch_symbol = (char)symbol;

    while (*str != '\0') {
        if (*str == ch_symbol) {
            return (char *)str;
        }
        str++;
    }

    if (ch_symbol == '\0') {
        return (char *)str;
    }

    return NULL;
}

char *get_str(const char *prompt) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    if (prompt) {
        printf("%s", prompt);
    }

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = my_strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            my_memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }

    return res;
}