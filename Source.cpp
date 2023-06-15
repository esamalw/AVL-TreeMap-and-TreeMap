/*
* Author: Esam Alwaseem
* Creation Date : 3 / 18 / 2023
* Modification Date : 3/ 24 / 2023
* Purpose : To program the implementation of AVLTreeMap and TreeMap following the steps of the question
* Question #4
*/

#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

// SearchTree from textbook
template <typename T, typename U>
class SearchTree
{
private:
    struct Node
    {
        T key;
        U value;
        Node* left;
        Node* right;
        int height;
    };
    Node* root;

public:
    SearchTree()
    {
        root = nullptr;
    }

    //Insert method
    void insert(const T& key, const U& value)
    {
        root = insert(root, key, value);
    }
    //Delete method
    void erase(const T& key)
    {
        root = erase(root, key);
    }
    //Other methods 
    bool contains(const T& key) const
    {
        return contains(root, key);
    }
    int height() const
    {
        return height(root);
    }

private:
    //Helper functions for inserting and deleting
    Node* insert(Node* node, const T& key, const U& value)
    {
        if (node == nullptr)
        {
            Node* newNode = new Node;
            newNode->key = key;
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }
        else if (key < node->key)
        {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, value);
        }
        else
        {
            node->value = value;
            return node;
        }

        // Balancing the tree
        node->height = max(height(node->left), height(node->right)) + 1;
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1 && key < node->left->key)
        {
            return rightRotate(node);
        }
        if (balanceFactor < -1 && key > node->right->key)
        {
            return leftRotate(node);
        }
        if (balanceFactor > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* erase(Node* node, const T& key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (key < node->key)
        {
            node->left = erase(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = erase(node->right, key);
        }
        else
        {
            // One or no child
            if (node->left == nullptr || node->right == nullptr)
            {
                Node* temp = node->left ? node->left : node->right;
                // No child case 
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    // One child case 
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                // Node with two children: Get the inorder successor 
                Node* temp = minValueNode(node->right);

                // Copy the inorder successor's data to this node 
                node->key = temp->key;
                node->value = temp->value;

                // Delete
                node->right = erase(node->right, temp->key);
            }
        }

        // If its only one node
        if (node == nullptr)
        {
            return node;
        }

        // tree balancing
        node->height = max(height(node->left), height(node->right)) + 1;
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }


    bool contains(Node* node, const T& key) const
    {
        if (node == nullptr)
        {
            return false;
        }
        else if (key < node->key)
        {
            return contains(node->left, key);
        }
        else if (key > node->key)
        {
            return contains(node->right, key);
        }
        else
        {
            return true;
        }
    }

    int height(Node* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    Node* minValueNode(Node* node) const
    {
        Node* current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    int getBalanceFactor(Node* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* node)
    {
        Node* x = node->left;
        Node* T2 = x->right;
        //  rotation 
        x->right = node;
        node->left = T2;
        // Update heights 
        node->height = max(height(node->left), height(node->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        // Return new root 
        return x;
    }

    Node* leftRotate(Node* node)
    {
        Node* x = node->right;
        Node* T2 = x->left;
        //  rotation 
        x->left = node;
        node->right = T2;
        //  Update heights 
        node->height = max(height(node->left), height(node->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        // Return new root 
        return x;
    }
};

int main() {
    // Empty AVL Tree 
    SearchTree<int, int> tree;

    // (a) Inserting 20 sample key-value pairs into the AVL Tree
    for (int i = 1; i <= 20; i++)
    {

        tree.insert(i, i * 2);

        // (d) and (c) printing
        cout << "Inserted Key: " << i << ", Value: " << i * 2 << endl;
        cout << "Height of AVL Tree: " << tree.height() << endl;
    }

    // (b) Deleting 5 keys from the AVL Tree
    for (int i = 1; i <= 5; i++)
    {
        int key = i;
        if (tree.contains(key))
        {
            tree.erase(key);
            cout << "Deleted Key: " << key << endl;
            cout << "Height of AVL Tree: " << tree.height() << endl;
        }
        else
        {
            cout << "Key " << key << " not found." << endl;
        }
    }

    return 0;
}
