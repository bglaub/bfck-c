#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "tokenlist.h"
#include "tokenizer.h"

struct token_list parse_tokens(const char * str)
{
  unsigned int strLen = strlen(str);

  struct token * tokens = malloc(strLen * sizeof(struct token));

  unsigned int currentSymbolIndex = 0;
  unsigned int tokenCount = 0;
  unsigned int column = 1;
  unsigned int line = 1;

  for(currentSymbolIndex = 0; currentSymbolIndex < strLen; currentSymbolIndex++) {
    if(is_token_symbol(str[currentSymbolIndex])) {
      tokens[tokenCount].symbol = str[currentSymbolIndex];
      tokens[tokenCount].position.column = column;
      tokens[tokenCount].position.line = line;
      tokenCount++;
    } else if(str[currentSymbolIndex] == '\n') {
      column = 0;
      line++;
    }
    column++;
  }

  struct token * tmp = realloc(tokens, tokenCount * sizeof(struct token));

  if(tmp == NULL) {
    printf("Unable to reallocate token size.");
    exit(EXIT_FAILURE);
  }

  tokens = tmp;

  return (struct token_list) {
    .tokens = tokens,
    .size = tokenCount
  };
}

bool is_token_symbol(char symbol)
{
  switch(symbol) {
    case '>':
    case '<':
    case '[':
    case ']':
    case '+':
    case '-':
    case '.':
    case ',':
      return true;
    default:
      return false;
  }
}