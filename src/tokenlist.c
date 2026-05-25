#include "tokenlist.h"

#include <stdlib.h>


void free_token_list(struct token_list ** token_list)
{
  if (token_list != NULL && *token_list != NULL) {
    free((*token_list)->tokens);
    free(*token_list);
    *token_list = NULL;
  }
}