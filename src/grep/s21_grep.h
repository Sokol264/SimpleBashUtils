#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define E_FLAG "-e"  // множественный вызов с 'шаблонами'
#define I_FLAG "-i"  // игнорирование регистра
#define V_FLAG "-v"  // инверсия смысла поиска
#define C_FLAG "-c"  // количество совпадающих строк
#define L_FLAG "-l"  // только совпадающие файлы
#define N_FLAG "-n"  // номер найденной строки + строка
#define H_FLAG "-h"  // совпадающие строки без названия файлов
#define S_FLAG "-s"  // без сообщений об ошибках
#define F_FLAG "-f"  // получает регулярное выражение из файла
#define O_FLAG "-o"  // только совпадающие части строк

void eOptionParsing(char *argv[], int *index, int *pattern);
void counting(int *opt, int *pattern, int *file, int args, char *argv[]);
int countingOption(char *option, int result, char **patternList, int *patternIndex);
int parsing(int args, char *argv[], char **patternList, char **fileList);
int checkEndOfFile(const char *str, int len);
int searchingResult(regex_t re, char *str, int options);
int compileRegex(char *str, char *pattern, int regFlag, int options);
int searchPatterns(char *pattern, char *str, int options);
void startSearchingPatterns(char **patternList, int countPattern,
                            FILE *fp, char *file, int countFiles, int options);
void fileParsing(char **fileList, char **patternList, int countFiles, int countPattern, int options);


#endif  // SRC_GREP_S21_GREP_H_


// проверка на бинарный файл
