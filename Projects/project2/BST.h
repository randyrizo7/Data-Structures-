
// Randy Rizo
// File: BST.h
// Date: 10/30/22
// Purpose: Define and implement class BST

#ifndef PROJECT2_BST_H
#define PROJECT2_BST_H
#include <sstream>
using namespace std;


template <typename T>
class BST {
public:
    BST();
    // Constructor
    // Precondition: none
    // Postcondition: initialize Node head pointing to nullptr
    ~BST();
    // Destructor
    // Precondition: none
    // Postcondition: call its helper function to delete LinkedList
    BST(BST &);
    // Copy constructor
    // Precondition: receive a reference of BST
    // Postcondition: call its helper function to copy present BST to new BST
    const BST<T> &operator=(BST<T> &);
    // Overload constructor
    // Precondition: receive a reference of BST
    // Postcondition: call its helper function to overload old BST with new BST
    void insert(T val);
    // Insert data to linked list
    // Precondition: receive a type T data
    // Postcondition: call its helper function to insert data to linkedList
    bool contains(T val);
    // Check if data is in the linked list
    // Precondition: receive a type T data
    // Postcondition: call on helper function to return boolean
    bool remove(T val);
    // Remove Node in linked list
    // Precondition: receive a type T data
    // Post-condition: call its helper function to remove the Node that
    //contains the data
    bool empty();
    // Check if the linked list is empty
    // Precondition: none
    // Postcondition: return boolean
    int size();
    // Return the size of the linked list
    // Precondition: none
    // Post-condition: call its helper function to return size of the linked list
    int getLeafCount();
    // Return the number of leaves
    // Precondition: none
    // Post-condition: call its helper function to return the number of leaves
    int getHeight();
    // Return the height of the linked list
    // Precondition: none
    // Post-condition: call its helper function to return the height of LL
    int getLevel(T val);
    // Return the level of the linked list
    // Precondition: none
    // Post-condition: call its helper function to return the level of
    // the linked list

    string getInOrderTraversal();
    // Return traversal in in-order
    // Precondition: none
    // Post-condition: call its helper function to return traversal in in-order
    string getAncestors(T val);
    // Return ancestors of the data
    // Precondition: receive a type T data
    // Post-condition: call its helper function to return ancestors of the data
    string getPreOrderTraversal();
    // Return traversal in pre-order
    // Precondition: none
    // Post-condition: call its helper function to return traversal in pre-order
    string getPostOrderTraversal();
    // Return traversal in post-order
    // Precondition: none
    // Post-condition: call its helper function to return traversal in post-order
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;                                // Root node of BST
    int treeSize;                              // hold size of the tree
    void destroy(Node* &);
    // Make Node point to nullptr
    // Precondition: receive a reference of Node
    // Postcondition: make Node point to nullptr
    void insert(T, Node* &);
    // Insert data to linked list
    // Precondition: receive two references of two Node
    // Postcondition: insert data to linkedList
    void copy(Node* &, Node* &);
    // Copy tree
    // Precondition: receive a reference of Node
    // Postcondition: copy constructor
    bool contains(T, Node* &);
    // Check if data is in the linked list
    // Precondition: receive a reference of Node and type T data
    // Postcondition: return boolean
    bool remove(T val, Node* &);
    // Remove Node in linked list
    // Precondition: receive a reference of Node and type T data
    // Postcondition: call its helper function and remove the Node
    // that contains the data
    int size(Node* &, int &);
    // Return the size of the linked list
    // Precondition: receive a reference of Node
    // Postcondition:
    int getLeafCount(Node* &, int &);
    // Return the number of leaves
    // Precondition: receive a reference of Node
    // Postcondition: return the number of leaves
    int getHeight(Node* &);
    // Return the height of the linked list
    // Precondition: receive a reference of Node
    // Postcondition: return the height of the linked list
    int getLevel(T val, Node* &);
    // Return ancestors of the data
    // Precondition: receive a reference of Node, a reference of stringstream
    // variable, and a type T varuable
    // Postcondition: return ancestors of the data
    void getAncestors(T val, stringstream &ss, Node* &node);
    // Return ancestors of the data
    // Precondition: receive a reference of Node, a reference of stringstream
    // variable, and a type T varuable
    // Postcondition: return ancestors of the data
    void getOrderTraversal(Node* &, stringstream &, string);
    //
};


// CONSTRUCTOR METHODS
template <typename T>
BST<T>::BST() {
    root = nullptr;
    treeSize = 0;
}

template <typename T>
BST<T>::~BST() {
    destroy(root);
}

template <typename T>
BST<T>::BST(BST &obj) {
    copy(root, obj.root);
    treeSize = obj.treeSize;
}

