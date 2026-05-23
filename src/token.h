#include "range.h"

#ifndef TOKEN_H
#define TOKEN_H

struct token
{
  char symbol;
  struct range range;
};

#endif // TOKEN_H