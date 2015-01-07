#include "consoletree.h"

ConsoleTree::ConsoleTree():BinaryTree() {}

ConsoleTree::ConsoleTree(std::initializer_list<Data> list):BinaryTree(list) {}

ConsoleTree::ConsoleTree(const ConsoleTree &other):BinaryTree(other) {}

ConsoleTree::ConsoleTree(ConsoleTree &&other):BinaryTree(other) {}

ConsoleTree::~ConsoleTree() {}

void ConsoleTree::printElements(TreeElements * array, int size, std::ostream & out) const
{
    for(int i = 0; i < size - 1; ++i)
    {
        out << array[i].value << ", ";
    }
    out << array[size - 1].value << "\n";
}

std::ostream & operator << (std::ostream & out, ConsoleTree & other)
{
    TreeElements * array = nullptr;
    int size  = 0;
    other.getElements(array, size);
    other.printElements(array, size, out);
    return out;
}

std::istream & operator >> (std::istream & in, ConsoleTree & other)
{
    Data data;
    in >> data;
    other.push(data);
    return in;
}
