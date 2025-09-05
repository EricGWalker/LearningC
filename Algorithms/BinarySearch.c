
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Returns a sorted Array of length @param length
 * The values are primitively the index
 */
unsigned long *generateSortedArray(size_t length) {
  unsigned long *returnArray = calloc(length, sizeof(unsigned long));
  for (size_t i = 0; i < length; ++i) {
    returnArray[i] = i;
  }
  return returnArray;
}

/*
 * Returns a (size_t *) which contains the index of the target if it exists.
 * Returns NULL if not found, so check the address of the return value;
 */
size_t *binarySearch(unsigned long target, unsigned long *sortedArray,
                     size_t sizeOfSortedArray) {
  size_t leftIdx = 0;
  size_t rightIdx = sizeOfSortedArray - 1;

  unsigned long iterations = 0;
  while (leftIdx <= rightIdx) {
    ++iterations;
    size_t midIdx = (leftIdx + rightIdx) / 2;
    unsigned long midValue = sortedArray[midIdx];
    if (midValue == target) {
      printf("Found %lu in %lu iterations in an array of size %lu.\n", target,
             iterations, sizeOfSortedArray);
      size_t *returnIdx_p = malloc(sizeof(size_t *));
      *returnIdx_p = midIdx;
      return returnIdx_p;
    } else if (midValue > target) {
      rightIdx = midIdx - 1;
    } else if (midValue < target) {
      leftIdx = midIdx + 1;
    } else {
      puts("How did we get here????");
    }
  }
  return NULL;
}

int main() {
  const size_t testIterations = 100;
  for (size_t i = 0; i < testIterations; ++i) {
    const size_t arrayLength = ((size_t)rand() % 1000000) + 1;
    unsigned long *array = generateSortedArray(arrayLength);
    unsigned long targetValue = (unsigned long)rand() % arrayLength;
    bool correct =
        targetValue == *binarySearch(targetValue, array, arrayLength);
    printf("Result was correct: %i\n", correct);
    free(array);
  }

  // Edge Cases
  puts("Edge Cases");
  const size_t arrayLength = 100;
  unsigned long *array = generateSortedArray(arrayLength);
  binarySearch(0, array, arrayLength);
  binarySearch(arrayLength - 1, array, arrayLength);
  return EXIT_SUCCESS;
}
// vim: ts=2 sts=2 sw=2 et
