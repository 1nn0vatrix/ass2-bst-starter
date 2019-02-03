/**
 * Testing BST - Binary Search Tree functions
 *
 * @author Jenna Martin
 * @date February 2, 2019
 */

#include <iostream>
#include <sstream>
#include <cassert>
#include <string>

#include "bst.hpp"

using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
 public:
    TreeVisitor() = delete;

    // insert output to SS rather than cout, so we can test it
    static stringstream SS;

    static string GetSS() {
        return SS.str();
    }

    static void ResetSS() {
        SS.str(string());
    }

    // instead of cout, insert item into a string stream
    static void visitor(const string &item) {
        SS << item;
    }

    // instead of cout, insert item into a string stream
    static void visitor(const int &item) {
        SS << item;
    }
};

// initialize the static variable
stringstream TreeVisitor::SS;

/**
 * Function I provided for the class test cases, this adds values (including
 * a duplicate and inorder traverses, then removes nodes including one not in
 * the tree and traveses the new BST.
 */
void test_jenna90() {
    // One-Parameter constructor
    BST<int> b1(1);
    // Adding items to BST
    b1.Add(4);
    b1.Add(8);
    b1.Add(3);
    b1.Add(12);
    b1.Add(9);
    b1.Add(-24);
    // adding duplicate item
    b1.Add(4);
    TreeVisitor::ResetSS();
    b1.InorderTraverse(TreeVisitor::visitor);
    string result = "-241348912";
    // asserting it outputs without duplicate
    assert(TreeVisitor::GetSS() == result);
    // get the height of the tree
    assert(b1.getHeight() == 5);
    // get the number of nodes in the tree
    assert(b1.NumberOfNodes() == 7);

    // removing values from BST
    // removing root
    assert(b1.Remove(1) == 1);
    // removing 1 child node
    assert(b1.Remove(4) == 1);
    // remove leaf node
    assert(b1.Remove(9) == 1);
    // remove leaf node
    assert(b1.Remove(0) == 0);

    // reset stringstream
    TreeVisitor::ResetSS();
    b1.InorderTraverse(TreeVisitor::visitor);
    result = "-243812";
    // testing that the removal works
    assert(TreeVisitor::GetSS() == result);
    // BST test height after removal
    assert(b1.getHeight() == 3);
    // test number of nodes in BST
    assert(b1.NumberOfNodes() == 4);

    // Yay, you did it!
    cout << "Ending test_Jenna90" << endl;
}

/**
 * This set tests each the constructors
 */
void test_Constructors() {
    cout<< "\n\nTesting all constructors " << endl;
    // Default Empty Constructor
    BST<int> b1;
    assert(b1.IsEmpty() == 1);
    // One parameter constructor
    BST<string> b2("Hello");
    assert(b2.IsEmpty() == 0);
    assert(b2.NumberOfNodes() == 1);
    // Copy Constructor
    BST<string> b3(b2);
    assert((b3 == b2) == 1);
    int testArray[10] = {5, 2, 7, 9, 3, 12, 23, 11, 1, 4};
    BST<int> b4(testArray, 10);
    assert(b4.NumberOfNodes() == 10);
    // balanced tree should have a height of 4
    assert(b4.getHeight() == 4);
    cout << "Testing Constructors Complete!" << endl;
}

/**
 * This ensures the tree is cleared when the clear function is called
 */
void test_Clear() {
    cout << "\n\nTesting Clear() function" << endl;
    string quickString[]={"C", "A", "B", "D", "H"};
    BST<string> b1(quickString, 5);
    assert(b1.IsEmpty() == 0);
    b1.Clear();
    assert(b1.IsEmpty() == 1);
    cout << "Clear successful!" << endl;
}

/**
 * This tests the traversal using the array implementation to ensure the tree
 * balances and traverses correctly
 */
