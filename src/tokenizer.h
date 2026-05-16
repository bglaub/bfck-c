#include <stdbool.h>

#ifndef TOKENIZER_H
#define TOKENIZER_H

struct token_list parse_tokens(const char * str);

bool is_token_symbol(char symbol);

#endif // TOKENIZER_H