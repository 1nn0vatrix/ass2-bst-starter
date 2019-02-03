/**
 * Binary Search Tree - Template
 *
 * Store values in a BST
 * Can use Inorder, Preorder and Postorder to traverse tree
 * Can use Add/Remove to modify tree
 * Rebalance creates a balanced tree
 *
 * @author Jenna Martin
 * @date January 24, 2019
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
        // TODO(Jenna Martin)
        // new node created
        node *newNode =  new node();
        // data assigned the value passed in
        newNode->data = value;
        // left pointer set to null (it's a leaf)
        newNode->leftPtr = nullptr;
        // right pointer set to null (it's a leaf)
        newNode->rightPtr = nullptr;
        return newNode;
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
    // TODO(Jenna)
    /**
     * isLeaf helper function checks if the current node is a leaf (no children)
     * @param n - the node that is being evaluated as a leaf
     * @return boolean, true if there are no children, false if otherwise
     */
    static bool isLeaf(node *n) {
        return (!n->leftPtr && !n->rightPtr);
    }

    /**
     * This helper function recursively returns the total nodes in the BST
     * @param root - the root node for the tree & resulting subtrees
     * @return an integer with the total number of nodes in the tree
     */
    int getCount(node *root) const {
        // this counts the current node
        int count = 1;
        // If there are values in the left child node
        if (root->leftPtr) {
            // adds to the total # of left nodes (recursively calls function)
            count += getCount(root->leftPtr);
        }
        // If the right child node is not empty
        if (root->rightPtr) {
            // it adds to the total # of right nodes recursively
            count +=  getCount(root->rightPtr);
        }
        // Once both left and right == null and there are no more calls to make
        // the count is returned
        return count;
    }

    /**
     * This helper function recursively counts the height of the node by
     * comparing the left and right sides and returning the larger of those two
     * values.
     * @param currentRoot - root node for the tree & subsequent subtrees
     * @return integer with the height of the tree
     */
    int findHeight(node *currentRoot) const {
        // int leftSide created to store the height of the longest left path
        int leftSide = 0;
        // int rightSide created to store the height of the longest right path
        int rightSide = 0;
        // if the leftChild is not empty
        if (currentRoot->leftPtr) {
            // keep traveling down the left child nodes
            leftSide = findHeight(currentRoot->leftPtr);
        }
        // if the rightChild is not empty
        if (currentRoot->rightPtr) {
            // keep traveling down the right childe nodes
            rightSide = findHeight(currentRoot->rightPtr);
        }
        // if the left side has a greater height than the right
        if (leftSide > rightSide)
            // add in the root and return the height
            return leftSide + 1;
            // otherwise return the height of the right + root
        else
            return rightSide + 1;
    }

    /**
     * This is the destroy helper function for Clear(), it recursively traverses
     * down the tree and deletes & dereferences the nodes
     * @param root - the node being deleted
     */
    void destroy(node*& root) {    // NOLINT
        if (root) {
            destroy(root->leftPtr);
            destroy(root->rightPtr);
            delete root;
            root = nullptr;
        }
    }

    /**
     * This is the helper function for preorderTraversal, this uses recursion
     * to traverse through all of the nodes in the tree and output them in the
     * Root - Left - Right order.
     *
     * @param visit - adds the root->data to the stringStream for bst_test.cpp
     * @param root - the current node
     */
    static void preorderHelper(void visit(const T &item), node* root) {
        if (root) {
            visit(root->data);
            preorderHelper(visit, root->leftPtr);
            preorderHelper(visit, root->rightPtr);
        }
    }

    /**
    * This is the helper function for inorderTraversal, this uses recursion
    * to traverse through all of the nodes in the tree and output them in the
    * Left - Root - Right order.
    *
    * @param visit - adds the root->data to the stringStream for bst_test.cpp
    * @param root - the current node
    */
    static void inorderHelper(void visit(const T &item), node* root) {
        if (root) {
            inorderHelper(visit, root->leftPtr);
            visit(root->data);
            inorderHelper(visit, root->rightPtr);
        }
    }

    /**
    * This is the helper function for postorderTraversal, this uses recursion
    * to traverse through all of the nodes in the tree and output them in the
    * Left - Right - Root order.
    *
    * @param visit - adds the root->data to the stringStream for bst_test.cpp
    * @param root - the current node
    */
    static void postorderHelper(void visit(const T &item), node* root) {
        if (root) {
            // recursively traverses left child nodes
            postorderHelper(visit, root->leftPtr);
            // recursively traverses right child nodes
            postorderHelper(visit, root->rightPtr);
            // outputs the root data
            visit(root->data);
        }
    }
    /**
     * Visit helper function adds the root data into the stringstream for
     * assertion
     * @param item - the generic data stored at each node's root
     */
    static void visit(const T &item) {
        stringstream SS;
        SS << item;
    }

    /**
     * Helper function to recursively copy the nodes for the copy constructor
     * @param root the current root of the tree and subtrees
     * @return the root node with all the copied subtrees
     */
    node* copyNodes(const node* root) const {
        if (!root) {
            return nullptr;
        } else {
            node* newNode = makeNode(root->data);
            newNode->leftPtr = copyNodes(root->leftPtr);
            newNode->rightPtr = copyNodes(root->rightPtr);
            return newNode;
        }
    }

    /**
     * This is the helper function that recursively checks that two nodes are
     * equal.
     * @param comp1 - first node for comparison
     * @param comp2 - second node for comparison
     * @return - true or false if objects being compared are equal
     */
    bool areEqual(const node* comp1, const node* comp2) const {
        // Base case: if both are null, they are equal
        if (comp1 == nullptr && comp2 == nullptr) {
            return true;
        } else if ((comp1 == nullptr) || (comp2 == nullptr)) {
            // If one has more nodes than the other, they are not equal
            return false;
        } else {
            // return T/F if each node contains the same data
            return ((comp1->data == comp2->data)&&areEqual(comp1->leftPtr,
                    comp2->leftPtr) && areEqual(comp1->rightPtr,
                            comp2->rightPtr));
        }
    }

