#include "s21_grep.h"

int main(int argc, char *argv[]) {
  output(argc, argv);
  return 0;
}

void output(int argc, char *argv[]) {
  char pattern[BUFFER] = {0};
  if (argc > 2) {
    int status = 0;
    int testArg = 1;
    char *params = "e:ivclnhsf:o";
    while ((status = getopt_long(argc, argv, params, 0, NULL)) != -1) {
      switch_case(status, pattern);
      if (flag.flag_e && argc == 2) {
        testArg = 0;
        break;
      }
    }
    if ((flag.flag_e || flag.flag_f) && argc < 4) {
      testArg = 0;
    }

    if ((!flag.flag_e && !flag.flag_f) && argc < 3) {
      testArg = 0;
    }

    if (testArg) {
      parsing(pattern, argv);
    }
  }
}

void switch_case(int val, char *pattern) {
  switch (val) {
  case 'e':
    p_flags->flag_e = 1;
    text_str(pattern);
    break;
  case 'i':
    p_flags->flag_i = 1;
    break;
  case 'v':
    p_flags->flag_v = 1;
    break;
  case 'c':
    p_flags->flag_c = 1;
    break;
  case 'l':
    p_flags->flag_l = 1;
    break;
  case 'n':
    p_flags->flag_n = 1;
    break;
  case 'h':
    p_flags->flag_h = 1;
    break;
  case 's':
    p_flags->flag_s = 1;
    break;
  case 'f':
    p_flags->flag_f = 1;
    funcFlagF(optarg, pattern);
    break;
  case 'o':
    p_flags->flag_o = 1;
    break;
  }
}

void parsing(char *pattern, char *argv[]) {
  int opt = 0;
  int amountFiles = 0;
  if ((!flag.flag_e) & (!flag.flag_f)) {
    pattern = argv[optind];
    opt = 1;
    fileNumbers(argv, &amountFiles, opt);
  }
  if (!opt) {
    fileNumbers(argv, &amountFiles, opt);
  }
  working(argv, opt, &amountFiles, pattern);
}

void working(char *argv[], int opt, int *amountFiles, char *pattern) {
  for (int i = 0; i < *amountFiles; i++) {
    FILE *fp;
    regex_t reg;
    int testL = 0;
    int numberStrFlagC = 0;
    int numberStr = 1;
    char buffer[BUFFER] = {0};
    if (flag.flag_i) {
      regcomp(&reg, pattern, REG_EXTENDED | REG_ICASE);
    } else {
      regcomp(&reg, pattern, REG_EXTENDED);
    }
    if ((fp = fopen(argv[optind + opt + i], "r")) != NULL) {
      while (fgets(buffer, BUFFER, fp) != NULL) {
        if (regexec(&reg, buffer, 0, NULL, 0) == 0 && flag.flag_v == 0) {
          if (flag.flag_c && flag.flag_l) {
            numberStrFlagC = 1;
          } else if (flag.flag_c && !flag.flag_l) {
            numberStrFlagC++;
          }
          if (!flag.flag_l) {
            flagTraining(*amountFiles, argv, buffer, numberStr,
                         optind + opt + i, pattern);
          } else {
            testL = 1;
          }
        } else if (regexec(&reg, buffer, 0, NULL, 0) != 0 && flag.flag_v) {
          if (flag.flag_c && flag.flag_l) {
            numberStrFlagC = 1;
          } else if (flag.flag_c && !flag.flag_l) {
            numberStrFlagC++;
          }
          if (!flag.flag_l) {
            flagTraining(*amountFiles, argv, buffer, numberStr,
                         optind + opt + i, pattern);
          } else {
            testL = 1;
          }
        }
        numberStr++;
      }
      if (flag.flag_c) {
        flagC(*amountFiles, argv[optind + opt + i], numberStrFlagC);
      }
      if (flag.flag_l && testL) {
        flagL(argv[optind + opt + i]);
      }
      fclose(fp);
    }
    regfree(&reg);
  }
}

void text_str(char *pattern) {
  if (pattern[0] == 0) {
    strcat(pattern, optarg);
  } else {
    strcat(pattern, "|");
    strcat(pattern, optarg);
  }
}

void fileNumbers(char *argv[], int *amountFiles, int opt) {
  if (opt) {
    for (int i = optind + 1; argv[i] != NULL; i++) {
      if (argv[i][0] != '-' ||
          (argv[i - 1][0] != '-' && argv[i - 1][1] != 'f')) {
        *amountFiles = *amountFiles + 1;
      }
    }
  } else {
    for (int i = optind; argv[i] != NULL; i++) {
      if (argv[i][0] != '-' ||
          (argv[i - 1][0] != '-' && argv[i - 1][1] != 'f')) {
        *amountFiles = *amountFiles + 1;
      }
    }
  }
}

void flagTraining(int numberFiles, char *argv[], char *buffer, int numberStr,
                  int numberArg, char *pattern) {
  if (flag.flag_c == 0) {
    if (numberFiles > 1 && flag.flag_h == 0) {
      printf("%s:", argv[numberArg]);
    }
    flagN(numberStr, flag.flag_n);

    if (flag.flag_o && flag.flag_v == 0) {
      flagO(buffer, pattern);
    } else {
      fputs(buffer, stdout);
    }
    if (buffer[strlen(buffer)] == '\0' && buffer[strlen(buffer) - 1] != '\n') {
      printf("\n");
    }
  }
}

void flagN(int numberStr, int n) {
  if (n) {
    printf("%d:", numberStr);
  }
}

void flagC(int testFiles, char *nameFile, int numberStrC) {
  if (testFiles > 1 && flag.flag_h == 0) {
    printf("%s:%d\n", nameFile, numberStrC);
  } else {
    printf("%d\n", numberStrC);
  }
}

void funcFlagF(char *fileName, char *pattern) {
  FILE *fp;
  char buffer[BUFFER];
  if ((fp = fopen(fileName, "r")) == NULL) {
    if (flag.flag_s == 0) {
      perror("No FILE");
    }
  }
  while (fgets(buffer, BUFFER, fp) != NULL) {
    if (buffer[strlen(buffer)] == '\0' && buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0';
    }
    if (pattern[0] == 0) {
      strcat(pattern, buffer);
    } else {
      strcat(pattern, "|");
      strcat(pattern, buffer);
    }
  }
  if (flag.flag_e) {
    pattern[strlen(pattern)] = '\0';
  } else {
    pattern[strlen(pattern) - 1] = '\0';
  }
  fclose(fp);
}

void flagO(char *buffer, char *pattern) {
  regex_t reg;
  regmatch_t pmatch[1024];
  int status = 1;
  char *s = buffer;
  if (flag.flag_i) {
    if ((status = regcomp(&reg, pattern, REG_EXTENDED | REG_ICASE)) != 0) {
      printf("failed %d", status);
      regfree(&reg);
    }
  } else {
    if ((status = regcomp(&reg, pattern, REG_EXTENDED)) != 0) {
      printf("failed %d", status);
      regfree(&reg);
    }
  }

  if (status == 0 && flag.flag_v == 0) {
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (regexec(&reg, s, 1, pmatch, 0) != flag.flag_v) {
        break;
      }
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             s + pmatch[0].rm_so);
      s += pmatch[0].rm_eo;
    }
  }
  regfree(&reg);
}

void flagL(char *nameFile) { printf("%s\n", nameFile); }
