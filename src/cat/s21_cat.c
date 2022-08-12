#include "s21_cat.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void printNonPrintable(char *c, int flags, int *situation) {
    int ch = (int)*c;
    if (*c < 0) {
        *c &= 127;
        ch = (int)*c;
        ch += 128;
    }
    if (ch < 32 && ch != 9 && ch != 10) {  // non printable characters
        *c += 64;
        printf("^");
    } else if (ch == 127) {
        *c = '?';
        printf("^");
    } else if (ch > 127) {
        if (ch < 128 + 32) {
            printf("M-^");
            *c = ch - 128 + 64;
            if (*c == 'J' && (flags & 4 || flags & 1)) {
                *situation = 1;
            }
        } else if (ch <= 128 + 127) {
            *c -= 128;
        } else {
            printf("^");
            *c = '?';
        }
    }
}

int combinedOptions(int exit, char *argv[], int result, int i) {
    for (size_t j = 1; j < strlen(argv[i]) && !exit && result >= 0; j++) {
        if (argv[i][j] == 'b') {
            result |= 1;
        } else if (argv[i][j] == 'e') {
            result |= 2;
            result |= 32;
        } else if (argv[i][j] == 'n') {
            result |= 4;
        } else if (argv[i][j] == 's') {
            result |= 8;
        } else if (argv[i][j] == 't') {
            result |= 16;
            result |= 32;
        } else if (argv[i][j] == 'v') {
            result |= 32;
        } else {
            printf("cat: illegal option -- %c\nusage: cat [-benstv] [file ...]\n",
                   argv[i][j]);
            result = -1;
        }
    }
    return result;
}

int parseFlags(int args, char *argv[], int *count) {
    int exit = 0;
    int result = 0;
    for (int i = 1; i < args && result >= 0; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], GNU_B_FLAG) == 0) {
                result |= 1;
                exit = 1;
            } else if (strcmp(argv[i], GNU_E_FLAG) == 0) {
                result |= 2;
                exit = 1;
            } else if (strcmp(argv[i], GNU_N_FLAG) == 0) {
                result |= 4;
                exit = 1;
            } else if (strcmp(argv[i], GNU_S_FLAG) == 0) {
                result |= 8;
                exit = 1;
            } else if (strcmp(argv[i], GNU_T_FLAG) == 0) {
                result |= 16;
                exit = 1;
            } else {
                result = combinedOptions(exit, argv, result, i);
            }
        } else {
            (*count)++;
        }
    }
    return result;
}

void parseFiles(int args, char *argv[], char **fileList) {
    int index = 0;
    for (int i = 1; i < args; i++) {
        if (argv[i][0] != '-') {
            snprintf(fileList[index++], sizeof(char) * 1024, "%s", argv[i]);
        }
    }
}

void checkFlags(int flags, char *c, const int *newString, int *third, int *index, int *sit) {
    if ((flags & 1) && (*newString || *sit) && *c != '\n') {
        printf("%6d\t", (*index)++);
        *sit = 0;
    }
    if ((flags & 8) && *newString && *c == '\n') {
        if (*third) {
            *third = 2;
        }
    }
    if ((flags & 4) && !(flags & 1) && (*newString || *sit)) {
        if (*third != 2) {
            printf("%6d\t", (*index)++);
            *sit = 0;
        }
    }
    if ((flags & 2) && *c == '\n') {
        if (*third != 2) {
            printf("$");
        }
    }
    if (flags & 16 && *c == '\t') {
        printf("^");
        *c = 'I';
    }
    if (flags & 32) {
        printNonPrintable(c, flags, sit);
    }
}

void printFile(FILE *file, int flags) {
    char c;
    int newString = 1, index = 1;
    int thirdNewLine = 0;
    fscanf(file, "%c", &c);
    int sit = 0;
    while (!feof(file)) {
        int secondNewLine;
        checkFlags(flags, &c, &newString, &thirdNewLine, &index, &sit);
        if (thirdNewLine != 2) {
            printf("%c", c);
        }
        secondNewLine = (newString && (c == '\n')) ? 1 : 0;
        thirdNewLine = (secondNewLine && (c == '\n')) ? 1 : 0;
        newString = (c == '\n') ? 1 : 0;
        fscanf(file, "%c", &c);
    }
    index = 0;
    fclose(file);
}

void printEveryFiles(int flags, char **fileList, int count) {
    for (int i = 0; i < count; i++) {
        FILE *fp;
        if ((fp = fopen(fileList[i], "rt")) == NULL) {
            printf("cat: %s: No such file or directory\n", fileList[i]);
        } else {
            printFile(fp, flags);
        }
    }
}

int main(int args, char *argv[]) {
    int flags = 0, count = 0;
    if (args > 1) {
        flags = parseFlags(args, argv, &count);
    }
    if (flags != -1) {
        char **fileList = (char**)malloc(sizeof(char*) * count);
        for (int i = 0; i < count; i++) {
            fileList[i] = (char*)malloc(sizeof(char) * 1024);
        }
        parseFiles(args, argv, fileList);
        printEveryFiles(flags, fileList, count);
        for (int i = 0; i < count; i++) {
            free(fileList[i]);
        }
        free(fileList);
    }
    return 0;
}
