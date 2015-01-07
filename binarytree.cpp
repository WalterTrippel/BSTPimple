#include "binarytree.h"

class BinaryTree::Implementation
{
public:
    Implementation();
    Implementation(std::initializer_list<int> list);
    Implementation(const Implementation & other);
    Implementation(Implementation && other);
    ~Implementation();

    Implementation & operator = (const Implementation & other);
    Implementation & operator = (Implementation && other);

    void clear();
    void push(Data data);
    void remove(Data data);
    bool isEmpty() const;

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
BinaryTree::Implementation::TreeNode::TreeNode():left(nullptr), right(nullptr), data(0) {}

BinaryTree::Implementation::TreeNode::TreeNode(Data data):left(nullptr), right(nullptr), data(data) {}

BinaryTree::Implementation::TreeNode::TreeNode(TreeNode &&other):left(nullptr), right(nullptr), data(other.data)
{
    std::swap(left, other.left);
    std::swap(right, other.right);
}

BinaryTree::Implementation::TreeNode::~TreeNode()
{
    left = nullptr;
    right = nullptr;
}

BinaryTree::Implementation::TreeNode & BinaryTree::Implementation::TreeNode::operator = (BinaryTree::Implementation::TreeNode && other)
{
    left = nullptr;
    right = nullptr;
    std::swap(left, other.left);
    std::swap(right, other.right);

    data = other.data;
    data = 0;
    return * this;
}

void BinaryTree::Implementation::TreeNode::push(Data data)
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
BinaryTree::Implementation::Implementation():root(nullptr) {}

BinaryTree::Implementation::Implementation(std::initializer_list<int> list):root(nullptr)
{
    for(unsigned i = 0; i < list.size(); ++i)
    {
        push(*(list.begin() + i));
    }
}

BinaryTree::Implementation::Implementation(const Implementation &other):root(nullptr)
{
    copy(root, other.root);
}

BinaryTree::Implementation::Implementation(Implementation &&other):root(nullptr)
{
    swap(root, other.root);
}

BinaryTree::Implementation::~Implementation()
{
    clear();
}

BinaryTree::Implementation & BinaryTree::Implementation::operator = (const BinaryTree::Implementation & other)
{
    if(this != &other)
    {
        copy(root, other.root);
    }
    return * this;
}

BinaryTree::Implementation & BinaryTree::Implementation::operator = (BinaryTree::Implementation && other)
{
    swap(root, other.root);
    return * this;
}

void BinaryTree::Implementation::swap(TreeNode *&rvalue, TreeNode *lvalue)
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

void BinaryTree::Implementation::clear()
{
    clear(root);
}

void BinaryTree::Implementation::clear(TreeNode *&root)
{
    if(root != nullptr)
    {
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

void BinaryTree::Implementation::copy(TreeNode *&copiedNode, TreeNode *otherNode)
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

BinaryTree::Implementation::TreeNode * BinaryTree::Implementation::rightMost(TreeNode *node) const
{
    if(node != nullptr && node->right != nullptr)
    {
        return rightMost(node->right);
    }
    return node;
}

BinaryTree::Implementation::TreeNode * BinaryTree::Implementation::findMin(TreeNode *node) const
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

void BinaryTree::Implementation::push(Data data)
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

void BinaryTree::Implementation::remove(Data data)
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

bool BinaryTree::Implementation::isEmpty() const
{
    return root == nullptr;
}

void BinaryTree::Implementation::inorder(TreeNode *node, TreeNode *rightMost, std::ostream &out)
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
    pimpl = new Implementation;
}

BinaryTree::BinaryTree(std::initializer_list<int> list):pimpl(nullptr)
{
    pimpl = new Implementation(list);
}

BinaryTree::BinaryTree(const BinaryTree &other):pimpl(nullptr)
{
    pimpl = new Implementation(*other.pimpl);
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

void BinaryTree::inorder(std::ostream &out)
{
    pimpl->inorder(pimpl->root, pimpl->rightMost(pimpl->root), out);
}

