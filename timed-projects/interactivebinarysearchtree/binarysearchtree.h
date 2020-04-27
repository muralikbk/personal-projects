#ifndef binarysearchtree_h
#define binarysearchtree_h

#include "Status.h"
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

//Templatizing  - because why not!
template <typename T>
class BinarySearchTree
{
 
    //I am declaring TreeNode as a struct since within a BinarySearchTree class
    // I want to be able to access all the members   
    //I am declaring it within the class so that this struct is not available
    //outside the class
    struct TreeNode
    {

        T value;
        TreeNode *left;
        TreeNode *right;
        //Default constructor
        TreeNode(): value(), left(NULL), right(NULL)
        {}
        //Parameterized constructor
        TreeNode(T inVal): value(inVal), left(NULL), right(NULL)
        {}
        //Copy constructor
        TreeNode(const TreeNode &in):value(in.value), left(NULL), right(NULL)
        {
            //This makes a deep copy
            if(NULL != in.left) left = new TreeNode(in->left);
            if(NULL != in.right) right = new TreeNode(in->right);
            
        }
        //Assignment operator
        TreeNode& operator=(const TreeNode &in)
        {
            value = in.value;

            //This makes a deep copy
            if(NULL != in.left) left = new TreeNode(in->left);
            if(NULL != in.right) right = new TreeNode(in->right);

            return *this;
        }
        //Destructor
        ~TreeNode()
        {
            delete left;
            delete right; 
        }

    };

    TreeNode root;

    //Making default constructor private since I want root to be always initialized
    BinarySearchTree()
    {}

    //Adds a node to the tree and returns pointer to that node
    TreeNode* addNode(TreeNode* node, const T& in, Status &stat)
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

		//Ideally, shouldn't come here
		stat.returnCode = -99;
		stat.message = "TreeNode.addNode() unknown issue";
		return NULL;
    } 

    //Private helper functions
    void buildTreeList(list<string> &lst, 
                    list<string>::iterator &li,
                    TreeNode *node,
                    int level = 0)

	{
		stringstream str;
		//This is the root
		if(level == 0)
		{
			str << node->value;
			li = lst.begin();
			lst.insert(li, str.str());
			++li; //li is now at root
		} 
		else
		{
			for(int i = 0; i < level; i++)
			{
				str << "  ";
			}
			str << "-" << node->value;
			lst.insert(li, str.str());
		}

		if(NULL != node->right)
		{
			buildTreeList(lst, li, node->right, level + 1);
		}
		if(NULL != node->left)
		{
			++li;
			buildTreeList(lst, li, node->right, level + 1);
		}
		--li;
	}

    public:
    //Parameterized constructor
    BinarySearchTree(const T& in):root(in)
    {}
    //Copy constructor
    BinarySearchTree(const BinarySearchTree &in):root(in.root)
    {}
    //Assignment operator
    BinarySearchTree& operator=(const BinarySearchTree &in)
    {
        root = in.root;
        return *this;
    }
    Status addElement(const T& in)
	{
		Status st(0,"");
		//For insertion, we start with the root. 
		// Then recursively go to left node if new value is less than node value
		// or to right node if new value is greater than node value
		// return an error message if duplicate is found
		addNode(&root, in, st); 

		return st;
	}
    void printTree()
	{
		list<string> lst;
		list<string>::iterator li;
		
		buildTreeList(lst, li, &root);
		
		for(li = lst.begin(); li != lst.end(); ++li)
		{
			cout << *li;
		}

	}
};


#endif
