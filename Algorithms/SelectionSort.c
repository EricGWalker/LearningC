#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * Returns a runtime allocated array of size arraySize
 * REMEMBER TO FREE IT
 */
long *generateRandomArray(size_t arraySize) {
  // This way the values are readable
  const long randModulus = 1000;
  long *array = calloc(arraySize, sizeof(unsigned long));
  for (size_t i = 0; i < arraySize; ++i) {
    array[i] = (long)rand() % randModulus;
  }
  return array;
}

long *selectionSort(long *unsortedArray, size_t arraySize) {
  long *sortedArray = calloc(arraySize, sizeof(long));
  for (size_t sortedIdx = 0; sortedIdx < arraySize; ++sortedIdx) {
    long minValue = LONG_MAX;
    // Setting to sortedIdx so that if for some reason every value was long_max
    // we still have a valid index
    size_t minIdx = sortedIdx;
    for (size_t selectionIdx = sortedIdx; selectionIdx < arraySize;
         ++selectionIdx) {
      long selectionValue = unsortedArray[selectionIdx];
      if (selectionValue < minValue) {
        minValue = selectionValue;
        minIdx = selectionIdx;
      }
    }
    sortedArray[sortedIdx] = minValue;
    // Swap unsorted Value into sortable range
    long notSortedValue = unsortedArray[sortedIdx];
    unsortedArray[minIdx] = notSortedValue;
  }

  return sortedArray;
}

void printArray(long *array, size_t arraySize) {
  assert(arraySize > 0);
  printf("{%li", array[0]);
  for (size_t i = 1; i < arraySize; ++i) {
    printf(",%li", array[i]);
  }
  printf("}\n");
}

int main() {
  const size_t testCount = 100;
  const size_t arrayModulus = 100;
  for (size_t test = 0; test < testCount; ++test) {
    size_t arraySize = ((size_t)rand() % arrayModulus) + 1;
    long *unsortedArray = generateRandomArray(arraySize);
    printArray(unsortedArray, arraySize);
    long *sortedArray = selectionSort(unsortedArray, arraySize);
    printArray(sortedArray, arraySize);
    free(sortedArray);
    free(unsortedArray);
  }
  return EXIT_SUCCESS;
}

// vim: ts=2 sts=2 sw=2 et
