/* Sam Auciello | 2013 | Algorithms Exam
 * This file contains an array-based implementation of heapsort
 */

// add the specified value to the heap
void heap_push(int* heap, int index, int value) {
  // add the new number at the bottom of the heap
  heap[index] = value;
  // swap the new number with its parent until it is parent is less than or
  // equal to it
  int parent = (index - 1) / 2;
  while (index > 0 && heap[parent] > heap[index]) {
    swap(&heap[parent], &heap[index]);
    index = parent;
    parent = (index - 1) / 2;
	steps++;
  }
}

// remove the smallest number from the front of the heap and rearrange the
// remaining items to maintain the validity of the heap
int heap_pop(int* heap, int size) {
  // remember the smallest element to be returned at th end
  int result = heap[0];
  // move the last element to the top
  heap[0] = heap[size - 1];
  // swap the new root with its smaller child until it is smaller than both of
  // its children
  int parent = 0;
  int child1 = 1;
  int child2 = 2;
  while (child1 < size &&
         (heap[parent] > heap[child1] ||
          heap[parent] > heap[child2])) {
    if (child2 < size && heap[child2] < heap[child1]) {
      swap(&heap[parent], &heap[child2]);
      parent = child2;
    } else {
      swap(&heap[parent], &heap[child1]);
      parent = child1;
    }
    child1 = (parent * 2) + 1;
    child2 = (parent * 2) + 2;
	steps++;
  }
  return result;
}

void my_heapsort(int* numbers, int size) {
  int i;
  int* heap = malloc(sizeof(int) * size);
  for (i = 0; i < size; i++) {
    heap_push(heap, i, numbers[i]);
  }
  for (i = 0; i < size; i++) {
    numbers[i] = heap_pop(heap, size - i);
  }
}
