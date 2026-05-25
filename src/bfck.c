#include <stdlib.h>
#include <stdio.h>

#include "fileparser.h"
#include "tokenlist.h"
#include "tokenizer.h"
#include "parser.h"

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

  struct token_list * token_list = parse_tokens(file_str);

  free(file_str);

  if (token_list == NULL) {
    printf("Unable to read program into memory.");
    exit(1);
  }

  struct treenode * syntax_tree = parse_tree(token_list);

  free(token_list.tokens);
  free(token_list);

  return 0;
}