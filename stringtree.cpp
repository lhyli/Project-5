//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class TreeNode
//{
//    public:
//        void insert_node(TreeNode* new_node);
//    private:
//        string data;
//        TreeNode* left;
//        TreeNode* right;
//        friend class BinarySearchTree;
//};
//
//class BinarySearchTree
//{
//    public:
//        BinarySearchTree();
//        void insert(string data);
//    private:
//        TreeNode* root;
//};
//
//BinarySearchTree::BinarySearchTree()
//{
//    root = nullptr;
//}
//
//void BinarySearchTree::insert(string data)
//{
//    TreeNode* new_node = new TreeNode;
//    new_node->data = data;
//    new_node->left = nullptr;
//    new_node->right = nullptr;
//    if (root == nullptr) root = new_node;
//    else root->insert_node(new_node);
//}
//
//void TreeNode::insert_node(TreeNode* new_node)
//{
//    if (new_node->data < data)
//    {
//        if (left == nullptr) left = new_node;
//        else left->insert_node(new_node);
//    }
//    else if (data < new_node->data)
//    {
//        if (right == nullptr) right = new_node;
//        else right->insert_node(new_node);
//    }
//}
//
