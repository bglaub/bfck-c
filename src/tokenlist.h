#include "token.h"

#ifndef TOKENLIST_H
#define TOKENLIST_H

struct token_list {
  struct token * tokens;
  unsigned int size;
};

#endif // TOKENLIST_H