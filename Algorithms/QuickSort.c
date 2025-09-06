#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
long *generateRandomArray(size_t arraySize) {
  // This way the values are readable
  const long randModulus = 20;
  long *array = calloc(arraySize, sizeof(long));
  for (size_t i = 0; i < arraySize; ++i) {
    array[i] = (long)rand() % randModulus;
  }
  return array;
}

size_t getPivotIndex(long *partition, size_t sizeOfPartition) {
  size_t firstIdx = 0;
  size_t lastIdx = sizeOfPartition - 1;
  size_t middleIdx = sizeOfPartition / 2;
  // I hope the compiler just reduces these expressions and doesn't allocate
  // more memory.
  long firstValue = partition[firstIdx];
  long lastValue = partition[lastIdx];
  long middleValue = partition[middleIdx];

  if (firstValue <= middleValue && middleValue <= lastValue) {
    return middleIdx;
  } else if (middleValue <= firstValue && firstValue <= lastValue) {
    return firstIdx;
  } else {
    return lastIdx;
  }
}

/*
 * Sorts a partition and returns the final position of the pivot
 */
size_t sortPartition(long *partition, size_t sizeOfPartition) {
  assert(sizeOfPartition > 0);
  if (sizeOfPartition == 1) {
    return 0;
  }
  size_t pivotIdx = getPivotIndex(partition, sizeOfPartition);
  long pivotValue = partition[pivotIdx];
  partition[pivotIdx] = partition[sizeOfPartition - 1];
  partition[sizeOfPartition - 1] = pivotValue;
  pivotIdx = sizeOfPartition - 1;
  size_t leftIdx = 0;
  size_t rightIdx = pivotIdx - 1;
  while (leftIdx < rightIdx) {
    // I think the <= means that this sort will not be stable
    // But without it I feel like my program could halt with duplicate values.
    while (partition[leftIdx] <= pivotValue && leftIdx < sizeOfPartition) {
      leftIdx++;
    }
    while (partition[rightIdx] >= pivotValue && rightIdx > 0) {
      rightIdx--;
    }
    if (leftIdx < rightIdx) {
      long rightValue = partition[rightIdx];
      partition[rightIdx] = partition[leftIdx];
      partition[leftIdx] = rightValue;
    }
  }
  // Left Idx Should have crossed with rightIdx by this point
  long oldLeftValue = partition[leftIdx];
  partition[leftIdx] = pivotValue;
  partition[pivotIdx] = oldLeftValue;
  pivotIdx = leftIdx;
  return pivotIdx;
}

void quickSort(long *array, size_t arraySize) {
  if (arraySize <= 1) {
    return;
  }
  // Sort whole array and get pivotIndex;
  size_t pivotIdx = sortPartition(array, arraySize);
  // Sort left half
  if (pivotIdx > 0) {
    quickSort(array, pivotIdx);
  }
  // Sort right half
  if (pivotIdx + 1 < arraySize) {
    long *rightArray = array + (pivotIdx + 1);
    size_t rightArraySize = arraySize - pivotIdx - 1;
    quickSort(rightArray, rightArraySize);
  }
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
  const size_t arraySize = 20;
  long *randArray = generateRandomArray(arraySize);
  printArray(randArray, arraySize);
  quickSort(randArray, arraySize);
  printArray(randArray, arraySize);
}
// vim: ts=2 sts=2 sw=2 et
