#include "kv.h"
#include "test.h"
#include <stdio.h>

int main() {
  printf("test main\n");
  kv_t *table = kv_init(1024);
  kv_put(table, "hehe", "huh");
  kv_put(table, "hehe", "huh, wtf?");
  kv_put(table, "lala", "huh");
  for (int i = 0; i < table->capacity; i++)
    if (table->entries[i].key)
      printf("[%d]: %s, %s\n", i, table->entries[i].key,
             table->entries[i].value);
  free(table);
  return 0;
}
