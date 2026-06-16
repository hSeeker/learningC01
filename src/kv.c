#include "kv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOMBSTONE ((char *)0x1)

size_t hash(char *val, int capacity) {
  size_t hash = 0x13371337deadbeef;
  while (*val) {
    hash ^= *val;
    hash = hash << 8;
    hash += *val;
    val++;
  }
  return hash % capacity;
}

void kv_free(kv_t *db) {
  if (!db)
    return;
  for (int i = 0; i < db->capacity - 1; i++) {
    kv_entry_t *entry = &db->entries[i];
    if (entry->key && entry->key != TOMBSTONE) {
      free(entry->key);
      free(entry->value);
      db->count--;
      entry->key = NULL;
      entry->value = NULL;
    }
  }
  free(db->entries);
  free(db);
  return;
}

int kv_delete(kv_t *db, char *key) {
  if (!db || !key)
    return -1;
  size_t idx = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    size_t real_idx = (idx + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];
    if (entry->key == NULL)
      return -1;
    if (entry->key && entry->key != TOMBSTONE && !strcmp(entry->key, key)) {
      free(entry->key);
      free(entry->value);
      db->count--;
      entry->key = TOMBSTONE;
      entry->value = NULL;
      return 0;
    }
  }
  return -1;
}

char *kv_get(kv_t *db, char *key) {
  if (!db || !key)
    return NULL;
  size_t idx = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    size_t real_idx = (idx + i) % db->capacity;
    kv_entry_t *entry = &db->entries[real_idx];
    if (entry->key == NULL || entry->key == TOMBSTONE)
      return NULL;
    if (entry->key && entry->key != TOMBSTONE && !strcmp(key, entry->key))
      return entry->value;
  }
  return NULL;
}

int kv_put(kv_t *db, char *key, char *value) {
  if (!db || !key || !value)
    return -1;
  size_t idx = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i++) {
    size_t real_idx = (idx + i) % db->capacity;

    kv_entry_t *entry = &db->entries[real_idx];

    if (entry->key && entry->key != (void *)TOMBSTONE &&
        !strcmp(key, entry->key)) {
      char *newval = strdup(value);
      if (!newval)
        return -1;
      free(entry->value);
      entry->value = newval;
      return 0;
      // return real_idx;
    }

    if (!entry->key || entry->key == (void *)TOMBSTONE) {
      char *newval = strdup(value);
      char *newkey = strdup(key);
      if (!newval || !newkey) {
        free(newval);
        free(newkey);
        return -1;
      }
      entry->key = newkey;
      entry->value = newval;
      db->count++;
      return 0;
      // return real_idx;
    }
  }
  return -2;
}

kv_t *kv_init(size_t capacity) {
  if (capacity == 0)
    return NULL;
  kv_t *table = malloc(sizeof(kv_t));
  if (table == NULL)
    return NULL;
  table->capacity = capacity;
  table->count = 0;
  table->entries = calloc(sizeof(kv_entry_t), capacity);
  if (table->entries == NULL)
    return NULL;
  return table;
}
