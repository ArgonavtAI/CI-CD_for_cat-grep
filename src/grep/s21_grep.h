#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

struct flags {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
  int flag_error;
};
struct flags flag = {0};
struct flags *p_flags = &flag;

void output(int argc, char *argv[]);
void switch_case(int val, char *pattern);
void parsing(char *pattern, char *argv[]);
void fileNumbers(char *argv[], int *amountFiles, int variant);
void text_str(char *pattern);
void working(char *argv[], int variant, int *amountFiles, char *pattern);
void flagL(char *nameFile);
void flagC(int testFiles, char *nameFile, int numberStrC);
void flagN(int numberStr, int n);
void funcFlagF(char *fileName, char *pattern);
void flagO(char *buffer, char *pattern);
void flagTraining(int numberFiles, char *argv[], char *buffer, int numberStr,
                  int numberArg, char *pattern);

#endif  // SRC_GREP_S21_GREP_H_
