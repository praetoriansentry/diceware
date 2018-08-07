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
  fread(&seed, 1, sizeof(unsigned int), f);
  printf("%s ", words[seed % current_word]);
  fread(&seed, 1, sizeof(unsigned int), f);
  printf("%s ", words[seed % current_word]);
  fread(&seed, 1, sizeof(unsigned int), f);
  printf("%s ", words[seed % current_word]);
  fread(&seed, 1, sizeof(unsigned int), f);
  printf("%s ", words[seed % current_word]);
  fread(&seed, 1, sizeof(unsigned int), f);
  printf("%s\n", words[seed % current_word]);

  fclose(f);
  for(int i = 0; i < current_word; i = i + 1) {
    free(words[i]);
  }
  free(dice);
  free(words);
  return 0;
}
