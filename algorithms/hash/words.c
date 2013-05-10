/* Sam Auciello | 2013 | Algorithms Exam
 * This file uses the hash table implementation in hash.c to create a histagram
 * of words in a file
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.c"
// non-word characters
#define DELIMETERS "\t \"'!@#$%^&*()-+_=,.<>0123456789;:?/[]{}\\|~`"

// linked list of words
typedef struct _list {
  char* word;
  struct _list* next;
}* list;

list list_push(list l, char* word) {
  list result = malloc(sizeof(struct _list));
  result->word = word;
  result->next = l;
  return result;
}

// determines whether the string contains a newline character and replaces it
// with '\0' if it does
bool end_of_line(char* word) {
  char* nl;
  if ((nl = strpbrk(word, "\n"))) {
    *nl = '\0';
    return true;
  }
  return false;
}

// converts the string to lower case
char* lower_case(char* string) {
  int i;
  for(i = 0; string[i]; i++){
    string[i] = tolower(string[i]);
  }
  return string;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("No file specified\n");
    return 1;
  }
  
  // a hash for storing word counts
  hash_table hash = new_hash();
  // a list of keys in the hash
  list unique_words;
  // open the specified file for reading
  FILE* f = fopen(argv[1], "r");
  // a buffer for lines read into the file
  char* line = malloc(sizeof(char) * 80);
  // a pointer into the line buffer
  char* tmp_line;
  // a temporary storage for word counts
  unsigned long count;
  // a pointer to specific word
  char* word;
  // a flag for whether the end of a line has been reached
  bool line_end;
  
  // for each line in the file
  while (fgets(line, 80, f)) {
    line_end = false;
    tmp_line = line;
    while (! line_end) {
	  // read the next word in the line
      word = malloc(sizeof(char) * 50);
      strcpy(word, strsep(&tmp_line, DELIMETERS));
      if (end_of_line(word)) {
        line_end = true;
      }
      if (strcmp(word, "") != 0) {
		// update the word cound hash
        lower_case(word);
        count = (unsigned long)hash_get(hash, word);
        if (count == 0) {
          unique_words = list_push(unique_words, word);
        }
        hash_set(hash, word, (void*)(count + 1));
      }
    }
  }
  
  // print the histagram
  while (unique_words != NULL) {
    printf("%s: %lu\n",
           unique_words->word,
           (unsigned long)hash_get(hash, unique_words->word));
    unique_words = unique_words->next;
  }
  
  return 0;
}
