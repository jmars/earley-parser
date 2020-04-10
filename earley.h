#include "bgc/gc.h"
#include <string.h>

enum symbol_type
{
  TERMINAL,
  NON_TERMINAL
};

// TERMINAL | NONTERMINAL
struct earley_symbol
{
  struct earley_symbol *next;
  const char *value;
  enum symbol_type type;
};

// NAME := NONTERMINAL TERMINAL NONTERMINAL
struct earley_rule
{
  struct earley_symbol *symbols; // SYMBOL[]
  const char *name;
};

// NAME := NONTERMINAL TERMINAL * NONTERMINAL
struct earley_item
{
  struct earley_item *next;
  struct earley_rule *rule; // RULE
  size_t progress;
  size_t start;
};

#define SKIPLIST_MAX_LEVEL 6

struct earley_state
{
  struct earley_state *next;
  struct earley_item *items; // ITEM[]
};