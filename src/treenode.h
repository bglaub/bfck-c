#include "range.h"
#include "identifier.h"

#ifndef TREENODE_H
#define TREENODE_H

struct treenode
{
  struct treenode * parent;
  struct treenode * children;
  unsigned int child_count;
  struct range range;
  enum identifier identifier;
};

#endif // TREENODE_H