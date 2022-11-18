
#ifndef __COLORBST__
#define __COLORBST__

#include <iostream>
#include <string>

using namespace std;


// forward declaration
template<typename T, typename CMP = std::less<T> >
class ColorBSTNode; //declare the node class

template<typename T, typename CMP = std::less<T> >
class ColorBST; //declare the tree class

template <typename T, typename CMP>
class ColorBSTNode
{
public:
    void insert_node(ColorBSTNode* new_node);

    T data;

private:
    char color;
    ColorBSTNode<T, CMP>* left;  //the left child of a node
    ColorBSTNode<T, CMP>* right;  // the right child of a node
    CMP comparator;
    friend class ColorBST<T, CMP>;
};

template <typename T, typename CMP>
class ColorBST
{
public:
    ColorBST();
    void insert(T data); //inserts a node (with value data and color c) to a tree and the color has a default value: 'r'
    void insert(T data, char color); //inserts a node (with value data and color c) to a tree and provide the color

    void ascending_print() const; //prints all elements in the ascending order
    void descending_print() const; //prints all elements in the descending order
    T largest() const; //returns the largest element

    bool BlackRoot() const; //returns true if the tree has a black root
    bool NoDoubleRed() const; //returns true if the tree has no double-red nodes
    bool BlackDepth() const; //returns true if the black depth property is preserved


private:
    ColorBSTNode<T, CMP>* root; //pointer to the root node
    void ascending_print_helper(ColorBSTNode<T, CMP>* root) const; //a helper function to the ascending_print function
    void descending_print_helper(ColorBSTNode<T, CMP>* root) const; //a helper function to the decending_print function
    bool NoDoubleRed_Helper(ColorBSTNode<T, CMP>* root) const; //a helper function to the no double red function
    pair<int, bool> BlackDepth_Helper(ColorBSTNode<T, CMP>* root) const; //a helper function to the black depth function
};



template <typename T, typename CMP>
void ColorBSTNode<T, CMP>::insert_node(ColorBSTNode* new_node)
{
    if (comparator(new_node->data, this->data)) // if the inserted node is less than the current node
    {
        if (left == nullptr) left = new_node; //if there is no left child of the current node, make the inserted node as the left child of the current node
        else left->insert_node(new_node); //compare the inserted node with the left child of the current node
    }
    else if (comparator(this->data, new_node->data)) // repeat the above procedures to compare the value of the current node and the value of the inserted node
    {
        if (right == nullptr) right = new_node;
        else right->insert_node(new_node);
    }
}

template <typename T, typename CMP>
T ColorBST<T, CMP>::largest() const //go through the nodes to reach the node in the rightest position
{
    auto prev = root;
    auto curr = root;
    while (curr != nullptr) {
        prev = curr;
        curr = curr->right; // go to the next right node
    }
    return prev->data;
}

template <typename T, typename CMP >
ColorBST<T, CMP>::ColorBST() : root(nullptr) { // default(empty) ColorBst class
}

template <typename T, typename CMP >
void ColorBST<T, CMP>::insert(T data) // insert a data to the tree class
{
    ColorBSTNode<T, CMP>* new_node = new ColorBSTNode<T, CMP>();  //create a pointer to new node with the given data
    new_node->data = data;
    new_node->color = 'r'; //the color of the inserted node has a default value: 'r'
    new_node->left = nullptr; //the inserted node defaultly has no left child
    new_node->right = nullptr; //the inserted node defaultly has no right child
    if (root == nullptr) { //if the class is empty(root is a null node)
        root = new_node; //set the inserted node as the root
    }
    else {
        root->insert_node(new_node); //insert the inserted node to the tree recursively, the start of insertion is the root node of the tree
    }
}

template <class T, typename CMP>
void ColorBST<T, CMP>::insert(T data, char color) //almost the same as the above insert function, except that the color of the inserted node is given 
{
    ColorBSTNode<T, CMP>* new_node = new ColorBSTNode<T, CMP>();
    new_node->data = data;
    new_node->color = color;
    new_node->left = nullptr;
    new_node->right = nullptr;
    if (root == nullptr) {
        root = new_node;
    }
    else {
        root->insert_node(new_node);
    }
}

template <class T, typename CMP>
bool ColorBST<T, CMP>::BlackRoot() const {
    return root == nullptr || root->color == 'b';
}

template <class T, typename CMP>
bool ColorBST<T, CMP>::NoDoubleRed_Helper(ColorBSTNode<T, CMP>* root) const {
    if (root == nullptr) //if the tree is empty, there is no double red issue
        return true;
    if (root->color == 'r') { //when the current node is in red color
        if (root->left != nullptr && root->left->color == 'r') // if the left child of the current node exists and the color is also red, then double red issue happen
            return false;
        if (root->right != nullptr && root->right->color == 'r') // if the right child of the current node exists and the color is also red, then double red issue happen
            return false;
    }
    return NoDoubleRed_Helper(root->left) && NoDoubleRed_Helper(root->right); //recursively check the double red issue for the left and right branches of the root
}

template <class T, typename CMP>
bool ColorBST<T, CMP>::NoDoubleRed() const {
    return NoDoubleRed_Helper(root);
}

template <class T, typename CMP>
pair<int, bool> ColorBST<T, CMP>::BlackDepth_Helper(ColorBSTNode<T, CMP>* node) const {
    if (node == nullptr) { //then the node is a null node, no black depth issue
        return std::make_pair(1, true);
    }
    pair<int, bool> left_subtree_info = BlackDepth_Helper(node->left);
    if (!left_subtree_info.second) { // if the left subtree cannot meet the black depth property
        return make_pair(-1, false);
    }
    pair<int, bool> right_subtree_info = BlackDepth_Helper(node->right);
    if (!right_subtree_info.second) { // if the right subtree cannot meet the black depth property
        return make_pair(-1, false);
    }
    if (left_subtree_info.first != right_subtree_info.first) {
        return make_pair(-1, false);
    }
    auto count = left_subtree_info.first + int(node->color == 'b');
    return make_pair(count, true);
}

template <class T, typename CMP>
bool ColorBST<T, CMP>::BlackDepth() const { //returns true if the black depth property is preserved
    auto verdict = BlackDepth_Helper(root);
    return verdict.second;
}

template <class T, typename CMP>
void ColorBST<T, CMP>::ascending_print_helper(ColorBSTNode<T, CMP>* root) const {
    if (root == nullptr) {
        return;
    }
    ascending_print_helper(root->left);  //print the left(smaller) node first
    cout << root->data << " ";
    ascending_print_helper(root->right);
}

template <class T, typename CMP>
void ColorBST<T, CMP>::descending_print_helper(ColorBSTNode<T, CMP>* root) const {
    if (root == nullptr) {
        return;
    }
    descending_print_helper(root->right); //print the right(larger) node first
    cout << root->data << " ";
    descending_print_helper(root->left);
}

template <class T, typename CMP>
void ColorBST<T, CMP>::ascending_print() const { //prints all elements in the ascending order
    ascending_print_helper(root);
    cout << endl;
}

template <class T, typename CMP>
void ColorBST<T, CMP>::descending_print() const { //prints all elements in the descending order
    descending_print_helper(root);
    cout << endl;
}

#endif