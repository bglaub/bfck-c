#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileparser.h"
#include "token.h"
#include "tokenlist.h"
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Need to provide filename.\n");
    return 1;
  }

  char *fileStr = file_to_str(argv[1]);
  struct token_list tokenlist = parse_tokens(fileStr);

  // the tokens have everything to move forward, so free the file string from memory
  free(fileStr);

  struct treenode *syntax_tree = parse_tree(&tokenlist);

  free(tokenlist.tokens);

  return 0;
}