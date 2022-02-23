#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class BinaryTreeNode
{
public:
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode *parent;

    // insert method returns the new node
    BinaryTreeNode *Insert(BinaryTreeNode *node, int data);
    // display method displays the tree
    void Display(BinaryTreeNode *node);
};

int main()
{

    BinaryTreeNode *root = nullptr; // root of the tree
    root = root->Insert(root, 10);
    root = root->Insert(root, 20);
    root = root->Insert(root, 30);
    root = root->Insert(root, 5);
    root = root->Insert(root, 15);

    root->Display(root);
}

void BinaryTreeNode ::Display(BinaryTreeNode *node)
{
    if (node == nullptr)
    {
        cout << " " << endl;
    }
    else
    {
        cout << "    " << node->data << " " << endl;
        Display(node->left);
        Display(node->right);
    }
}

BinaryTreeNode *BinaryTreeNode::Insert(BinaryTreeNode *node, int data)
{
    // If BinaryTree doesn't exist
    // create a new node as root
    // or it's reached when
    // there's no any child node
    // so we can insert a new node here
    if (node == NULL)
    {
        node = new BinaryTreeNode;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = nullptr;

        return node;
    }
    // If the given key is greater than
    // node's key then go to right subtree
    else if (node->data < data)
    {
        node->right = Insert(node->right, data);
        node->right->parent = node;

        return node;
    }
    // If the given key is smaller than
    // node's key then go to left subtree
    else
    {
        node->left = Insert(node->left, data);
        node->left->parent = node;

        return node;
    }
}