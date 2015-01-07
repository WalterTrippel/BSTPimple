#include "prettytree.h"

PrettyTree::PrettyTree():ConsoleTree() {}

PrettyTree::PrettyTree(std::initializer_list<Data> list):ConsoleTree(list) {}

PrettyTree::PrettyTree(const PrettyTree &other):ConsoleTree(other) {}

PrettyTree::PrettyTree(PrettyTree &&other):ConsoleTree(other) {}

PrettyTree::~PrettyTree() {}

void PrettyTree::printElements(TreeElements *array, int size, std::ostream &out) const
{
    for(int i = 0; i < size; ++i)
    {
        out << "(" << array[i].value << "->" << array[i].order << ")" << "\n";
    }
}
