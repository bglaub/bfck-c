#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "executor.h"
#include "identifier.h"

struct memory
{
  size_t pointer;
  size_t size;
  char * bank;
};

static struct memory * allocate_memory();
static struct memory * reallocate_memory(struct memory * memory);
static void free_memory(struct memory ** memory);
static void increment_data_pointer(struct memory * memory);
static void decrement_data_pointer(struct memory * memory);
static void increment_byte(struct memory * memory);
static void decrement_byte(struct memory * memory);
static void output_byte(struct memory * memory);
static void input_byte(struct memory * memory);
static void loop(struct tree_node * node, struct memory * memory);
static void execute_node(struct tree_node * node, struct memory * memory);

static struct memory * allocate_memory()
{
  struct memory * memory = malloc(sizeof(struct memory));

  if (memory == NULL) {
    return memory;
  }

  memory->pointer = 0;
  memory->size = 30000;
  memory->bank = calloc(memory->size, sizeof(char));

  if (memory->bank == NULL) {
    free(memory);
    memory = NULL;
  }

  return memory;
}

static struct memory * reallocate_memory(struct memory * memory)
{
  if (memory != NULL && memory->bank != NULL && memory->pointer > memory->size) {
    size_t new_size = 2 * memory->size;
    char * tmp = realloc(memory->bank, new_size * sizeof(char));

    if (tmp == NULL) {
      // handle
    }

    memset(tmp + (memory->size * sizeof(char)), 0, memory->size);

    memory->size = new_size;
    memory->bank = tmp;
  }

  return memory;
}

static void free_memory(struct memory ** memory)
{
  if (memory != NULL && *memory != NULL) {
    free((*memory)->bank);
    free(*memory);
    *memory = NULL;
  }
}

static void increment_data_pointer(struct memory * memory)
{
  memory->pointer++;
  reallocate_memory(memory);
}

static void decrement_data_pointer(struct memory * memory)
{
  if (memory->pointer == 0) {
    exit(1);
    // figure out what to truly do here
  }
  memory->pointer--;
}

static void increment_byte(struct memory * memory)
{
  memory->bank[memory->pointer]++;
}

static void decrement_byte(struct memory * memory)
{
  memory->bank[memory->pointer]--;
}

static void output_byte(struct memory * memory)
{
  printf("%c", memory->bank[memory->pointer]);
}

static void input_byte(struct memory * memory)
{
  scanf("%c", &memory->bank[memory->pointer]);
}

static void loop(struct tree_node * node, struct memory * memory)
{
  if (memory->bank[memory->pointer] == 0) {
    return;
  }

  size_t i;

  while (true) {
    for (i = 1; i < node->child_count - 1; i++) {
      execute_node(&node->children[i], memory);
    }
    if (memory->bank[memory->pointer] == 0) {
      return;
    }
  }
}

static void execute_node(struct tree_node * node, struct memory * memory)
{
  switch (node->identifier) {
    case INCREMENT_DATA_POINTER:
      increment_data_pointer(memory);
      break;
    case DECREMENT_DATA_POINTER:
      decrement_data_pointer(memory);
      break;
    case INCREMENT_BYTE:
      increment_byte(memory);
      break;
    case DECREMENT_BYTE:
      decrement_byte(memory);
      break;
    case OUTPUT_BYTE:
      output_byte(memory);
      break;
    case INPUT_BYTE:
      input_byte(memory);
      break;
    case LOOP:
      loop(node, memory);
      break;
    default:
      assert(0);
  }
}

void execute(struct tree_node * syntax_tree)
{
  if (syntax_tree == NULL || syntax_tree->child_count == 0) {
    return;
  }

  size_t i;
  struct memory * memory = allocate_memory();

  for (i = 0; i < syntax_tree->child_count; i++) {
    execute_node(&syntax_tree->children[i], memory);
  }

  free_memory(&memory);
}