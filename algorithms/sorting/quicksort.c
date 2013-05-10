/* Sam Auciello | 2013 | Algorithms Exam
 * This file contains an in place implementation of quicksort
 */

void quicksort(int* numbers, int size) {
  // the pivot is initially at index 0 and will be swapped to the center at the
  // end
  int left = 1; // a pointer to the leftmost number that isn't the pivot
  int right = size - 1; // a pointer to the rightmost number
  // until the two pointers meet
  while (left < right) {
	// scan left with the right pointer until you find a number less than the
	// pivot
    while (numbers[right] >= numbers[0] && left < right) {
	  steps++;
      right--;
    }
	// scan right with the left pointer until you find a number greater than the
	// pivot
    while (numbers[left] <= numbers[0] && left < right) {
	  steps++;
      left++;
    }
	// swap the two numbers which are on the wrong side
    swap(&numbers[left], &numbers[right]);
  }
  // swap the pivot to the center
  if (numbers[0] > numbers[left]) {
    swap(numbers, &numbers[left]);
  }
  // recursively quicksort the left side
  if (left > 1) {
    quicksort(numbers, left);
  }
  // recursively quicksort the right side
  if (size - right > 1) {
    quicksort(&numbers[right], size - right);
  }
}
