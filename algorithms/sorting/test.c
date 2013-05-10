/* Sam Auciello | 2013 | Algorithms Exam
 * This file tests my implementation of quicksort, mergesort, and heapsort on
 * five prepared inputs of size 10, 20, 30, 40, and 50 respectively.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// a counter to measure the complexity of the three algorithms
int steps;

// the "xor swap trick" swaps two numbers in place
void swap(int *a, int *b) {
  if (a != b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
  }
}

#include "quicksort.c"
#include "mergesort.c"
#include "heapsort.c"

// print a list of numbers as they would appear in a python list
void print_numbers(int* numbers, int size) {
  int i;
  printf("[ %d", numbers[0]);
  for (i = 1; i < size; i++) {
    printf(", %d", numbers[i]);
  }
  printf(" ]\n");
}

// verify that the list of numbers is in ascending order
bool check(int* numbers, int size) {
  int i;
  for (i = 1; i < size; i++) {
    if (numbers[i] < numbers[i - 1]) {
      return false;
    }
  }
  return true;
}

// test quicksort on a list of numbers reporting and verifying the results and
// reporting the number of steps taken
void quicksort_test(int* numbers, int size) {
  steps = 0;
  quicksort(numbers, size);
  printf("after quicksort:\n");
  print_numbers(numbers, size);
  if (check(numbers, size)) {
    printf("SORTED!\n");
  } else {
    printf("BUG!\n");
  }
  printf("steps: %d\n\n", steps);
}

// test mergesort on a list of numbers reporting and verifying the results and
// reporting the number of steps taken
void mergesort_test(int* numbers, int size) {
  steps = 0;
  int* sorted = my_mergesort(numbers, size);
  printf("after mergesort:\n");
  print_numbers(sorted, size);
  if (check(sorted, size)) {
    printf("SORTED!\n");
  } else {
    printf("BUG!\n");
  }
  printf("steps: %d\n\n", steps);
}

// test heapsort on a list of numbers reporting and verifying the results and
// reporting the number of steps taken
void heapsort_test(int* numbers, int size) {
  steps = 0;
  my_heapsort(numbers, size);
  printf("after heapsort:\n");
  print_numbers(numbers, size);
  if (check(numbers, size)) {
    printf("SORTED!\n");
  } else {
    printf("BUG!\n");
  }
  printf("steps: %d\n\n", steps);
}

// return a copy of the list
int* copy_list(int* numbers, int size) {
  int* result = malloc(sizeof(int) * size);
  int i;
  for (i = 0; i < size; i++) {
    result[i] = numbers[i];
  }
  return result;
}

// test all three algorithms on a given list
void test(int* numbers, int size) {
  int log2n = size * (int)log2((double)size);
  printf("size: %d\nn*log_2(n): %d\n", size, log2n);
  printf("initial list:\n");
  print_numbers(numbers, size);
  printf("\n");
  quicksort_test(copy_list(numbers, size), size);
  mergesort_test(copy_list(numbers, size), size);
  heapsort_test(copy_list(numbers, size), size);
  printf(" ---\n");
}

int main() {
  // these lists were generated using:
  // $ ruby -e"p n.times.map{rand 100}"
  
  int test1[10] = { 11, 69, 24, 18, 51, 69, 66, 49, 95, 81 };
  test(test1, 10);
  
  int test2[20] = { 80, 92, 41, 75, 64, 6, 2, 70, 11, 97, 95, 46, 89, 96, 45,
					38, 29, 82, 14, 24 };
  test(test2, 20);
  
  int test3[30] = { 42, 75, 44, 34, 6, 55, 90, 88, 49, 40, 2, 89, 97, 68, 87,
					54, 35, 8, 94, 32, 11, 65, 33, 79, 49, 46, 80, 28, 58, 56 };
  test(test3, 30);
  
  int test4[40] = { 98, 7, 96, 18, 17, 89, 16, 5, 99, 39, 6, 72, 36, 73, 83, 44,
					59, 55, 76, 15, 19, 54, 5, 16, 43, 21, 6, 46, 82, 0, 70, 72,
					63, 37, 28, 42, 13, 83, 26, 60 };
  test(test4, 40);
  
  int test5[50] = { 72, 10, 36, 50, 12, 43, 41, 55, 83, 8, 66, 69, 11, 46, 24,
					84, 84, 74, 3, 33, 75, 86, 54, 83, 73, 64, 84, 20, 94, 68,
					29, 69, 32, 96, 83, 32, 87, 22, 6, 96, 91, 7, 24, 30, 21,
					39, 36, 60, 3, 81 };
  test(test5, 50);
  
  return 0;
}