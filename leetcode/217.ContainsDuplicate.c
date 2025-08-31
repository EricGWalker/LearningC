#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  size_t capacity;
  size_t size;
  int **array;
} hashList;
// I don't know what to call this. It's between an arraylist and a hashmap.

/*
 * Creates a hashList struct pre-allocated with capacity amount of memory for
 * ints and returns a pointer to it.
 * capacity > 0;
 */
hashList *createHashList(size_t capacity) {
  assert(capacity > 0);
  hashList *hashList_p = (hashList *)malloc(sizeof(hashList));
  hashList_p->capacity = capacity;
  hashList_p->size = 0;
  hashList_p->array = malloc(sizeof(int) * capacity);

  return hashList_p;
}

bool containsDuplicate(int *nums, int numsSize) {
  // code here
  return true;
}

int main(){
  hashList *hashList_p = createHashList(10);
  size_t *capacity_p = &hashList_p->capacity;
  size_t *size_p = &hashList_p->size;
  int **array = hashList_p->array;
  array[1] = malloc(sizeof(int));
  *array[1] = 5;

  printf("Capacity=%lu\n", *capacity_p);
  printf("Size=%lu\n", *size_p);
  printf("array[0]=%p\n", array[0]);
  printf("*array[1]=%i\n", *array[1]);
  return EXIT_SUCCESS;
}
// vim: ts=2 sts=2 sw=2 et
