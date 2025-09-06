#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
typedef struct __avlNode {
  long value;
  unsigned long occurrence;
  long height;
  struct __avlNode *rightChild_p;
  struct __avlNode *leftChild_p;
} avlNode;

typedef struct {
  size_t valueCount; // The number of nodes weighted against their occurrence.
  size_t nodeCount;  // The literal number of nodes in the tree.
  avlNode *root_p;
} avlTree;

typedef struct __stackNode {
  avlNode *avlNode_p;
  struct __stackNode *next;
} stackNode;



/*
 * Insert a value into the AVL Tree
 */
void avlInsert(long value, avlTree *avlTree_p) {
  // Init a new AVL Tree if empty
  if (avlTree_p->root_p == NULL) {
    avlNode *root_p = calloc(1, sizeof(avlNode));
    root_p->value = value;
    root_p->height = 0;
    root_p->occurrence= 1;
    root_p->rightChild_p = NULL;
    root_p->leftChild_p = NULL;

    avlTree_p->root_p = root_p;
    avlTree_p->nodeCount = 1;
  }
}

void getTraversal(size_t nodeCount) {
  assert(nodeCount > 0);
  nodeCount -= 1;
  while (nodeCount >= 1) {
  }
}
// vim: ts=2 sts=2 sw=2 et
