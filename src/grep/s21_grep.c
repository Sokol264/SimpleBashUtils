#include "s21_grep.h"

void eOptionParsing(char *argv[], int *index, int *pattern) {
    int ex = 0;
    for (size_t j = 0; j < strlen(argv[(*index)]) && !ex; j++) {
        if (argv[(*index)][j] == 'e') {
            if (j != strlen(argv[(*index)]) - 1) {
                (*pattern)++;
                ex = 1;
            } else {
                (*pattern)++;
                (*index)++;
            }
        }
    }
}

void counting(int *opt, int *pattern, int *file, int args, char *argv[]) {
    for (int i = 1; i < args; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'e') {
                if (argv[i][2] == '\0') {
                    (*opt)++;
                    (*pattern)++;
                    i++;
                } else {
                    (*opt)++;
                    (*pattern)++;
                }
            } else {
                eOptionParsing(argv, &i, pattern);
                (*opt)++;
            }
        } else if (*pattern == 0) {
            (*pattern)++;
        } else {
            (*file)++;
        }
    }
}

int countingOption(char *option, int result, char **patternList, int *patternIndex) {
    int stop = 0;
    for (size_t i = 1; i < strlen(option) && result >= 0 && !stop; i++) {
        if (option[i] == 'e') {
            if (i != strlen(option) - 1) {
                snprintf(patternList[(*patternIndex)++],
                         sizeof(char) * strlen(&option[i + 1]) + 1, "%s", &option[i + 1]);
            }
            stop = 1;
        } else if (option[i] == 'i') {
            result |= 1;
        } else if (option[i] == 'v') {
            result |= 2;
        } else if (option[i] == 'c') {
            result |= 4;
        } else if (option[i] == 'l') {
            result |= 8;
        } else if (option[i] == 'n') {
            result |= 16;
        } else if (option[i] == 'h') {
            result |= 32;
        } else if (option[i] == 's') {
            result |= 64;
        } else {
            printf("grep: invalid option -- %c\n", option[i]);
            printf("usage: grep [-ivclnhsfo] [-e pattern] [file ...]\n");
            result = -1;
        }
    }
    return result;
}

int parsing(int args, char *argv[], char **patternList, char **fileList) {
    int patIndex = 0, fileIndex = 0, result = 0;
    for (int i = 1; i < args && result >= 0; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'e') {
                if (argv[i][2] == '\0') {
                    i++;
                    snprintf(patternList[patIndex++], sizeof(char) * strlen(argv[i]) + 1, "%s", argv[i]);
                } else {
                    snprintf(patternList[patIndex++], sizeof(char) * strlen(argv[i]) - 1, "%s", &argv[i][2]);
                }
            } else {
                result = countingOption(argv[i], result, patternList, &patIndex);
            }
        } else if (patIndex == 0) {
            snprintf(patternList[patIndex++], sizeof(char) * strlen(argv[i]) + 1, "%s", argv[i]);
        } else {
            snprintf(fileList[fileIndex++], sizeof(char) * strlen(argv[i]) + 1, "%s", argv[i]);
        }
    }
    return result;
}

int checkEndOfFile(const char *str, int len) {
    return (str[len - 1] != '\n') ? 1 : 0;
}

int searchingResult(regex_t re, char *str, int options) {
    int result = 0;
    if (options & 2) {
        if ((regexec(&re, str, 0, NULL, 0)) != 0) {
            result = 1;
        }
    } else {
        if ((regexec(&re, str, 0, NULL, 0)) == 0) {
            result = 1;
        }
    }
    return result;
}

int compileRegex(char *str, char *pattern, int regFlag, int options) {
    regex_t re;
    int result = 0;
    if ((regcomp(&re, pattern, regFlag)) == 0) {
        if (searchingResult(re, str, options)) {
            result = 1;
        }
    }
    regfree(&re);
    return result;
}

int searchPatterns(char *pattern, char *str, int options) {
    int result = 0;
    if (options & 1) {
        result = compileRegex(str, pattern, REG_ICASE, options);
    } else {
        result = compileRegex(str, pattern, REG_EXTENDED, options);
    }
    return result;
}

void checkCAndLOptions(int options, int countFiles, int coincidence, char* file, int result) {
    if (options & 4) {
        if (countFiles > 1 && !coincidence)
            printf("%s:", file);
        printf("%d\n", coincidence);
    }
    if (options & 8 && result) {
        printf("%s\n", file);
    }
}

void startSearchingPatterns(char **patternList, int countPattern,
                            FILE *fp, char *file, int countFiles, int options) {
    char *str = NULL;
    size_t len;
    int size = 0, exit = 0, coincidence = 0, stringNumber = 0;
    int stopParsingFile = 0, printFileNameWithOptionC = 1;
    int result = 0;
    while ((size = getline(&str, &len, fp)) != -1 && !stopParsingFile) {
        stringNumber++;
        for (int i = 0; i < countPattern && !exit; i++) {
            if ((result = searchPatterns(patternList[i], str, options))) {
                coincidence++;
                if (options & 8) {
                    stopParsingFile = 1;
                    fseek(fp, 0, SEEK_END);
                }
                if (countFiles > 1 && (!(options & 8) || options & 4) && !(options & 32)) {
                    if (printFileNameWithOptionC) {
                        printf("%s:", file);
                        printFileNameWithOptionC = 0;
                    }
                }
                if (!(options & 8) && !(options & 4)) {
                    if (options & 16) {
                        printf("%d:", stringNumber);
                    }
                    printf("%s", str);
                    if (checkEndOfFile(str, size)) printf("\n");
                }
                exit = 1;
            }
        }
        exit = 0;
        if (!(options & 4))
            printFileNameWithOptionC = 1;
    }
    checkCAndLOptions(options, countFiles, coincidence, file, result);
    free(str);
}

void fileParsing(char **fileList, char **patternList, int countFiles, int countPattern, int options) {
    for (int i = 0; i < countFiles; i++) {
        FILE *fp;
        if ((fp = fopen(fileList[i], "rt")) == NULL) {
            if (!(options & 64))
                printf("grep: %s: No such file or directory\n", fileList[i]);
        } else {
            while (!feof(fp)) {
                startSearchingPatterns(patternList, countPattern, fp, fileList[i], countFiles, options);
            }
            fclose(fp);
        }
    }
}

int main(int args, char *argv[]) {
    int countFiles = 0, countOptions = 0, countPattern = 0;
    counting(&countOptions, &countPattern, &countFiles, args, argv);
    char **fileList = (char**)malloc(sizeof(char*) * countFiles);
    for (int i = 0; i < countFiles; i++) {
        fileList[i] = (char*)malloc(sizeof(char) * 1024);
    }
    char **patternList = (char**)malloc(sizeof(char*) * countPattern);
    for (int i = 0; i < countPattern; i++) {
        patternList[i] = (char*)malloc(sizeof(char) * 1024);
    }
    int options = parsing(args, argv, patternList, fileList);
    fileParsing(fileList, patternList, countFiles, countPattern, options);
    for (int i = 0; i < countFiles; i++)
        free(fileList[i]);
    free(fileList);
    for (int i = 0; i < countPattern; i++)
        free(patternList[i]);
    free(patternList);
    return 0;
}
