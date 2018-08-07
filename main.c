#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WORD_LIST "eff_large_wordlist.txt"
#define MAX_WORDS 10000

int main(int argc, char **argv) {
  int n_flag = 5;
  int p_flag = 1;
  int c;
  while ((c = getopt (argc, argv, "n:p:")) != -1) {
    switch (c) {
    case 'n':
      n_flag = atoi(optarg);
      break;
    case 'p':
      printf("%s\n", optarg);
      p_flag = atoi(optarg);
      break;
    default:
      abort ();
    }
  }

  printf("%d:%d\n", n_flag, p_flag);

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
    words[current_word++] = word;
    word = (char*) calloc(10, sizeof(char));
  }
  fclose(f);
  unsigned int seed = 1;
  f = fopen("/dev/urandom", "r");

  for(int i = 0; i < p_flag; i = i + 1) {
    for (int j = 0; j < n_flag; j = j + 1) {
      fread(&seed, 1, sizeof(unsigned int), f);
      printf("%s", words[seed % current_word]);
      if (j < n_flag - 1) {
        printf(" ");
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
