/* Sam Auciello | 2013 | Algorithms Exam
 * This file contains an array-based implementation of heapsort
 */

// merge two sorted lists into a larger sorted list containing the union of the
// two lists
int* merge(int* list1, int size1, int* list2, int size2) {
  int* result = malloc(sizeof(int) * (size1 + size2));
  int result_index, list1_index, list2_index;
  result_index = list1_index = list2_index = 0;
  // while we haven't yet reached the end of either input list
  while (list1_index < size1 && list2_index < size2) {
	// insert the smaller of the next elements of either input list into the
	// next position in the result list
    if (list1[list1_index] < list2[list2_index]) {
      result[result_index] = list1[list1_index];
      list1_index++;
    } else {
      result[result_index] = list2[list2_index];
      list2_index++;
    }
    result_index++;
	steps++;
  }
  // insert the remaining elements from whichever list we aren't at the end of
  // yet into the result list
  while (list1_index < size1) {
    result[result_index] = list1[list1_index];
    list1_index++;    
    result_index++;
	steps++;
  }
  while (list2_index < size2) {
    result[result_index] = list2[list2_index];
    list2_index++;    
    result_index++;
	steps++;
  }
  return result;
}

int* my_mergesort(int* numbers, int size) {
  if (size < 2) {
    return numbers;
  }
  int size1 = size / 2;
  int size2 = size - size1;
  return merge(my_mergesort(numbers, size1),         size1,
               my_mergesort(&numbers[size1], size2), size2);
}