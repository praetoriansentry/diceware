#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

#define WORD_LIST "eff_large_wordlist.txt"
#define MAX_WORDS 10000

void show_help() {
  printf("Diceware Passphrase Generator\n\n");
  printf("Basic usage:\n");
  printf("\t$ diceware\n\n");
  printf("Optional Arguments:\n");
  printf("\t-w\tThe number of words to use in each passphrase\n");
  printf("\t-p\tThe number of passphrases to generate\n");
  printf("\t-d\tThe delimiter to use between words. Defaults to space.\n");
  printf("\t-c\tCapitalize the first letter of each word.\n");
  printf("\n");
  printf("Example:\n");
  printf("\t$ diceware -w 5 -p 1 -c -d ''\n");
  return;
}

int main(int argc, char **argv) {
  int w_flag = 5;
  int p_flag = 1;
  int c_flag = 0;
  char* d_flag = " ";
  int c;
  while ((c = getopt (argc, argv, "w:p:hd:c")) != -1) {
    switch (c) {
    case 'c':
      c_flag = 1;
      break;
    case 'w':
      w_flag = atoi(optarg);
      break;
    case 'p':
      p_flag = atoi(optarg);
      break;
    case 'd':
      d_flag = optarg;
      break;
    case 'h':
      show_help();
      exit(0);
    default:
      show_help();
      exit(0);
    }
  }

  FILE* f = fopen(WORD_LIST, "r");
  if (f == NULL) {
    printf("Unable to open word list: %s\n", WORD_LIST);
    exit(1);
  }
  char* dice = (char*) calloc(5, sizeof(char));
  char* word = (char*) calloc(10, sizeof(char));
  char** words = (char**) calloc(MAX_WORDS, sizeof(char**));
  int current_word = 0;
  while(fscanf(f, "%s\t%s\n", dice,word) == 2) {
    if (c_flag == 1) {
      word[0] = toupper(word[0]);
    }
    words[current_word++] = word;
    word = (char*) calloc(10, sizeof(char));
  }
  fclose(f);
  unsigned int seed = 1;
  f = fopen("/dev/urandom", "r");

  for(int i = 0; i < p_flag; i = i + 1) {
    for (int j = 0; j < w_flag; j = j + 1) {
      fread(&seed, 1, sizeof(unsigned int), f);
      printf("%s", words[seed % current_word]);
      if (j < w_flag - 1) {
        printf("%s", d_flag);
      }
    }
    printf("\n");
  }

  fclose(f);
  for(int i = 0; i < current_word; i = i + 1) {
    free(words[i]);
  }
  free(dice);
  free(words);
  return 0;
}
