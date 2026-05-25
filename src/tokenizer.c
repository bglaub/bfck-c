#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "tokenlist.h"
#include "tokenizer.h"


static bool is_token_symbol(char symbol)
{
  switch (symbol) {
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

struct token_list * parse_tokens(const char * str)
{
  if (str == NULL) {
    return NULL;
  }

  size_t str_length = str_length(str);

  if (str_length == 0) {
    return NULL;
  }

  struct token * tokens = malloc(str_length * sizeof(struct token));

  unsigned int currentSymbolIndex = 0;
  unsigned int tokenCount = 0;
  unsigned int characterCount = 0;

  for (currentSymbolIndex = 0; currentSymbolIndex < str_length; currentSymbolIndex++) {
    if (is_token_symbol(str[currentSymbolIndex])) {
      tokens[tokenCount].symbol = str[currentSymbolIndex];
      tokens[tokenCount].range.start = characterCount;
      tokens[tokenCount].range.end = characterCount + 1;
      tokenCount++;
    }
    characterCount++;
  }

  if (tokenCount < str_length) {
    struct token * tmp = realloc(tokens, tokenCount * sizeof(struct token));

    if (tmp == NULL) {
      printf("Unable to reallocate token size.");
      exit(EXIT_FAILURE);
    }

    tokens = tmp;
  }

  struct token_list * token_list = malloc(sizeof(struct token_list));

  if (token_list == NULL) {
    free(tokens);
    return NULL;
  }

  token_list->tokens = tokens;
  token_list->size = token_count;

  return token_list;
}
