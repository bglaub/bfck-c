#include "position.h"

#ifndef TOKEN_H
#define TOKEN_H

struct token {
  char symbol;
  struct position position;
};

#endif // TOKEN_H