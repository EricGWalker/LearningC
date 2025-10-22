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
 * Allocates Memory for a new leaf node and returns a pointer to it
 */
avlNode *createNewAVLLeafNode(long value) {
  avlNode *newAVLNode = calloc(1, sizeof(avlNode));
  newAVLNode->value = value;
  newAVLNode->height = 0;
  newAVLNode->occurrence = 1;
  newAVLNode->leftChild_p = NULL;
  newAVLNode->rightChild_p = NULL;
  return newAVLNode;
}

long maxLong(long x, long y) { return (x > y) ? x : y; }

/*
 * Updates the height of the current AVLNode given
 * The children have the correct height or are null.
 */
void updateHeight(avlNode *avlNode_p) {
  // This should never be called but putting here just in case.
  if (avlNode_p == NULL) {
    return;
  }
  // Doing this for code readability
  avlNode *leftChild_p = avlNode_p->leftChild_p;
  avlNode *rightChild_p = avlNode_p->rightChild_p;
  long leftHeight = (leftChild_p) ? leftChild_p->height : -1;
  long rightHeight = (rightChild_p) ? rightChild_p->height : -1;
  long height = 1 + maxLong(leftHeight, rightHeight);
  avlNode_p->height = height;
  return;
}

/* NOTE: I realize that I could write a function updateHeightAndGetBalance and
 * save some executions But I think that would make the code I'm writing less
 * maintainable / readable I'm not sure for now because I don't know how to
 * write beautiful code, but I'm trying to figure it out
 */

/*
 * Returns the correct balance of an avlNode given
 * both the child nodes have the correct height stored
 */
int getBalance(avlNode *avlNode_p) {
  // Re Implementing some of the same logic from updateHeight b/c we assume that
  // the child node's height is correct.
  avlNode *leftChild_p = avlNode_p->leftChild_p;
  avlNode *rightChild_p = avlNode_p->rightChild_p;
  long leftHeight = (leftChild_p) ? leftChild_p->height : -1;
  long rightHeight = (rightChild_p) ? rightChild_p->height : -1;
  // WOW WHAT A MICRO-OPTIMIZATION CHANGING BALANCE TO AN INT ROFL
  // As if my code is performant, even though I try to make it performant *sigh*
  int balance = leftHeight - rightHeight;
  return balance;
}

/*
 * Hides a chunk of code that is used to initialize an empty AVL Tree
 * DO NOT USE WITH AN AVL TREE THAT HAS A ROOT
 */
void initializeEmptyAVLTree(long rootValue, avlTree *avlTree_p) {
  assert(avlTree_p->root_p == NULL);
  avlNode *root_p = createNewAVLLeafNode(rootValue);

  avlTree_p->root_p = root_p;
  avlTree_p->nodeCount = 1;
  avlTree_p->valueCount = 1;
}

/* All credit for my ability to implement this goes to  whoever qingyi is:
 * https://pages.cs.wisc.edu/~qingyi/
 * The graphic image on this page makes tracking subtrees easy to visualize
 */

/*
 * Rotates a subtree that is unbalanced by skew of left left.
 * grandParentChild_pp is the address of the pointer to the child of the
 * grandparent or the AVLTree root pointer if changing tree root
 */
void rotateLeftLeft(avlNode *oldSubTreeRoot_p, avlNode **grandParentChild_pp) {
  avlNode *newSubTreeRoot_p = oldSubTreeRoot_p->leftChild_p;
  *grandParentChild_pp = newSubTreeRoot_p;
  oldSubTreeRoot_p->leftChild_p = newSubTreeRoot_p->rightChild_p;
  newSubTreeRoot_p->rightChild_p = oldSubTreeRoot_p;
  // I think this is the only height I need to update
  // will probably have to fix later when I'm wrong.
  updateHeight(oldSubTreeRoot_p);
}
/*
 * Rotates a subtree that is unbalanced by skew of right right.
 * grandParentChild_pp is the address of the pointer to the child of the
 * grandparent or the AVLTree root pointer if changing tree root
 */
