#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include "avl.h"
#include "abp.h"

#define MAX_FILENAME_LENGTH 20
#define SUCCESSFUL_RETURN 0
#define ERROR_RETURN -1
#define MAX_STRING_LENGTH 1000
#define ABP 1
#define AVL 2

int main(int argc, char **argv);
char *limpa(char *p);
int maximo(int a, int b);

#endif