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
    ~BinaryTree();

    BinaryTree & operator = (const BinaryTree & other);
    BinaryTree & operator = (BinaryTree && other);

    void clear();
    void push(Data data);
    void remove(Data data);
    bool isEmpty() const;

    friend std::ostream & operator << (std::ostream & out, const BinaryTree & other);
    friend std::istream & operator >> (std::istream & in, const BinaryTree & other);
private:
    class BinaryTreeImplementation;
    BinaryTreeImplementation  * pimpl;
};

#endif // BINARYTREE_H
