#ifndef binarysearchtree_cpp
#define binarysearchtree_cpp
/*
#include "binarysearchtree.h"
#include <list>
#include <sstream>

using namespace std;


template <typename T>
TreeNode* BinarySearchTree::addNode(TreeNode* node, const T& in, Status &stat)
{
    if(NULL == node)
    {
        node = new TreeNode(in);
        return node;
    } 

    if(in == node->value)
    {
        stat.returnCode = 1;
        stat.message = "Duplicate element, skipping";
        return NULL;
    }    
    
    if(in > node->value)
    {
        return addNode(node->right, in, stat);
    }

    if(in < node->value)
    {
        return addNode(node->left, in, stat);
    }
} 


template <typename T>
Status BinarySearchTree::addElement(const T& in)
{
    Status st(0,"");
    //For insertion, we start with the root. 
    // Then recursively go to left node if new value is less than node value
    // or to right node if new value is greater than node value
    // return an error message if duplicate is found
    addNode(&root, in, st); 

    return st;
}

template <typename T>
void BinarySearchTree::buildTreeList(list<string> &list, 
                    list<string>::iterator li,
                    TreeNode *node,
                    int level = 0)
{
    stringstream str;
    //This is the root
    if(level == 0)
    {
        str << node->value;
        li = list.begin();
        list.emplace(li, str.str());
        ++li; //li is now at root
    } 
    else
    {
        for(int i = 0; i < level; i++)
        {
            str << "  ";
        }
        str << "-" << node->value;
        list.emplace(li, str.str());
    }

    if(NULL != node->right)
    {
        buildTreeList(list, li, node->right, level + 1);
    }
    if(NULL != node->left)
    {
        ++li;
        buildTreeList(list, li, node->right, level + 1);
    }
    --li;
}

template <typename T>
void BinarySearchTree::printTree()
{
    list<string> list;
    list<string>::iterator li;
    
    buildTreeList(list, li, root);
    
    for(li = list.begin(); li != list.end; ++li)
    {
        cout << *li;
    }

}
*/
#endif
