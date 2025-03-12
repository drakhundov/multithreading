#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "utils.h"

void* start_routine(void* arg) {
  if (arg == NULL) {
    perror("Need a file name to start.");
  }
  char* filename = (char*)arg;
  catf(filename);
  puts("");
  return NULL;
}

int main(int argc, char* argv[]) {
  char* dirname = (char*)malloc(MAXDIRNAME);
  printf("Directory to search: ");
  scanf("%s", dirname);
  size_t dirnamesz = strlen(dirname);
  if (dirnamesz < MAXDIRNAME - 1) {
    char* temp =
      realloc(dirname, dirnamesz + 1);  // +1 for the terminating char.
    if (temp == NULL) {
      perror("Failed to reallocate memory.");
      free(dirname);
      exit(1);
    }
    dirname = temp;
  }
  char filenames[MAXFILES][MAXFILENAME];
  pthread_t threads[MAXFILES];
  memset(filenames, '\0', sizeof(filenames));
  int nfiles = listdir(dirname, filenames);
  printf("nfiles: %d\n", nfiles);
  fflush(stdout);
  for (int fileno = 0; fileno < nfiles; fileno++) {
    pthread_create(&threads[fileno], NULL, start_routine, (void*)filenames[fileno]);
  }
  for (int fileno = 0; fileno < nfiles; fileno++) {
    pthread_join(threads[fileno], NULL);
  }
  free(dirname);
  return 0;
}