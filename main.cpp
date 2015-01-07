#include <iostream>
#include <utility>
#include "binarytree.h"
#include "consoletree.h"

using namespace std;

int main()
{
    ConsoleTree tree = {1, 2, 5, -7, 8};

    cout << tree << "\n";
    cin >> tree;
    cout << tree << "\n";
    tree.remove(2);
    cout << tree << "\n";
    return 0;
}

