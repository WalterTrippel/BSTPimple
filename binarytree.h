#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <exception>

typedef int Data;

class BSTException : public std::exception
{
    const char * what() const throw()
    {
        return "The element was not found!";
    }
};

class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(std::initializer_list<int> list);
    BinaryTree(const BinaryTree & other);
    BinaryTree(BinaryTree && other);
    virtual ~BinaryTree();

    BinaryTree & operator = (const BinaryTree & other);
    BinaryTree & operator = (BinaryTree && other);

    void clear();
    void push(Data data);
    void remove(Data data);
    bool isEmpty() const;

protected:
    virtual void inorder(std::ostream & out);

private:
    class Implementation;
    Implementation  * pimpl;
};

#endif // BINARYTREE_H
