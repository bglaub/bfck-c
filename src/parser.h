#include "tokenlist.h"
#include "treenode.h"

#ifndef PARSER_H
#define PARSER_H

struct tree_node * parse_tree(struct token_list * tokenlist);

#endif // PARSER_H