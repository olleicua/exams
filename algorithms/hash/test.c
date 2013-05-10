/* Sam Auciello | 2013 | Algorithms Exam
 * This demonstrates the use of the hash table api found in hash.c
 */

#include <stdio.h>
#include "hash.c"

void hash_set_print(hash_table hash, char* key, char* value) {
  hash_set(hash, key, value);
  printf("> hash['%s'] = '%s'\n", key, value);
}

void hash_get_print(hash_table hash, char* key) {
  printf("> hash['%s']\n'%s'\n", key, (char*)hash_get(hash, key));
}

int main() {
  hash_table hash = new_hash();
  hash_set_print(hash, "foo", "bar");
  hash_set_print(hash, "baz", "qux");
  // '@B', '`C', and ' A' are all designed specifically to have the same hash
  // so as to test that the hash has the correct behavior when there is a collision.
  hash_set_print(hash, "@B", "a");
  hash_set_print(hash, "`C", "b");
  hash_get_print(hash, "foo");
  hash_get_print(hash, "baz");
  hash_set_print(hash, "baz", "snap");
  hash_get_print(hash, "baz");
  hash_get_print(hash, "thingy");
  hash_get_print(hash, " A");
  hash_get_print(hash, "@B");
  hash_get_print(hash, "`C");
  hash_set_print(hash, "`C", NULL);
  hash_get_print(hash, "`C");
  hash_set_print(hash, "xyzzy", NULL);
  hash_get_print(hash, "xyzzy");
  printf("> hash->size\n%d\n", hash->elements);
  
  return 0;
}
