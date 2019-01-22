/**
 * Binary Search Tree - Template
 *
 * Store values in a BST
 * Can use Inorder, Preorder and Postorder to traverse tree
 * Can use Add/Remove to modify tree
 * Rebalance creates a balanced tree
 *
 * @author XXX
 * @date XXX
 */

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>

using namespace std;

template<class T>
class BST {
  // display a sideways ascii representation of tree
  friend ostream &operator<<(ostream &os, const BST &bst) {
    bst.sideways(bst.rootPtr, 0, os);
    return os;
  }

 private:
  // Node for BST
  typedef struct node {
    T data;
    struct node *leftPtr;
    struct node *rightPtr;
  } Node;

  // root of the tree
  Node *rootPtr{nullptr};

  // Make a new BST Node
  Node *makeNode(const T &value) const {
    // TODO(me)
    return nullptr;
  }

  // helper function for displaying tree sideways, works recursively
  void sideways(Node *current, int level, ostream &os) const {
    static const string indents{"   "};
    if (current) {
      level++;
      sideways(current->rightPtr, level, os);

      // indent for readability, 4 spaces per depth level
      for (int i = level; i >= 0; i--)
        os << indents;

      // display information of object
      os << current->data << endl;
      sideways(current->leftPtr, level, os);
    }
  }

  // Additional private functions
  // TODO(me)

 public:
  // constructor, empty tree
  BST() {
    // TODO(me)
  }

  // constructor, tree with root
  explicit BST(const T &rootItem) {
    // TODO(me)
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  BST(const T arr[], int n) {
    // TODO(me)
  }

  // copy constructor
  BST(const BST<T> &bst) {
    // TODO(me)
  }

  // destructor
  virtual ~BST() {
    // TODO(me)
  }

  // true if no nodes in BST
  bool IsEmpty() const {
    // TODO(me)
    return true;
  }

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const {
    // TODO(me)
    return 0;
  }

  // number of nodes in BST
  int NumberOfNodes() const {
    // TODO(me)
    return 0;
  }
  // add a new item, return true if successful
  bool Add(const T &item) {
    // TODO(me)
    return true;
  }

  // remove item, return true if successful
  bool Remove(const T &item) {
    // TODO(me)
    return true;
  }

  // true if item is in BST
  bool Contains(const T &item) const {
    // TODO(me)
    return true;
  }

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void InorderTraverse(void visit(const T &item)) const {
    // TODO(me)
  }

  // preorder traversal: root-left-right
  void PreorderTraverse(void visit(const T &item)) const {
    // TODO(me)
  }

  // postorder traversal: left-right-root
  void PostorderTraverse(void visit(const T &item)) const {
    // TODO(me)
  }

  // create dynamic array, copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree should be balanced
  void Rebalance() {
    // TODO(me)
  }

  // delete all nodes in tree
  void Clear() {
    // TODO(me)
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &other) const {
    // TODO(me)
    return true;
  }

  // not == to each other
  bool operator!=(const BST<T> &other) const {
    // TODO(me)
    return true;
  }
};

#endif  // BST_HPP
