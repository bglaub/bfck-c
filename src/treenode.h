#include "range.h"
#include "identifier.h"

#ifndef TREE_NODE_H
#define TREE_NODE_H

struct tree_node
{
  struct tree_node * parent;
  struct tree_node * children;
  size_t child_count;
  struct range range;
  enum identifier identifier;
};

#endif // TREE_NODE_H