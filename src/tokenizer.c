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

struct token_list * str_to_tokens(const char * str)
{
  if (str == NULL) {
    return NULL;
  }

  size_t str_length = strlen(str);

  if (str_length == 0) {
    return NULL;
  }

  struct token * tokens = malloc(str_length * sizeof(struct token));

  size_t current_symbol_index = 0;
  size_t token_count = 0;

  for (current_symbol_index = 0; current_symbol_index < str_length; current_symbol_index++) {
    if (is_token_symbol(str[current_symbol_index])) {
      tokens[token_count].symbol = str[current_symbol_index];
      tokens[token_count].range.start = current_symbol_index;
      tokens[token_count].range.end = current_symbol_index + 1;
      token_count++;
    }
  }

  if (token_count < str_length) {
    struct token * tmp = realloc(tokens, token_count * sizeof(struct token));

    if (tmp == NULL) {
      free(tokens);
      return NULL;
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
