#include "earley.h"

int main() {
  uintptr_t stack_root;
  struct gc_state gcs = gcinit(4096, &stack_root, NULL);

  printf("test");

  gcfree(gcs);
  return 0;
}