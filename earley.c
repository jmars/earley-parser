#include "earley.h"
#include <limits.h>

static struct symbol *make_terminal(const char *match)
{
  struct symbol *symbol;

  symbol = GCALLOC(symbol, 2);
  symbol->type = TERMINAL;
  symbol->value = match;
  symbol->next = NULL;

  return symbol;
}

static struct symbol *make_nonterminal(const char *name)
{
  struct symbol *symbol;

  symbol = GCALLOC(symbol, 2);
  symbol->type = NON_TERMINAL;
  symbol->value = name;
  symbol->next = NULL;

  return symbol;
}

static struct rule *make_rule(const char *name)
{
  struct rule *rule;

  rule = GCALLOC(rule, 3);
  rule->name = name;
  rule->next = NULL;
  rule->symbols = NULL;

  return rule;
}

static struct item *make_item(struct rule *rule, size_t start)
{
  struct item *item;

  item = GCALLOC(item, 2);
  item->rule = rule;
  item->start = start;
  item->next = NULL;

  return item;
}

static struct state *make_state(struct item *items)
{
  struct state *state;

  state = GCALLOC(state, 2);
  state->items = items;
  state->next = NULL;

  return state;
}

static struct rule *rules_by_name(const char *name, struct rule *rule)
{
  if (rule == NULL) {
    return rule;
  }

  if (strcmp(name, rule->name) == 0) {
    struct rule *new = make_rule(rule->name);
    new->next = rules_by_name(name, new->next);
    return new;
  } else {
    return rules_by_name(name, rule->next);
  }
}

static struct item *items_of_rules(struct rule *rule, int start)
{ 
  if (rule == NULL) {
    return rule;
  }

  struct item *item = make_item(rule, start);
  item->next = items_of_rules(item->next, start);
  return item;
}

static struct state *init(const char *first, struct rule *rules)
{
  struct rule *rules = rules_by_name(first, rules);
  struct item *items = items_of_rules(rules, 0);
  struct state *state = make_state(items);

  return state;
}

static void item_loop();

static void state_loop();