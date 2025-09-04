#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define letterCount 26

/*
 * Node for a string anagrams to be chained in a linked list
 */
typedef struct node {
  char *string;
  struct node *next;
} node;

typedef struct {
  // This is the key
  // This will have a fixed size of 26
  unsigned int *charCountArray;
  unsigned long long hash;
  node *stringsLinkedList;
} hashSet;

typedef struct {
  // Total capacity of the array
  unsigned int capacity;
  // Total utilized capacity of the array
  unsigned int size;
  // pointer to the first element in the array
  hashSet *hashSetArray;
} hashMap;

// Numbers taken form wikipedia for a fnv-1 hash
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
#define FNV_offset_basis 14695981039346656037ULL
#define FNV_prime 1099511628211ULL
unsigned long long hash(unsigned int *charCountArray) {
  unsigned long long hash = FNV_offset_basis;
  // I hope this works, and if it does. I'm sorry.
  // This is so hacky and bad
  uint8_t *charCountArrayEnd =
      ((uint8_t *)charCountArray + (letterCount * sizeof(unsigned int)));
  for (uint8_t *p = (uint8_t *)charCountArray; p < charCountArrayEnd; p++) {
    hash *= FNV_prime;
    hash ^= *p;
  }
  return hash;
}

hashMap *createHashMap(unsigned int capacity) {
  assert(capacity > 0);
  hashMap *hashMap_p = calloc(1, sizeof(hashMap));
  hashMap_p->capacity = capacity;
  hashMap_p->size = 0;
  hashMap_p->hashSetArray = calloc(capacity, sizeof(hashSet));
  return hashMap_p;
}

/*
 * Doubles capacity of a passed in hashed map
 */
void doubleHashMapCapacity(hashMap *hashMap_p) {
  unsigned int newCapacity = hashMap_p->capacity * 2;
  hashSet *newHashSetArray = calloc(newCapacity, sizeof(hashSet));

  for (unsigned int oldArrayIndex = 0; oldArrayIndex < hashMap_p->capacity;
       oldArrayIndex++) {
    hashSet *oldHashSet_p = &hashMap_p->hashSetArray[oldArrayIndex];
    if (oldHashSet_p == NULL) {
      continue;
    }
    // begin linear probing
    for (unsigned int offset = 0; offset < newCapacity; offset++) {
      unsigned int newHashSetArray_idx =
          (oldHashSet_p->hash + offset % newCapacity);
      if (&newHashSetArray[newHashSetArray_idx] == NULL) {
        newHashSetArray[newHashSetArray_idx] = *oldHashSet_p;
        break;
      } else {
        continue;
      }
    }
  }
  hashMap_p->capacity = newCapacity;
  hashMap_p->hashSetArray = newHashSetArray;
}

/*
 * Inserts a hashSet into a hashMap and doubles capacity if needed
 */
void insertHashSet(hashSet hashSetObject, hashMap *hashMap_p) {
  // Check if we need to double capacity
  if (hashMap_p->size + 1 > hashMap_p->capacity / 2.0) {
    doubleHashMapCapacity(hashMap_p);
  }
  // begin linear probing
  for (unsigned int offset = 0; offset < hashMap_p->capacity; offset++) {
    unsigned int targetIndex =
        hashSetObject.hash + offset % hashMap_p->capacity;
    hashSet *targetValue_p = &hashMap_p->hashSetArray[targetIndex];
    if (targetValue_p == NULL) {
      hashMap_p->hashSetArray[targetIndex] = hashSetObject;
      break;
    } else {
      continue;
    }
  }
  hashMap_p->size++;
}
/*
 * Generates a new hashSet for the unique charCountArray
 */
hashSet generateHashSet(unsigned int *charCountArray) {
  hashSet hashSetObject = {.charCountArray = charCountArray,
                           .hash = hash(charCountArray),
                           .stringsLinkedList = NULL};
  return hashSetObject;
}

/*
 * Determines if two arrays are equal
 */
bool arraysEqual(unsigned int *array1, unsigned int *array2,
                 unsigned int sizeOfArray) {
  for (unsigned int i = 0; i < sizeOfArray; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}

/*
 * Checks if the charCountArray exists in the hashMap and returns the hashSet
 */
hashSet *getHashSet(unsigned int *charCountArray, hashMap *hashMap_p) {
  unsigned long long charHash = hash(charCountArray);
  // begin linear probing
  for (unsigned int offset = 0; offset < hashMap_p->capacity; offset++) {
    unsigned int targetIndex = charHash + offset % hashMap_p->capacity;
    hashSet *targetValue_p = &hashMap_p->hashSetArray[targetIndex];
    if (targetValue_p == NULL) {
      return NULL;
    } else if (arraysEqual(charCountArray, targetValue_p->charCountArray,
                           letterCount)) {
      return targetValue_p;
    } else {
      continue;
    }
  }
  return NULL;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
char **groupAnagrams(char **strs, int strsSize, int *returnSize,
                     int **returnColumnSizes) {
  // todo
  return NULL;
}
int main() {
  unsigned int letters[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned int letters2[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  printf("%llu\n", hash(letters));
  printf("%llu\n", hash(letters2));
}
// vim: ts=2 sts=2 sw=2 et
