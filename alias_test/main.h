#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_or_update_alias(const char *name, const char *value);
void print_aliases();
void alias(int argc, char *argv[]);
void free_aliases();
int main(int argc, char *argv[]);

extern typedef struct Alias;

Alias* find_alias(const char *name);

#endif /* MAIN_H */
