/* Sam Auciello | 2013 | Algorithms Exam
 * This file implements a general purpose hash table
 */

#include <stdlib.h>
#include <string.h>

// A linked list "bucket" for handling collisions
typedef struct _bucket *bucket;
struct _bucket {
  char* key;
  void* value;
  bucket next;
};

// A hash table
typedef struct _hash_table *hash_table;
struct _hash_table {
  int elements; // the number of non-null key/value pairs currently in the hash
  bucket* array; // allocated space for the data
};

// function based on the CRC variant described at:
// http://www.cs.hmc.edu/~geoff/classes/hmc.cs070.200101/homework10/hashfuncs.html
int hash_func(char* key) {
  int i, highorder, result = 0;
  for (i = 0; key[i]; i++) {
    highorder = result & 0xe0;
    result = result << 3;
    result ^= (highorder >> 5);
    result ^= key[i];
  }
  return result & 0xff;
}

// Create a new hash table and allocate 256 buckets
hash_table new_hash() {
  hash_table result = malloc(sizeof(struct _hash_table));
  result->elements = 0;
  result->array = malloc(sizeof(bucket) * 256);
  return result;
}

// Create a new bucket containing the key/value pair
bucket new_bucket(char* key, void* value) {
  bucket result = malloc(sizeof(struct _bucket));
  result->key = key;
  result->value = value;
  return result;
}

// If a bucket for the given key exists update the value, otherwise add a new
// bucket for the pair.  Either way update hash->elements appropriately.
void hash_set(hash_table hash, char* key, void* value) {
  bucket* location = &hash->array[hash_func(key)];
  while (*location != NULL) { // look at each node in this "bucket"
    if (strcmp(key, (*location)->key) == 0) {
      // matching key found: update value
      (*location)->value = value;
      if (value == NULL) {
        hash->elements--;
      }
      return;
    }
    // key doesn't match: move to the next one
    location = &((*location)->next);
  }
  // no matching key found: add a new bucket
  if (value != NULL) {
    *location = new_bucket(key, value);
    hash->elements++;
  }
}

// If a bucket for the given key exists return the value, otherwise return NULL
void* hash_get(hash_table hash, char* key) {
  bucket location = hash->array[hash_func(key)];
  while (location != NULL) { // look at each node in this "bucket"
    // matching key found: return value
    if (strcmp(key, location->key) == 0) {
      return location->value;
    }
    // key doesn't match: move to the next one
    location = location->next;
  }
  // no matching key found: return NULL
  return NULL;
}
