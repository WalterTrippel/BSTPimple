#include <iostream>
#include <utility>
#include "binarytree.h"
#include "consoletree.h"
#include "prettytree.h"

using namespace std;

int main()
{
    ConsoleTree * tree = nullptr;
    tree = new PrettyTree;
    for(int i = 0; i < 8; ++i)
    {
        cin >> *tree;
    }
    cout << *tree;
    return 0;
}

