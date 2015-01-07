#ifndef PRETTYTREE_H
#define PRETTYTREE_H

#include "consoletree.h"

class PrettyTree : public ConsoleTree
{
public:
    PrettyTree();
    PrettyTree(std::initializer_list<Data> list);
    PrettyTree(const PrettyTree & other);
    PrettyTree(PrettyTree && other);
    ~PrettyTree();

    PrettyTree & operator = (const PrettyTree & other) = default;
    PrettyTree & operator = (PrettyTree && other) = default;

private:
    void printElements(TreeElements * array, int size, std::ostream & out) const override;
};

#endif // PRETTYTREE_H
