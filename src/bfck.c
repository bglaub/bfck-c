#include <stdlib.h>
#include <stdio.h>

#include "executor.h"
#include "fileparser.h"
#include "parser.h"
#include "tokenlist.h"
#include "tokenizer.h"


int main(int argc, char ** argv)
{
  if (argc != 2) {
    printf("Need to provide filename.\n");
    return 1;
  }

  char * file_str = file_to_str(argv[1]);

  if (file_str == NULL) {
    printf("Unable to read program into memory.");
    exit(1);
  }

  struct token_list * token_list = str_to_tokens(file_str);

  free(file_str);

  if (token_list == NULL) {
    printf("Unable to read program into memory.");
    exit(1);
  }

  struct tree_node * syntax_tree = parse_tree(token_list);

  free_token_list(&token_list);

  execute(syntax_tree);

  return 0;
}