#include "bgc/gc.h"
#include <string.h>

enum symbol_type
{
  TERMINAL,
  NON_TERMINAL
};

// TERMINAL | NONTERMINAL
struct symbol
{
  struct symbol *next;
  const char *value;
  enum symbol_type type;
};

// NAME := NONTERMINAL TERMINAL NONTERMINAL
struct rule
{
  struct symbol *symbols; // SYMBOL[]
  const char *name;
  struct rule *next;
};

// NAME := NONTERMINAL TERMINAL * NONTERMINAL
struct item
{
  struct item *next;
  struct rule *rule; // RULE
  size_t start;
};

#define SKIPLIST_MAX_LEVEL 6

struct state
{
  struct state *next;
  struct item *items; // ITEM[]
};