#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileparser.h"


char * file_to_str(char * fileName)
{
  char buffer[2];
  char* str = NULL;
  char* tmp = NULL;

  FILE *fptr;

  fptr = fopen(fileName, "r");

  int i = 1;

  while(fgets(buffer, 2, fptr)) {
    tmp = realloc(str, i * 2 * sizeof(char));

    if (tmp == NULL) {
      printf("Unable to allocate more memory.");
      return NULL; // handle error
    }

    str = tmp;
    str = strcat(str, buffer);

    i++;
  }

  free(tmp);
  
  fclose(fptr);

  return str;
}