// Helper functions for Rebalance() function
    /**
     * inorderSorter function traverses the BST inorder and places values in
     * an array. Sorts the array in ascending order. Recursively increments the
     * index of the array
     * @param adder  - name of my array
     * @param n  - the node being traversed
     * @param index - the index of the array
     * @return - an incremental index for each element in the sorted array
     */
    int inorderSorter(T* adder, node* n, int index) {
        // base case return the index when you reach a leaf
        if (!n) {
            return index;
        }
        // traverse down the left child
        if (n->leftPtr) {
            index = inorderSorter(adder, n->leftPtr, index);
        }
        // input the value into the array
        adder[index] = n->data;
        // increase the index
        index++;
        // traverse the right child
        if (n->rightPtr) {
            index = inorderSorter(adder, n->rightPtr, index);
        }
        // satisfies cppcheck.
        return index;
    }

    /**
     * This constructs a rebalanced BST using the inorderSorter function above
     * It finds the middle of the array and places it as a node, then it
     * recursively searches the left and right half of the array until the
     * balanced BST is created
     * @param adder - sorted array - adds elements to the BST
     * @param start - the first index of each array (and subarray)
     * @param end - the last index of each array (and subarray)
     */
    void rebalanceBST(T* adder, int start, int end) {
        // if end index crosses the starting index the array has been exhausted
        if (start > end) {
            return;
        } else {
            // find the middle element
            int mid = (start + end) / 2;
            T item = adder[mid];
            // item is added into the BST
            Add(item);
            // first half of array searched for subtree root
            rebalanceBST(adder, start, mid - 1);
            // second half of array searched for subtree root
            rebalanceBST(adder, mid + 1, end);
        }
    }

 public:
    /*************************************/
    //         Constructors              //
    /*************************************/
    // constructor, empty tree
    BST() {
        // TODO(Jenna)
        this->rootPtr = nullptr;
    }

    // constructor, tree with root
    explicit BST(const T &rootItem) {
        // RootPtr becomes a new node with no children
        rootPtr = makeNode(rootItem);
    }

    // given an array of length n
    // create a tree to have all items in that array
    // with the minimum height (i.e. rebalance)
    BST(T array[], int n) {
        // TODO(Jenna)
        for (int i = 0; i < n; i++) {
            Add(array[i]);
        }
        Rebalance();
    }

    /**
     * Copy constructor copies the nodes in a binary search tree to the current
     * object.
     * @param bst - the BST being copied
     */
    // copy constructor
    explicit BST(const BST<T> &bst) {
        // TODO(Jenna)
        this->rootPtr = copyNodes(bst.rootPtr);
    }

    /**
     * The destructor function destroys the BST
     */
     ~BST() {
        // TODO(Jenna)
        Clear();
        delete rootPtr;
    }
    /*************************************/
    //          Functions                //
    /*************************************/
    // true if no nodes in BST
    bool IsEmpty() const {
        // TODO(Jenna)
        // if the root is null it's empty
        return rootPtr == nullptr;
    }

    // 0 if empty, 1 if only root, otherwise
    // height of root is max height of subtrees + 1
    int getHeight() const {
        // TODO(Jenna)
        // if empty return height = 0
        if (this->IsEmpty()) {
            return 0;
        } else {
            // pointer node for rootPtr created
            node *current = rootPtr;
            // return the height from the helper function
            return this->findHeight(current);
        }
    }

    // number of nodes in BST
    int NumberOfNodes() const {
        // TODO(Jenna)
        // if its empty, there are no nodes
        if (IsEmpty()) {
            return 0;
        }
        // if the root has no children, return 1
        if (isLeaf(rootPtr)) {
            return 1;
        } else {
            // start the counter at 0
            int count = 0;
            // uses recursive helper function to count all of the nodes
            count = getCount(rootPtr);
            // returns the total number of nodes
            return count;
        }
    }

    // add a new item, return true if successful
    bool Add(const T &item) {
        // if the tree is empty
        // TODO(Jenna)
        // make a new child leaf node of the item
        node *child = makeNode(item);
        if (IsEmpty()) {
            // the child node becomes the root node
            rootPtr = child;
            // insertion was successful, return true
            return true;
        } else {
            // prevents duplication and memory leaks :)
            if (this->Contains(item)) {
                // new node removed
                delete child;
                // new node dereferenced
                child = nullptr;
                // duplicate node not added
                return false;
            }
            // currentRoot is initialized at the root of the tree
            node *currentRoot = rootPtr;
            // initialize child's parent(root) node;
            node *parent;
            // while currentRoot isn't empty
            while (currentRoot) {
                // as we traverse down the tree, this keeps track of the root
                // for the newly added node
                parent = currentRoot;
                // if the child's data is greater than the current root's data
                // traverse down the right child nodes
                if (child->data > currentRoot->data)
                    currentRoot = currentRoot->rightPtr;
                    // Otherwise, traverse down the left child nodes
                else
                    currentRoot = currentRoot->leftPtr;
            }
            // if the new node's data is less than it's root's data
            if (child->data < parent->data)
                // make the newly added node the left child of that root
                parent->leftPtr = child;
                // otherwise add it to the root's right child node
            else
                parent->rightPtr = child;
            // node has been added - return true
            return true;
        }
    }

    // remove item, return true if successful
    bool Remove(const T &item) const {
        // TODO(Jenna)
        // if the tree is empty, return false
        if (IsEmpty()) {
            return false;
        }
        // if the item is not in the tree, return false
        if (!(Contains(item))) {
            return false;
        } else {
            // otherwise create a node starting at the root
            node* child = rootPtr;
            // create a second node to keep track of the target's root
            node* parent = child;
            // while the current node is not empty locate the node being removed
            while (child) {
                // if target is found, break out of the loop
                if (child->data == item) {
                    break;
                } else {
                    // parent node = child, child node traverses down the tree
                    parent = child;
                    // if the child's data is greater than the item, look left
                    if (child->data > item)
                        child = child->leftPtr;
                        // otherwise traverse through the right child nodes
                    else
                        child = child->rightPtr;
                }
            }
            if (parent != nullptr && child != nullptr) {
                // If the node has no children, simply remove the node
                if (isLeaf(child)) {
                    // if the child was a left child of the parent node, set
                    // it to null
                    if (parent->leftPtr == child) parent->leftPtr = nullptr;
                        // Otherwise, remove the right child
                    if (parent->rightPtr == child) parent->rightPtr = nullptr;
                    // delete the child node
                    delete child;
                    // derefence the node
                    child = nullptr;
                    // return true
                    return true;
                }
                // If the node has 1 child, replace the root with the child node
                // right child present, no left child
                if (!child->leftPtr && child->rightPtr) {
                    // If the node being removed was a left child node
                    if (parent->leftPtr == child) {
                        // set the parent's left child to the child's right node
                        parent->leftPtr = child->rightPtr;
                        // remove the node
                        delete child;
                        child = nullptr;
                    } else {    // if the node being removed was a right child
                        // node set parent's right node to child's right node
                        parent->rightPtr = child->rightPtr;
                        // remove the node
                        delete child;
                        child = nullptr;
                    }
                    // return true
                    return true;
                } else if (child->leftPtr && !child->rightPtr) {
                    // if the node being removed was the parent's left child
                    if (parent->leftPtr == child) {
                        // set the parent's left child to the child's left node
                        parent->leftPtr = child->leftPtr;
                        // remove node
                        delete child;
                        child = nullptr;
                    } else {  // Otherwise, it's the parent's right child
                        // parent's right child is set to the child's left node
                        parent->rightPtr = child->leftPtr;
                        // remove node
                        delete child;
                        child = nullptr;
                    }
                    // Node removed
                    return true;
                }
                // If the node has 2 children, replace with smallest descendant
                // of right
                if (!isLeaf(child)) {
                    // node created to locate the smallest descendant
                    node *currentSmallest = child->rightPtr;
                    // if the right child is a leaf
                    if (isLeaf(currentSmallest)) {
                        // replace the node with the data from the right child
                        child->data = currentSmallest->data;
                        // delete the currentSmallest node
                        delete currentSmallest;
                        currentSmallest = nullptr;
                        // set the child's right child to null
                        child->rightPtr = nullptr;
                    } else {  // traverse until smallest descendant located
                        // if the right child has a left child
                        if (child->rightPtr->leftPtr) {
                            // set the smallestChild node to that
                            node *smallestChild = child->rightPtr->leftPtr;
                            // node created for smallest Child's parent (root)
                            // node
                            node *smallestParent = child->rightPtr;
                            // while the smallestChild has a left child,
                            // traverse
                            while (smallestChild->leftPtr) {
                                // smallest parent node becomes smallest
                                // child node
                                smallestParent = smallestChild;
                                // smallest Child node traverses left
                                smallestChild = smallestChild->leftPtr;
                            }
                            // data is replaced with the smallest descendant's
                            // data
                            child->data = smallestChild->data;
                            // smallestChild node is deleted
                            delete smallestChild;
                            smallestChild = nullptr;
                            // smallest parent node's left pointer is set to
                            // null
                            smallestParent->leftPtr = nullptr;
                        } else {  // The node is replaced with the right child
                            child->data = child->rightPtr->data;
                            child->rightPtr = child->rightPtr->rightPtr;
                        }
                    }
                }
            }
            // removal was successful, return true;
            return true;
        }
    }

    // true if item is in BST
    bool Contains(const T &item) const {
        // TODO(Jenna)
        // if the tree is empty, return false
        if (IsEmpty()) {
            return false;
        } else {  // otherwise search through tree for value
            // child node created and set to the root
            node *child = rootPtr;
            // while all nodes have not been searched
            while (child) {
                // if the current node is the item, return true
                if (child->data == item) {
                    return true;
                } else {  // otherwise keep looking based on comparison
                    // if the current node's data is greater than the item,
                    // look left
                    if (child->data > item) {
                        child = child->leftPtr;
                    } else {  // otherwise, look right
                        child = child->rightPtr;
                    }
                }
            }
        }
        // if the value is not found, return false
        return false;
    }

    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of type T
    void InorderTraverse(void visit(const T &item)) const {
        // TODO(Jenna)
        // calls helper function to traverse the nodes
        inorderHelper(visit, rootPtr);
    }

    // preorder traversal: root-left-right
    void PreorderTraverse(void visit(const T &item)) const {
        // TODO(Jenna)
        // calls helper function to traverse the nodes
        preorderHelper(visit, rootPtr);
    }

    // postorder traversal: left-right-root
    void PostorderTraverse(void visit(const T &item)) const {
        // TODO(Jenna)
        // calls helper function to traverse the nodes
        postorderHelper(visit, rootPtr);
    }

    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree from scratch
    // so that resulting tree should be balanced
    void Rebalance() {
        // TODO(me)
        int size = NumberOfNodes();
        T* sortedArray = new T[size];
        inorderSorter(sortedArray, rootPtr, 0);
        Clear();
        rebalanceBST(sortedArray, 0, size - 1);
        delete[] sortedArray;
        sortedArray = nullptr;
    }

    // delete all nodes in tree
    void Clear() {
        // TODO(Jenna)
        // calls helper function to destroy the nodes
        destroy(rootPtr);
    }

    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BST<T> &other) const {
        // TODO(Jenna)
        // if they are different heights return false
        if (this->getHeight() != other.getHeight()) return false;
        // if they have a different number of nodes, return false
        if (NumberOfNodes() != other.NumberOfNodes()) return false;
        // otherwise use helper function to check each node, if same return true
        return areEqual(rootPtr, other.rootPtr);
    }

    // not == to each other
    bool operator!=(const BST<T> &other) const {
        // TODO(Jenna)
        // checks to see if they are equal and returns the negation
        return !(operator==(other));
    }

    /**
     * IDE's cppcheck complains that there is no = operator, implemented so
     * it would stop complaining :)
     */
    BST<T>& operator=(const BST<T> &that) {
        // avoid self-copy
        if (this != &that) {  // if the binary tree is not empty,
            if (rootPtr != NULL)
                // destroy the binary tree
                destroy(rootPtr);
            // that is empty
            if (that.rootPtr == NULL)
                // this is empty
                rootPtr = NULL;
            // otherwise copy each node into the tree
            else
               this->rootPtr = copyNodes(that.rootPtr);
        }
        // return the newly copied tree
        return *this;
    }
};

#endif  // BST_HPP
