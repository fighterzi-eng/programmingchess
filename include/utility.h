#ifndef UTILITY_H
#define UTILITY_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EMPTY(c) ((c) == '.' || (c) == '-')   // just a suggestion not yet implemented but using #define could save us space
#define WHITE(c) islower(c)
#define BLACK(c) isupper(c)

char** boardmaker();
int inside(int x, int y);
int inCheck(int kx, int ky, char **board);
//int checkdanger(int x,int y,char**board);
#endif