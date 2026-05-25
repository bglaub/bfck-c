#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "identifier.h"


static enum identifier get_identifier(struct token * token)
{
  switch (token->symbol) {
    case '>':
      return INCREMENT_DATA_POINTER;
    case '<':
      return DECREMENT_DATA_POINTER;
    case '+':
      return INCREMENT_BYTE;
    case '-':
      return DECREMENT_BYTE;
    case '.':
      return OUTPUT_BYTE;
    case ',':
      return INPUT_BYTE;
    case '[':
      return MOVE_FORWARD_INSTRUCTION_POINTER;
    case ']':
      return MOVE_BACKWARD_INSTRUCTION_POINTER;
    default:
      assert(0);
  }
}

static struct tree_node * build_syntax_tree(struct tree_node * current_node, struct token_list * token_list,
                                            size_t current_token_index)
{
  if (token_list->size <= current_token_index) {
    if (current_node->identifier != PROGRAM_START) {
      // started loop with no ending close symbol "]"
      // need to cleanup tree at this point.
    }
    return current_node;
  }

  struct tree_node * next_node = current_node;
  struct token * current_token = &(token_list->tokens[current_token_index]);

  if (current_token->symbol == '[') {
    struct tree_node * tmp =
      realloc(current_node->children, (current_node->child_count + 1) * sizeof(struct tree_node));

    if (tmp == NULL) {
      // handle bad condition
    }

    current_node->children = tmp;
    current_node->children[current_node->child_count].parent = current_node;
    current_node->children[current_node->child_count].children = NULL;
    current_node->children[current_node->child_count].child_count = 0;
    current_node->children[current_node->child_count].identifier = LOOP;
    current_node->children[current_node->child_count].range.start = current_token->range.start;
    current_node->child_count++;

    current_node = &(current_node->children[current_node->child_count - 1]);
    next_node = current_node;

  } else if (current_token->symbol == ']') {
    if (current_node->identifier != LOOP) {
      // ended loop with no beginning symbol "["
      // need to exit, but for now ignore
    }
    current_node->range.end = current_token->range.end;
    next_node = current_node->parent;
  }

  struct tree_node * tmp = realloc(current_node->children, (current_node->child_count + 1) * sizeof(struct tree_node));

  if (tmp == NULL) {
    // handle bad condition
  }

  current_node->children = tmp;
  current_node->children[current_node->child_count].parent = current_node;
  current_node->children[current_node->child_count].children = NULL;
  current_node->children[current_node->child_count].child_count = 0;
  current_node->children[current_node->child_count].identifier = get_identifier(current_token);
  current_node->children[current_node->child_count].range.start = current_token->range.start;
  current_node->children[current_node->child_count].range.end = current_token->range.end;
  current_node->child_count++;

  build_syntax_tree(next_node, token_list, ++current_token_index);
}

struct tree_node * parse_tree(struct token_list * token_list)
{
  if (token_list == NULL || token_list->size <= 0) {
    return NULL;
  }

  struct tree_node * syntax_tree = malloc(sizeof(struct tree_node));
  syntax_tree[0].parent = NULL;
  syntax_tree[0].children = NULL;
  syntax_tree[0].child_count = 0;
  syntax_tree[0].identifier = PROGRAM_START;
  syntax_tree[0].range.start = token_list->tokens[0].range.start;
  syntax_tree[0].range.end = token_list->tokens[token_list->size - 1].range.end;

  syntax_tree = build_syntax_tree(syntax_tree, token_list, 0);

  return syntax_tree;
}