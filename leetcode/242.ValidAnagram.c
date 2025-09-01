#include <stdio.h>
#include <stdlib.h>

bool isAnagram(char *s, char *t) {
  int letterCount['z' - 'a' + 1] = {0};
  unsigned int i = 0;
  // Add up letterCount
  while ((s[i] != '\0') || (t[i] != '\0')) {
    if (s[i] == '\0' || t[i] == '\0') {
      return false;
    }
    letterCount[s[i] - 'a'] += 1;
    letterCount[t[i] - 'a'] -= 1;
    i++;
  }

  for (unsigned int i = 0; i < ('z' - 'a' + 1); i++) {
    if (letterCount[i] != 0) {
      return false;
    }
  }
  return true;
}
int main() {
  char s[] = "str";
  char t[] = "string";
  printf("bool: %u\n", isAnagram(s, t));
  return EXIT_SUCCESS;
}
// vim: ts=2 sts=2 sw=2 et
