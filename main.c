#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WORD_LIST "eff_large_wordlist.txt"
#define MAX_WORDS 10000

int main() {
  FILE* f = fopen(WORD_LIST, "r");
  if (f == NULL) {
    printf("Unable to open word list: %s\n", WORD_LIST);
    exit(1);
  }
  char* dice = NULL;
  char* word = NULL;
  char** words = (char**) calloc(MAX_WORDS, sizeof(char**));
  int current_word = 0;
  while(fscanf(f, "%ms\t%ms\n", &dice, &word) == 2) {
    words[current_word++] = word;
    // printf("%s\t%s\n", dice, word);
  }

  srand(time(0));
  printf("%s ", words[rand() % current_word]);
  printf("%s ", words[rand() % current_word]);
  printf("%s ", words[rand() % current_word]);
  printf("%s ", words[rand() % current_word]);
  printf("%s\n", words[rand() % current_word]);

  return 1;
}
