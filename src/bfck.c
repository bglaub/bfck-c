#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileparser.h"
#include "token.h"
#include "tokenlist.h"
#include "tokenizer.h"

int main(int argc, char **argv) {
  
  if (argc != 2) {
    printf("Need to provide filename.\n");
    return 1;
  }

  char * fileStr = file_to_str(argv[1]);
  struct token_list tokenlist = parse_tokens(fileStr);

  // the tokens have everything to move forward, so free the file string from memory
  free(fileStr);

  unsigned int currentTokenIndex;

  for(currentTokenIndex = 0; currentTokenIndex < tokenlist.size; currentTokenIndex++) {
    struct token token = tokenlist.tokens[currentTokenIndex];
    printf("symbol: %c\n", token.symbol);
    printf("start: %d\n", token.position.start);
    printf("end: %d\n", token.position.end);
    printf("\n");
  }

  free(tokenlist.tokens);

  return 0;
}