template <typename T>
const BST<T> & BST<T>::operator=(BST &obj) {
    if (this != &obj) {
        if (root != nullptr) destroy(root);
        copy(root, obj.root);
        treeSize = obj.treeSize;
    }
    return *this;
}

//PUBLIC METHODS
template <typename T>
void BST<T>::insert(T val) {
    insert(val, root);
}

template <typename T>
bool BST<T>::contains(T val) {
    if (empty()) return false;
    return contains(val, root);
}

template <typename T>
bool BST<T>::remove(T val) {
    return remove(val, root);
}

template <typename T>
bool BST<T>::empty() {
    return root == nullptr;
}

template <typename T>
int BST<T>::size() {
    int count = 0;
    return size(root, count);

}

template <typename T>
int BST<T>::getLeafCount() {
    int count = 0;
    return getLeafCount(root, count);
}

template <typename T>
int BST<T>::getHeight() {
    return getHeight(root);
}

template <typename T>
int BST<T>::getLevel(T val) {
    return getLevel(val, root);
}

template <typename T>
string BST<T>::getAncestors(T val) {
    stringstream ss;
    getAncestors(val, ss, root);
    return ss.str();
}

template <typename T>
string BST<T>::getPreOrderTraversal() {
    stringstream ss;
    getOrderTraversal(root, ss, "preorder");
    return ss.str();
}

template <typename T>
string BST<T>::getInOrderTraversal() {
    stringstream ss;
    getOrderTraversal(root, ss, "inorder");
    return ss.str();
}

template <typename T>
string BST<T>::getPostOrderTraversal() {
    stringstream ss;
    getOrderTraversal(root, ss, "postorder");
    return ss.str();
}

// PRIVATE METHODS
template <typename T>
void BST<T>::destroy(Node* &node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
    treeSize--;
}

template <typename T>
void BST<T>::insert(T val, Node* &node) {
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->left = newNode->right= nullptr;
        node = newNode;
        treeSize++;
    } else if (val != node->data)
        insert(val, val > node->data ? node->right: node->left);
}

template <typename T>
void BST<T>::copy(Node* &targetNode, Node* &originalNode) {
    if (originalNode == nullptr) targetNode = nullptr;
    else {
        targetNode = new Node;
        targetNode->data = originalNode->data;
        copy(targetNode->left, originalNode->left);
        copy(targetNode->right, originalNode->right);
    }
}

template <typename T>
bool BST<T>::contains(T val, Node* &node) {
    if (node == nullptr) return false;
    if (node->data == val) return true;
    return contains(val, val>node->data?node->right:node->left);
}

template <typename T>
bool BST<T>::remove(T val, Node* &node) {
    if (node == nullptr) return false;

    if (val != node->data)
        return remove(val, val > node->data ? node->right : node->left);
    else {
        Node* curr = nullptr;
        if(node->left == nullptr) {
            curr = node;
            node = node->right;
            delete curr;
        }
        else if (node->right == nullptr) {
            curr = node;
            node = node->left;
            delete curr;
        }
        else {
            curr = node->right;
            while (curr->left != nullptr)
                curr = curr->left;
            node->data = curr->data;
            return remove(curr->data, node->right);
        }
    }
    treeSize--;
    return true;
}

template <typename T>
int BST<T>::getLevel(T val, Node* &node) {
    if (node->data == val) return 0;
    else return 1 + getLevel(val, val > node->data ? node->right : node->left);
}

template <typename T>
int BST<T>::size(Node* &node, int &count) {
    if (node != nullptr) {
        count++;
        size(node->left, count);
        size(node->right, count);
    }
    return count;
}

template <typename T>
int BST<T>::getLeafCount(Node* &node, int &count) {
    if (node != nullptr) {
        getLeafCount(node->left, count);
        getLeafCount(node->right, count);
        if (node->left == nullptr && node->right == nullptr)
            count++;
    }
    return count;
}

template <typename T>
int BST<T>::getHeight(Node* &node) {
    if (node == nullptr)
        return 0;
    else
        return max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <typename T>
void BST<T>::getOrderTraversal(Node* &node, stringstream &ss, string type) {
    if (node != nullptr) {
        if (type == "preorder") ss << node->data << " ";
        getOrderTraversal(node->left, ss, type);
        if (type == "inorder") ss << node->data << " ";
        getOrderTraversal(node->right, ss, type);
        if (type == "postorder") ss << node->data << " ";
    }
}


template <typename T>
void BST<T>::getAncestors(T val, stringstream &ss, Node* &node) {
    if (node->data != val) {
        ss << node->data << " ";
        getAncestors(val, ss, val > node->data ? node->right : node->left);
    }
}



#endif //PROJECT2_BST_H
