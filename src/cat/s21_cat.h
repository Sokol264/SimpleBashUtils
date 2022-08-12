#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>

#define B_FLAG "-b"
#define E_FLAG "-e"
#define N_FLAG "-n"
#define S_FLAG "-s"
#define T_FLAG "-t"
#define V_FLAG "-v"
#define GNU_B_FLAG "--number-nonblank"
#define GNU_E_FLAG "-E"
#define GNU_N_FLAG "--number"
#define GNU_S_FLAG "--squeeze-blank"
#define GNU_T_FLAG "-T"
#define GNU_V_FLAG "-v"

void printNonPrintable(char *c, int flags, int *situation);
int combinedOptions(int exit, char *argv[], int result, int i);
int parseFlags(int args, char *argv[], int *count);
void parseFiles(int args, char *argv[], char **fileList);
void checkFlags(int flags, char *c, const int *newString, int *third, int *index, int *sit);
void printFile(FILE *file, int flags);
void printEveryFiles(int flags, char **fileList, int count);

#endif  // SRC_CAT_S21_CAT_H_
