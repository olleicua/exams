/* Sam Auciello | 2013 | languages Exam
 * This program reads in people from people.csv constructs a linked family tree
 * structure from it, then provides a console interface to navigate the tree.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _person *person;
typedef struct _people *people;

struct _person {
  char* first_name;
  char* last_name;
  int father_id; // the index of the parent in the csv file
  int mother_id;
  person father; // a link the the actual parent struct
  person mother;
  people children; // a list of children
  int born;
  int died;
};

// lists of people are stored as a linked list
struct _people {
  person car; // the first element of the list
  people cdr; // the sublist following the first element
};

// allocate space for a new person
person new_person() {
  person result = malloc(sizeof(struct _person));
  result->first_name = malloc(sizeof(char) * 40);
  result->last_name = malloc(sizeof(char) * 40);
  return result;
}

// add a person to people linked list.  This should be used with something like:
// people list;
// person jane;
// list = people_push(list, jane);
people people_push(people list, person p) {
  people result = malloc(sizeof(struct _people));
  result->car = p;
  result->cdr = list;
  return result;
}

// print out the person in form "Jane Doe (1902 - 1987)\n"
// prints "N/A\n" for the NULL person
void print_person(person p) {
  if (p == NULL) {
	printf("N/A\n");
  } else {
	printf("%s %s (%i - ", p->first_name, p->last_name, p->born);
	if (p->died < 0) {
	  printf("present)\n");
	} else {
	  printf("%i)\n", p->died);
	}
  }
}

// print each person in the list
void print_people(people p) {
  for (; p != NULL; p = p->cdr) {
	print_person(p->car);
  }
}

// find the spouce of the person if there is one
person spouce(person p) {
  if (p->children == NULL) {
	return NULL;
  }
  if (p->children->car->father == p) {
	return p->children->car->mother;
  }
  return p->children->car->father;
}

// print the person, their parents, their spouce, and their children
void person_info(person p) {
  printf("\n");
  print_person(p);
  printf("\nMother: ");
  print_person(p->mother);
  printf("Father: ");
  print_person(p->father);
  if (p->children != NULL) {
	printf("Spouce: ");
	print_person(spouce(p));
	printf("Children:\n");
	print_people(p->children);
  }
}

// find the person corresponding to the given index into the people list
person nth_person(people list, int n) {
  if (list == NULL) {
	return NULL;
  }
  people p = list;
  int i = 0;
  while (p->cdr != NULL && i < n) {
	i++;
	p = p->cdr;
  }
  if (i == n) {
	return p->car;
  }
  return NULL;
}

// generate a people list from a .csv file
people load_people(FILE* csv_file) {
  people result = NULL, last_person, p;
  char* line_buf = malloc(sizeof(char) * 80);
  fgets(line_buf, 80, csv_file); // ignore header
  while (fgets(line_buf, 80, csv_file)) {
	
	// each line
	
	// make sure last_person points to an empty people list at the end of the
	// linked result list
	if (result == NULL) {
	  result = last_person = malloc(sizeof(struct _people));
	} else {
	  last_person->cdr = malloc(sizeof(struct _people));
	  last_person = last_person->cdr;
	}
	
	// add the next person at the end
	last_person->car = new_person();
	sscanf(line_buf, "%*i,%[^,],%[^,],%i,%i,%i,%i",
		  last_person->car->first_name,
		  last_person->car->last_name,
		  &last_person->car->father_id,
		  &last_person->car->mother_id,
		  &last_person->car->born,
		  &last_person->car->died);
  }
  
  // create links to parents and children
  for (p = result; p != NULL; p = p->cdr) {
	if (p->car->father_id >= 0) {
	  p->car->father = nth_person(result, p->car->father_id);
	  p->car->father->children = people_push(p->car->father->children, p->car);
	}
	if (p->car->mother_id >= 0) {
	  p->car->mother = nth_person(result, p->car->mother_id);
	  p->car->mother->children = people_push(p->car->mother->children, p->car);
	}
  }
  return result;
}

int main() {
  
  // setup
  FILE* f = fopen("people.csv", "r");
  people list = load_people(f);
  person current_person = list->car;
  char* command = malloc(sizeof(char) * 80);
  
  // command prompt loop
  while (true) {
	person_info(current_person);
	printf("\nEnter a relative to navigate to (mother, father, spouce, child_n): ");
	gets(command);
	if (strcmp(command, "quit") == 0) {
	  break;
	} else if (strcmp(command, "mother") == 0) {
	  if (current_person->mother == NULL) {
		printf("\n! no mother available\n");
	  } else {
		current_person = current_person->mother;
	  }
	} else if (strcmp(command, "father") == 0) {
	  if (current_person->father == NULL) {
		printf("\n! no father available\n");
	  } else {
		current_person = current_person->father;
	  }
	} else if (strcmp(command, "spouce") == 0) {
	  if (spouce(current_person) == NULL) {
		printf("\n! no spouce available\n");
	  } else {
		current_person = spouce(current_person);
	  }
	} else if (strncmp(command, "child_", 6) == 0) {
	  int n = atoi(&command[6]);
	  if (nth_person(current_person->children, n) == NULL) {
		printf("\n! no child %i available\n", n);
	  } else {
		current_person = nth_person(current_person->children, n);
	  }
	} else {
	  printf("\n! invalid command: %s\n", command);
	}
  }
  
  return 0;
}
