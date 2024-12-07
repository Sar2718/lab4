#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


size_t my_strlen(const char *s);
char *my_strdup(const char *s);
void *my_memcpy(void *dest, const void *src, size_t count);
char *my_strtok(char *str, const char *delim);
char *my_strchr(const char *str, int symbol);
char *get_str(const char *prompt);


#endif