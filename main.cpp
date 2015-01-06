#include <iostream>
#include "binarytree.h"

using namespace std;

int main()
{
    BinaryTree tree = {1, 2, 5, -7, 8};
    cin >> tree;
    cout << tree << "\n";
    tree.remove(5);
    cout << tree << "\n";
    tree.clear();
    cout << tree << "\n";
    for(int i = 0; i < 5; ++i)
    {
        cin >> tree;
    }
    cout << tree << "\n";
    tree.remove(111);
    return 0;
}