void test_traversal() {
    cout << "\n\nTesting Traversal of BST constructed from array" << endl;
    int quickInt[]={8, 15, 22, 4, 6, 12, 1};
    BST<int> b1(quickInt, 7);

    TreeVisitor::ResetSS();
    b1.InorderTraverse(TreeVisitor::visitor);
    string result = "1468121522";
    assert(TreeVisitor::GetSS() == result);
    cout << "Inorder Traversal Successful!" << endl;

    TreeVisitor::ResetSS();
    b1.PreorderTraverse(TreeVisitor::visitor);
    result = "8416151222";
    assert(TreeVisitor::GetSS() == result);
    cout << "Preorder Traversal Successful!" << endl;

    TreeVisitor::ResetSS();
    b1.PostorderTraverse(TreeVisitor::visitor);
    result = "1641222158";
    assert(TreeVisitor::GetSS() == result);
    cout << "Preorder Traversal Successful!" << endl;

    // Empty tree
    BST<int> b2;
    TreeVisitor::ResetSS();
    b2.InorderTraverse(TreeVisitor::visitor);
    result = "";
    assert(TreeVisitor::GetSS() == result);
    cout << "Empty Inorder Traversal Successful!" << endl;
}

/**
 * cLion cppcheck wanted an assignment operator for the copy constructor
 * so I figured I would test that too. I assign, then check for equality,
 * modify one and check for inequality.
 */
void test_Assignment() {
    cout << "\n\nTesting Assignment and Equality" << endl;
    BST<int> b1(8);
    b1.Add(5);
    b1.Add(15);
    b1.Add(2);
    b1.Add(6);
    b1.Add(17);
    b1.Add(7);
    cout << "Creating a copy BST" << endl;
    // testing assignment operator cLion wanted implemented w/copy constructor
    BST<int> b2;
    b2 = b1;
    cout << "Checking that the BSTs are Equal" << endl;
    assert((b2 == b1) == 1);
    cout << "Copy successful" << endl;
    cout << "Removing a node from second BST" << endl;
    b2.Remove(6);
    cout << "Checking for inequality now" << endl;
    assert((b2 != b1) == 1);
    cout << "Second BST changed successfully" << endl;
}

void testBSTConstructors() {
    cout << "\n\n* Testing 0 param constructor, ==, !=, IsEmpty, and XTraverse"
         << endl;
    BST<string> b1;
    BST<string> b2;
    BST<string> b3;
    // == and != for empty trees
    assert(b1 == b2 && (!(b1 != b2)));
    b1.Add("c");
    b2.Add("c");
    b3.Add("b");
    // == and !- for 1-node trees b1, b2, b3
    assert(b1 == b2 && (!(b1 != b2)));
    assert(b1 != b3 && (!(b1 == b3)));

    b1.Add("a");
    b1.Add("f");
    b1.Add("g");
    b1.Add("x");
    b2.Add("a");
    b2.Add("f");
    b2.Add("g");
    b2.Add("x");
    // == for 5-node trees b1, b2
    assert(b1 == b2 && (!(b1 != b2)));

    BST<string> b4(b3);
    // copy constructor for 1-node trees b3, b4
    assert(b3 == b4 && (!(b3 != b4)));

    BST<string> b5(b1);
    // copy constructor for 5-node trees b1, b5
    assert(b1 == b5 && (!(b5 != b1)));

    BST<string> b7("b");
    // 1-param constructor for 1-node trees b3, b7
    assert(b3 == b7 && (!(b3 != b7)));

    cout << "b1 is: " << endl;
    cout << b1 << endl;

    TreeVisitor::ResetSS();
    b1.InorderTraverse(TreeVisitor::visitor);
    string result = "acfgx";
    assert(TreeVisitor::GetSS() == result);
    cout << "Inorder Traversal Successful!" << endl;

    TreeVisitor::ResetSS();
    b1.PreorderTraverse(TreeVisitor::visitor);
    result = "cafgx";
    assert(TreeVisitor::GetSS() == result);
    cout << "Preorder Traversal Successful!" << endl;

    TreeVisitor::ResetSS();
    b1.PostorderTraverse(TreeVisitor::visitor);
    result = "axgfc";
    assert(TreeVisitor::GetSS() == result);
    cout << "Postorder Traversal Successful!" << endl;

    cout << "Done testBSTConstructors" << endl;
}

void testBSTAll() {
    testBSTConstructors();
    test_jenna90();
    test_Clear();
    test_Constructors();
    test_traversal();
    test_Assignment();
}
