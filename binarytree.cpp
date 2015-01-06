#include "binarytree.h"

class BinaryTree::BinaryTreeImplementation
{
public:
    BinaryTreeImplementation();
    BinaryTreeImplementation(std::initializer_list<int> list);
    BinaryTreeImplementation(const BinaryTreeImplementation & other);
    BinaryTreeImplementation(BinaryTreeImplementation && other);
    ~BinaryTreeImplementation();

    BinaryTreeImplementation & operator = (const BinaryTreeImplementation & other);
    BinaryTreeImplementation & operator = (BinaryTreeImplementation && other);

    void clear();
    void push(Data data);
    void remove(Data data);
    bool isEmpty() const;

    friend std::ostream & operator << (std::ostream & out, BinaryTreeImplementation & other)
    {
        BinaryTreeImplementation::TreeNode * node  = other.rightMost(other.root);
        other.inorder(other.root, node, out);
        return out;
    }

    friend std::istream & operator >> (std::istream & in, BinaryTreeImplementation & other)
    {
        Data data;
        in >> data;
        other.push(data);
        return in;
    }

private:
    struct TreeNode
    {
        TreeNode();
        TreeNode(Data data);
        TreeNode(TreeNode && other);
        ~TreeNode();

        TreeNode & operator = (TreeNode && other);
        void push(Data data);

        TreeNode * left;
        TreeNode * right;
        Data data;
    } * root;

    void clear(TreeNode *& root);
    void copy(TreeNode *& copiedNode, TreeNode * otherNode);
    void swap(TreeNode *& rvalue, TreeNode * lvalue);
    void inorder(TreeNode * node, TreeNode * rightMost, std::ostream & out);
    TreeNode * rightMost(TreeNode * node) const;
    TreeNode * findMin(TreeNode * node) const;
};


/**
 * TreeNode implementation
*/
BinaryTree::BinaryTreeImplementation::TreeNode::TreeNode():left(nullptr), right(nullptr), data(0) {}

BinaryTree::BinaryTreeImplementation::TreeNode::TreeNode(Data data):left(nullptr), right(nullptr), data(data) {}

BinaryTree::BinaryTreeImplementation::TreeNode::TreeNode(TreeNode &&other):left(nullptr), right(nullptr), data(other.data)
{
    std::swap(left, other.left);
    std::swap(right, other.right);
}

BinaryTree::BinaryTreeImplementation::TreeNode::~TreeNode()
{
    left = nullptr;
    right = nullptr;
}

BinaryTree::BinaryTreeImplementation::TreeNode & BinaryTree::BinaryTreeImplementation::TreeNode::operator = (BinaryTree::BinaryTreeImplementation::TreeNode && other)
{
    left = nullptr;
    right = nullptr;
    std::swap(left, other.left);
    std::swap(right, other.right);

    data = other.data;
    data = 0;
    return * this;
}

void BinaryTree::BinaryTreeImplementation::TreeNode::push(Data data)
{
    if(data < this->data)
    {
        if(left == nullptr)
        {
            left = new TreeNode(data);
        }
        else
        {
            left->push(data);
        }
    }
    else if(data >= this->data)
    {
        if(right == nullptr)
        {
            right = new TreeNode(data);
        }
        else
        {
            right->push(data);
        }
    }
}

/**
 *
 * BinaryTreeImplementation implementation
*/
BinaryTree::BinaryTreeImplementation::BinaryTreeImplementation():root(nullptr) {}

BinaryTree::BinaryTreeImplementation::BinaryTreeImplementation(std::initializer_list<int> list):root(nullptr)
{
    for(unsigned i = 0; i < list.size(); ++i)
    {
        push(*(list.begin() + i));
    }
}

BinaryTree::BinaryTreeImplementation::BinaryTreeImplementation(const BinaryTreeImplementation &other):root(nullptr)
{
    copy(root, other.root);
}

BinaryTree::BinaryTreeImplementation::BinaryTreeImplementation(BinaryTreeImplementation &&other):root(nullptr)
{
    swap(root, other.root);
}

BinaryTree::BinaryTreeImplementation::~BinaryTreeImplementation()
{
    clear();
}

BinaryTree::BinaryTreeImplementation & BinaryTree::BinaryTreeImplementation::operator = (const BinaryTree::BinaryTreeImplementation & other)
{
    if(this != &other)
    {
        copy(root, other.root);
    }
    return * this;
}

BinaryTree::BinaryTreeImplementation & BinaryTree::BinaryTreeImplementation::operator = (BinaryTree::BinaryTreeImplementation && other)
{
    swap(root, other.root);
    return * this;
}

void BinaryTree::BinaryTreeImplementation::swap(TreeNode *&rvalue, TreeNode *lvalue)
{
    if(lvalue == nullptr)
    {
        rvalue = lvalue;
    }
    else
    {
        std::swap(rvalue, lvalue);
        swap(rvalue->left, lvalue->left);
        swap(rvalue->right, lvalue->right);
    }
}

void BinaryTree::BinaryTreeImplementation::clear()
{
    clear(root);
}