void rotateRightRight(avlNode *oldSubTreeRoot_p,
                      avlNode **grandParentChild_pp) {
  avlNode *newSubTreeRoot_p = oldSubTreeRoot_p->rightChild_p;
  *grandParentChild_pp = newSubTreeRoot_p;
  oldSubTreeRoot_p->rightChild_p = newSubTreeRoot_p->leftChild_p;
  newSubTreeRoot_p->leftChild_p = oldSubTreeRoot_p;
  // I think this is the only height I need to update
  // will probably have to fix later when I'm wrong.
  updateHeight(oldSubTreeRoot_p);
}
void rotateRightLeft(avlNode *oldSubTreeRoot_p, avlNode **grandParentChild_pp) {
  avlNode *newSubTreeRoot_p = oldSubTreeRoot_p->leftChild_p;
  *grandParentChild_pp = newSubTreeRoot_p;
  oldSubTreeRoot_p->leftChild_p = newSubTreeRoot_p->rightChild_p;
  newSubTreeRoot_p->rightChild_p = oldSubTreeRoot_p;
  updateHeight(oldSubTreeRoot_p);
  updateHeight(newSubTreeRoot_p);
  // TODO: Wipe out all the rotation functions and redo them.
}
void rotateLeftRight(avlNode *subTreeRoot_p) {
  // TODO:
}
/*
 * Insert a value into the AVL Tree
 */
void avlInsert(long value, avlTree *avlTree_p) {
  // Init a new AVL Tree if empty
  if (avlTree_p->root_p == NULL) {
    // YAY Clean Section of insert Function
    initializeEmptyAVLTree(value, avlTree_p);
    return;
  }

  // Traversal Stack for updating Height and Balance
  stackNode *visitedHead_p = NULL;

  avlNode *currentAVLNode_p = avlTree_p->root_p;
  do {
    // Add current AVLNode to the stack.
    stackNode *nextVisited_p = calloc(1, sizeof(stackNode));
    nextVisited_p->avlNode_p = currentAVLNode_p;
    nextVisited_p->next = visitedHead_p;
    visitedHead_p = nextVisited_p;

    // Determine what the next node should be
    long currentValue = currentAVLNode_p->value; // Done for readability
    if (value > currentValue) {
      currentAVLNode_p = currentAVLNode_p->rightChild_p;
    } else if (value < currentValue) {
      currentAVLNode_p = currentAVLNode_p->leftChild_p;
    } else if (value == currentValue) {
      currentAVLNode_p->occurrence += 1;
      avlTree_p->valueCount += 1;
      return;
    } else {
      // This should be unreachable
      // I just like having conditions on all of my if statements to document
      // what the condition of the block should be.
      abort();
      return;
    }
  } while (currentAVLNode_p != NULL);

  // Create newAVLNode
  avlNode *newLeafNode_p = createNewAVLLeafNode(value);

  /* The visitedHead_p should now be pointing the the parent of the to be
   created AVLNode */

  // Insert into correct child pointer of parent
  avlNode *parentNode = visitedHead_p->avlNode_p;
  long parentValue = parentNode->value;
  if (value > parentValue) {
    parentNode->rightChild_p = newLeafNode_p;
  } else if (value < parentValue) {
    parentNode->leftChild_p = newLeafNode_p;
  } else {
    // Should be unreachable
    abort();
    return;
  }

  // This logic is going to be complicated so that we only traverse the
  // traversalStack once instead of twice.

  while (visitedHead_p != NULL) {
    avlNode *currentAVLNode = visitedHead_p->avlNode_p;
    updateHeight(currentAVLNode_p);
    int currentBalance = getBalance(currentAVLNode_p);
    if (currentBalance > 1 || currentBalance < -1) {
      // TODO: begin the rotations.
    }
  }

  // TODO: Check Balance of ancestors and then perform necessary rotations.
}
// vim: ts=2 sts=2 sw=2 et
