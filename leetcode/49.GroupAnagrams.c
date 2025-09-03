#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define letterCount 26

typedef struct node {
  char *string;
  struct node *next;
} node;

typedef struct {
  // This is the key
  // This will have a fixed size of 26
  unsigned int charCountArray[letterCount];
  node stringsLinkedList;
} pair;

// Numbers taken form wikipedia for a fnv-1 hash
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
#define FNV_offset_basis 14695981039346656037ULL
#define FNV_prime 1099511628211ULL
unsigned long long hash(unsigned int *charCountArray) {
  unsigned long long hash = FNV_offset_basis;
  // I hope this works, and if it does. I'm sorry.
  // This is so hacky and bad
  for (uint8_t *p = (uint8_t *)charCountArray;
       p < ((uint8_t *)charCountArray + (letterCount * sizeof(unsigned int))); p++) {
    hash *= FNV_prime;
    hash ^= *p;
  }
  return hash;
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
  unsigned int letters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned int letters2[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
  printf("%llu\n", hash(letters));
  printf("%llu\n", hash(letters2));
}
// vim: ts=2 sts=2 sw=2 et