void BinaryTree::BinaryTreeImplementation::clear(TreeNode *&root)
{
    if(root != nullptr)
    {
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

void BinaryTree::BinaryTreeImplementation::copy(TreeNode *&copiedNode, TreeNode *otherNode)
{
    if(otherNode == nullptr)
    {
        copiedNode = otherNode;
    }
    else
    {
        copiedNode = new TreeNode(otherNode->data);
        copy(copiedNode->left, otherNode->left);
        copy(copiedNode->right, otherNode->right);
    }
}

BinaryTree::BinaryTreeImplementation::TreeNode * BinaryTree::BinaryTreeImplementation::rightMost(TreeNode *node) const
{
    if(node != nullptr && node->right != nullptr)
    {
        return rightMost(node->right);
    }
    return node;
}

BinaryTree::BinaryTreeImplementation::TreeNode * BinaryTree::BinaryTreeImplementation::findMin(TreeNode *node) const
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else if(node->left == nullptr)
    {
        return node;
    }
    return findMin(node->left);
}

void BinaryTree::BinaryTreeImplementation::push(Data data)
{
    if(root == nullptr)
    {
        root = new TreeNode(data);
    }
    else
    {
        root->push(data);
    }
}

void BinaryTree::BinaryTreeImplementation::remove(Data data)
{
    bool found = false;
    if(isEmpty())
    {
        return;
    }
    TreeNode * curr;
    TreeNode * parent;
    curr = root;

    while(curr != nullptr)
    {
        if(curr->data == data)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if(data > curr->data)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
    }
    if(!found)
    {
        throw BSTException();
    }

    if((curr->left == nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr))
    {
        if(curr->left == nullptr && curr->right != nullptr)
        {
            if(parent->left == curr)
            {
                parent->left = curr->right;
            }
            else
            {
                parent->right = curr->right;
            }
        }
        else
        {
            if(parent->left == curr)
            {
                parent->left = curr->left;
            }
            else
            {
                parent->right = curr->left;
            }
        }
        delete curr;
        return;
    }

    if(curr->left == nullptr && curr->right == nullptr)
    {
        if(parent->left == curr)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
        delete curr;
        return;
    }

    if(curr->left != nullptr && curr->right != nullptr)
    {
        TreeNode * ncurr;
        ncurr = curr->right;
        if((ncurr->left == nullptr) && (ncurr->right == nullptr))
        {
            curr = ncurr;
            delete ncurr;
            curr->right = nullptr;
        }
        else
        {
            if((curr->right)->left != nullptr)
            {
                TreeNode * lcurr;
                TreeNode * lcurrp;
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while(lcurr->left != nullptr)
                {
                    lcurrp = lcurr;
                    lcurr = lcurr->left;
                }
                curr->data = lcurr->data;
                delete lcurr;
                lcurrp->left = nullptr;
            }
            else
            {
                TreeNode * tmp;
                tmp = curr->right;
                curr->data = tmp->data;
                curr->right = tmp->right;
                delete tmp;
            }
        }
        return;
    }
}

bool BinaryTree::BinaryTreeImplementation::isEmpty() const
{
    return root == nullptr ? true : false;
}

void BinaryTree::BinaryTreeImplementation::inorder(TreeNode *node, TreeNode *rightMost, std::ostream &out)
{
    if(node == nullptr)
    {
        return;
    }
    else if(node->left)
    {
        inorder(node->left, rightMost, out);
    }
    out << node->data;
    if(node != rightMost)
    {
        out << ", ";
    }
    if(node->right)
    {
        inorder(node->right, rightMost, out);
    }
}

/**
 *
 * BinaryTree itself implementation
*/
BinaryTree::BinaryTree():pimpl(nullptr)
{
    pimpl = new BinaryTreeImplementation;
}

BinaryTree::BinaryTree(std::initializer_list<int> list):pimpl(nullptr)
{
    pimpl = new BinaryTreeImplementation(list);
}

BinaryTree::BinaryTree(const BinaryTree &other):pimpl(nullptr)
{
    pimpl = new BinaryTreeImplementation(*other.pimpl);
}

BinaryTree::BinaryTree(BinaryTree &&other):pimpl(nullptr)
{
    pimpl = std::move(other.pimpl);
}

BinaryTree::~BinaryTree()
{
    clear();
}

BinaryTree & BinaryTree::operator = (const BinaryTree & other)
{
    *pimpl = *other.pimpl;
    return * this;
}

BinaryTree & BinaryTree::operator = (BinaryTree && other)
{
    pimpl = std::move(other.pimpl);
    return * this;
}

void BinaryTree::clear()
{
    pimpl->clear();
}

void BinaryTree::push(Data data)
{
    pimpl->push(data);
}

void BinaryTree::remove(Data data)
{
    pimpl->remove(data);
}

bool BinaryTree::isEmpty() const
{
    return pimpl->isEmpty();
}

std::ostream & operator << (std::ostream & out, const BinaryTree & other)
{
    out << *other.pimpl;
    return out;
}

std::istream & operator >> (std::istream & in, const BinaryTree & other)
{
    in >> *other.pimpl;
    return in;
}
