#include <iostream>
#include "binarysearchtree.h"

int main(int argc, char *argv[])
{
    BinarySearchTree<int> bt(0);
    bt.addElement(1);
    bt.addElement(2);
    bt.addElement(3);
    bt.addElement(4);

    bt.printTree();

}
