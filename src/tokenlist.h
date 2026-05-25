#include <stddef.h>

#include "token.h"

#ifndef TOKENLIST_H
#define TOKENLIST_H

struct token_list
{
  struct token * tokens;
  size_t size;
};

void free_token_list(struct token_list ** token_list);

#endif // TOKENLIST_H