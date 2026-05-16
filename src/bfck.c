#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileparser.h"

int main(int argc, char **argv) {
  
  if (argc != 2) {
    printf("Need to provide filename.\n");
    return 1;
  }

  char* fileStr = file_to_str(argv[1]);
/*
  char fileBuffer[2];
  char* fileStr = NULL;
  char* tmp = NULL;

  FILE *fptr;

  fptr = fopen(argv[1], "r");

  int i = 1;

  while(fgets(fileBuffer, 2, fptr)) {
    tmp = realloc(fileStr, i * 2 * sizeof(char));

    if (tmp == NULL) {
      printf("Unable to allocate more memory.");
      return 1;
    }

    fileStr = tmp;
    fileStr = strcat(fileStr, fileBuffer);

    i++;
  }

  free(tmp);
  
  fclose(fptr);
*/
  printf("%s\n", fileStr);

  return 0;
}