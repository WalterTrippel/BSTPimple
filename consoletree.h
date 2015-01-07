#ifndef CONSOLETREE_H
#define CONSOLETREE_H

#include "binarytree.h"

class ConsoleTree : public BinaryTree
{
public:
    ConsoleTree();
    ConsoleTree(std::initializer_list<Data> list);
    ConsoleTree(const ConsoleTree & other);
    ConsoleTree(ConsoleTree && other);
    virtual ~ConsoleTree();

    ConsoleTree & operator = (const ConsoleTree & other) = default;
    ConsoleTree & operator = (ConsoleTree && other) = default;

    friend std::ostream & operator << (std::ostream & out, ConsoleTree & other);
    friend std::istream & operator >> (std::istream & in, ConsoleTree & other);

private:
    virtual void printElements(TreeElements * array, int size, std::ostream & out) const;
};

#endif // CONSOLETREE_H
