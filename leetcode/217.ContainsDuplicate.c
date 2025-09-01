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
 * This is a personal print debugging function
 */
void printHashList(hashList *hashList_p) {
  printf("Capacity: %lu\n", hashList_p->capacity);
  printf("Size: %lu\n", hashList_p->size);
  printf("{");
  for (size_t i = 0; i < hashList_p->capacity; ++i) {
    int *value_p = hashList_p->array[i];
    if (value_p == NULL) {
      printf("nil, ");
    } else {
      printf("%i, ", *value_p);
    }
  }
  printf("}\n");
}

/*
 * Creates a hashList struct pre-allocated with capacity amount of memory for
 * ints and returns a pointer to it.
 * capacity > 0;
 */
hashList *createHashList(size_t capacity) {
  assert(capacity > 0);
  hashList *hashList_p = (hashList *)calloc(1, sizeof(hashList));
  hashList_p->capacity = capacity;
  hashList_p->size = 0;
  hashList_p->array = (int **)calloc(capacity, sizeof(int *));

  return hashList_p;
}

/*
 * Allocates double the current capacity to a new array object and then sets the
 * hashList struct's array object to point to the new array with double
 * capacity. Additionally this function will re-index and insert all old array
 * values in the new array
 */
void resizeHashList(hashList *hashList_p) {
  size_t new_capacity = hashList_p->capacity * 2;
  int **new_array = calloc(new_capacity, sizeof(int *));

  // Iterate through the old array
  for (size_t i = 0; i < hashList_p->capacity; ++i) {
    int *value_p = hashList_p->array[i];
    // Insert only non Null values
    if (value_p != NULL) {
      size_t new_init_index = *value_p % new_capacity;
      // Iterate through the new array starting at the new_init_index until a
      // NULL pointer is found While the worst case is O(N) the average case is
      // going to be O(1)
      for (size_t offset = 0; offset < new_capacity; ++offset) {
        size_t target_index = (new_init_index + offset) % new_capacity;
        if (new_array[target_index] == NULL) {
          new_array[target_index] = (int *)malloc(sizeof(int));
          *new_array[target_index] = *value_p;
          break;
        } else {
          continue;
        }
      }
    }
  }

  free(hashList_p->array);
  hashList_p->capacity = new_capacity;
  hashList_p->array = new_array;
}

/*
 * This function takes a hashlist and inserts a value if it's not found
 * Otherwise it reurns True if the value already exists in the hashList
 */
bool seenBeforeInHashList(int value, hashList *hashList_p) {
  assert(hashList_p->size < hashList_p->capacity);
  // If we need to insert a value into the hashList this will save us time.
  size_t null_idx;
  // Step 1 is to see if we can find the value in the hashList
  size_t init_index = value % hashList_p->capacity;
  // Iterate through the array starting at the init_index until a
  // NULL pointer is found While the worst case is O(N) the average case is
  // going to be O(1)
  for (size_t offset = 0; offset < hashList_p->capacity; ++offset) {
    size_t target_index = (init_index + offset) % hashList_p->capacity;
    if (hashList_p->array[target_index] == NULL) {
      null_idx = target_index;
      break;
    } else if(*hashList_p->array[target_index] == value){
      return true;
    }
  }
  // We've scanned the hashList for our value and learned that it isn't there
  hashList_p->array[null_idx] = malloc(sizeof(int *));
  *hashList_p->array[null_idx] = value;
  hashList_p->size += 1;
  //Finally if the size is too big we need to resize.
  if(hashList_p->size > hashList_p->capacity / 2.0){
    resizeHashList(hashList_p);
  }

  return false;
}

bool containsDuplicate(int *nums, int numsSize) {
  hashList *hashList_p = createHashList(1);
  for (size_t index; index < numsSize; ++index) {
    if (seenBeforeInHashList(nums[index], hashList_p)){
      return true;
    }
  }
  return false;
}

int main() {
  int noDuplicates[] = {0,1,2,3,4,5,6,7,8,9};
  printf("noDuplicates = %i\n", containsDuplicate(noDuplicates, 10));
  int duplicates[] = {0,2,1,0};
  printf("Duplicates = %i\n", containsDuplicate(duplicates, 10));
  return EXIT_SUCCESS;
}
// vim: ts=2 sts=2 sw=2 et
