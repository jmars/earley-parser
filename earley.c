#include "earley.h"
#include <limits.h>

#define GCALLOC(type, ptrs) ((struct type *)gcalloc(sizeof(struct type), 2))

static struct earley_symbol *make_terminal(const char *match)
{
  struct earley_symbol *symbol;

  symbol = GCALLOC(earley_symbol, 2);
  symbol->type = TERMINAL;
  symbol->value = match;

  return symbol;
}

static struct earley_symbol *make_nonterminal(const char *name)
{
  struct earley_symbol *symbol;

  symbol = GCALLOC(earley_symbol, 2);
  symbol->type = NON_TERMINAL;
  symbol->value = name;

  return symbol;
}

static struct earley_rule *make_rule(const char *name)
{
  struct earley_rule *rule;

  rule = GCALLOC(earley_rule, 2);
  rule->name = name;

  return rule;
}

static void cons_symbol(struct earley_symbol *symbol, struct earley_rule *rule)
{
  symbol->next = rule->symbols;
  rule->symbols = symbol;
}

static struct earley_item *make_item(struct earley_rule *rule, size_t start, size_t progess)
{
  struct earley_item *item;

  item = GCALLOC(earley_item, 2);
  item->rule = rule;
  item->start = start;
  item->progress = progess;

  return item;
}

static void cons_item(struct earley_item *head, struct earley_item *tail)
{
  head->next = tail;
}

static struct earley_state *make_state(struct earley_item *items)
{
  struct earley_state *state;

  state = GCALLOC(earley_state, 2);
  state->items = items;

  return state;
}

static void state_cons(struct earley_state *head, struct earley_state *tail)
{
  head->next = tail;
}