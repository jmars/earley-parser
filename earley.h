#include "bgc/gc.h"
#include <string.h>

enum symbol_type
{
  TERMINAL,
  NON_TERMINAL
};

union symbol_value {
  struct
  {
    const char *match;
  };
  struct
  {
    struct earley_symbol *symbols;
    char length;
  };
};

struct earley_symbol
{
  union symbol_value *value;
  enum symbol_type type;
};

struct earley_symbol *make_symbol(
    enum symbol_type type,
    union symbol_value value);

struct earley_rule
{
  struct earley_symbol *symbols;
  const char *name;
};

struct earley_item
{
  struct earley_rule rule;
};