#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "identifier.h"


enum identifier get_identifier(struct token * token) {
  if(token->symbol == '>') {
    return INCREMENT_DATA_POINTER;
  } else if (token->symbol == '<') {
    return DECREMENT_DATA_POINTER;
  } else if (token->symbol == '+') {
    return INCREMENT_BYTE;
  } else if (token->symbol == '-') {
    return DECREMENT_BYTE;
  } else if (token->symbol == '.') {
    return OUTPUT_BYTE;
  } else if (token->symbol == ',') {
    return INPUT_BYTE;
  } else if (token->symbol == '[') {
    return MOVE_FORWARD_INSTRUCTION_POINTER;
  } else if (token->symbol == ']') {
    return MOVE_BACKWARD_INSTRUCTION_POINTER;
  }

  // this should never ever happen
}

static struct treenode *build_syntax_tree(struct treenode * currentNode, struct token_list *tokenlist, unsigned int currentTokenIndex)
{
  if(tokenlist->size <= currentTokenIndex) {
    printf("Breaking Loop\n");
    if(currentNode->identifier != PROGRAM_START) {
      // started loop with no ending close symbol "]"
      // need to exit, but for now ignore
    }
    return currentNode;
  }

  struct treenode * nextNode = currentNode;
  struct token * currentToken = &(tokenlist->tokens[currentTokenIndex]);

  printf("--------------------------------------------------------------------------\n");
  printf("Starting on token: %d, %c\n", currentTokenIndex, currentToken->symbol);
  printf("Current node identifier: %d\n", currentNode->identifier);
  printf("Current node child count: %d\n", currentNode->child_count);
  printf("--------------------------------------------------------------------------\n");

  if(currentToken->symbol == '[') {

    printf("Creating loop node.\n");
    struct treenode * tmp = realloc(currentNode->children, (currentNode->child_count + 1) * sizeof(struct treenode));
    
    if (tmp == NULL) {
      // handle bad condition
    }

    currentNode->children = tmp;
    currentNode->children[currentNode->child_count].parent = currentNode;
    currentNode->children[currentNode->child_count].children = NULL;
    currentNode->children[currentNode->child_count].child_count = 0;
    currentNode->children[currentNode->child_count].identifier = LOOP;
    currentNode->children[currentNode->child_count].range.start = currentToken->range.start;
    currentNode->child_count++;

    
    printf("Current node child count: %d\n", currentNode->child_count);
    printf("Loop node child count: %d\n", currentNode->children[currentNode->child_count - 1].child_count);

    currentNode = &(currentNode->children[currentNode->child_count - 1]);
    nextNode = currentNode;

    printf("Current node identifier: %d\n", currentNode->identifier);
    printf("Current node child count: %d\n", currentNode->child_count);

  } else if(currentToken->symbol == ']') {
    if(currentNode->identifier != LOOP) {
      // ended loop with no beginning symbol "["
      // need to exit, but for now ignore
    }
    currentNode->range.end = currentToken->range.end;
    nextNode = currentNode->parent;
  }

  struct treenode * tmp = realloc(currentNode->children, (currentNode->child_count + 1) * sizeof(struct treenode));
  
  if (tmp == NULL) {
    // handle bad condition
  }

  currentNode->children = tmp;
  currentNode->children[currentNode->child_count].parent = currentNode;
  currentNode->children[currentNode->child_count].children = NULL;
  currentNode->children[currentNode->child_count].child_count = 0;
  currentNode->children[currentNode->child_count].identifier = get_identifier(currentToken);
  currentNode->children[currentNode->child_count].range.start = currentToken->range.start;
  currentNode->children[currentNode->child_count].range.end = currentToken->range.end;
  currentNode->child_count++;

  build_syntax_tree(nextNode, tokenlist, ++currentTokenIndex);
}

struct treenode *parse_tree(struct token_list *tokenlist)
{
  if (tokenlist == NULL || tokenlist->size <= 0) {
    // what do we do here
    return NULL;
  }

  struct treenode *syntax_tree = malloc(sizeof(struct treenode));
  syntax_tree[0].parent = NULL;
  syntax_tree[0].children = NULL;
  syntax_tree[0].child_count = 0;
  syntax_tree[0].identifier = PROGRAM_START;
  syntax_tree[0].range.start = tokenlist->tokens[0].range.start;
  syntax_tree[0].range.end = tokenlist->tokens[tokenlist->size - 1].range.end;

  printf("Token Count: %d\n", tokenlist->size);
  printf("Building Tree.\n");

  syntax_tree = build_syntax_tree(syntax_tree, tokenlist, 0);
  
  printf("Tree Built");

  return syntax_tree;
}