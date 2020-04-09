#include "earley.h"

struct earley_symbol *make_symbol(
    enum symbol_type type,
    union symbol_value value)
{
  return (struct earley_symbol *)gcalloc(sizeof(struct earley_symbol), 1);
}