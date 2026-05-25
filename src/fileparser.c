#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileparser.h"

char * file_to_str(const char * const file_name)
{
  char buffer[2];
  char * str = NULL;
  char * tmp = NULL;

  FILE * fptr;

  fptr = fopen(file_name, "r");

  size_t i = 1;

  while (fgets(buffer, 2, fptr)) {
    tmp = realloc(str, i * 2 * sizeof(char));

    if (tmp == NULL) {
      free(str);
      return NULL;
    }

    str = tmp;

    str = strcat(str, buffer);

    i++;
  }

  fclose(fptr);

  return str;
}