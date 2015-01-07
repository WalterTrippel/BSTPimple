#include "consoletree.h"

ConsoleTree::ConsoleTree():BinaryTree() {}

ConsoleTree::ConsoleTree(std::initializer_list<Data> list):BinaryTree(list) {}

ConsoleTree::ConsoleTree(const ConsoleTree &other):BinaryTree(other) {}

ConsoleTree::ConsoleTree(ConsoleTree &&other):BinaryTree(other) {}

ConsoleTree::~ConsoleTree() {}

std::ostream & operator << (std::ostream & out, ConsoleTree & other)
{
    other.inorder(out);
    return out;
}

std::istream & operator >> (std::istream & in, ConsoleTree & other)
{
    Data data;
    in >> data;
    other.push(data);
    return in;
}
