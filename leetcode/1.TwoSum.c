/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *indices = calloc(2, sizeof(int));
  for (unsigned int i = 0; i < numsSize - 1; ++i) {
    for (unsigned int j = i + 1; j < numsSize; ++j) {
      int sum = nums[i] + nums[j];
      if (sum == target) {
        indices[0] = i;
        indices[1] = j;
        *returnSize = 2; // This single line fucked me up, I didn't know I needed to specify the length of my return
        return indices;
      }
    }
  }
  return NULL;
}

int main() {
  int numSize = 4;
  int nums[] = {2, 7, 11, 15};
  int target = 9;
  int returnSize = 2;
  int *returnArray = twoSum(nums, numSize, target, &returnSize);
  printf("[%i,%i]\n", returnArray[0], returnArray[1]);
}
// vim: ts=2 sts=2 sw=2 et
