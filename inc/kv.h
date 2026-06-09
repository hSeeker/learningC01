#include <stdlib.h>

#ifndef KV_H
#define KV_H

typedef struct {
  char *key;
  char *value;
} kv_entry_t;

typedef struct {
  size_t capacity;
  size_t count;
  kv_entry_t *entries;
} kv_table;

kv_table *kv_init(size_t capacity);

#endif
