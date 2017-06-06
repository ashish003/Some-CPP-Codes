#include <iostream>
#include <cstdio>

using namespace std;

class AVLTree;

class TreeNode
{
    friend class AVLTree;
    int key;
    int height;
    TreeNode *left1;
    TreeNode *right1;
    TreeNode(int val);
};

class AVLTree
{
    TreeNode *root;

    TreeNode* insertUtility(TreeNode*, int);
    TreeNode* deleteUtility(TreeNode*, int);
    void searchUtility(TreeNode*, int);
    void preOrderUtility(TreeNode*);
    void postOrderUtility(TreeNode*);
    void inOrderUtility(TreeNode*);
    TreeNode* leftRotate(TreeNode*);
    TreeNode* rightRotate(TreeNode*);
    int getMinValue(TreeNode*);
    int height(TreeNode*);
    int getBalance(TreeNode*);
    void myDelete(TreeNode*);

    public:
    AVLTree();
    ~AVLTree();
    void insert1();
    void delete1();
    void search1();
    void preOrder();
    void postOrder();
    void inOrder();
};

TreeNode::TreeNode(int val)
{
    key=val;
    height=1;
    left1=NULL;
    right1=NULL;
}

AVLTree::AVLTree()
{
    root=NULL;
}

int max1(int a, int b)
{
    if(a>b)
    return a;

    return b;
}

void AVLTree::myDelete(TreeNode* node)
{
    if(node==NULL)
    return;

    TreeNode* left1=node->left1;
    TreeNode* right1=node->right1;
    myDelete(left1);
    myDelete(right1);
    delete node;
}

AVLTree::~AVLTree()
{
    myDelete(root);
}

int AVLTree::height(TreeNode *node)
{
    if(node==NULL)
    return 0;

    return node->height;
}

int AVLTree::getBalance(TreeNode *node)
{
    if(node==NULL)
    return 0;

    return (height(node->left1)-height(node->right1));
}

TreeNode* AVLTree::leftRotate(TreeNode* node)
{
    TreeNode* temp=node->right1;
    TreeNode* t1=temp->left1;

    temp->left1=node;
    node->right1=t1;

    node->height=1+max1(height(node->left1), height(node->right1));
    temp->height=1+max1(height(temp->left1), height(temp->right1));

    return temp;
}

TreeNode* AVLTree::rightRotate(TreeNode* node)
{
    TreeNode* temp=node->left1;
    TreeNode* t1=temp->right1;

    temp->right1=node;
    node->left1=t1;

    node->height=1+max1(height(node->left1), height(node->right1));
    temp->height=1+max1(height(temp->left1), height(temp->right1));

    return temp;
}

TreeNode* AVLTree::insertUtility(TreeNode* node, int data)
{
    if(node==NULL)
    {
        TreeNode *temp=NULL;
        temp=new TreeNode(data);
        return temp;
    }

    if(data < node->key)
    {
        node->left1=insertUtility(node->left1, data);
    }
    else if(data > node->key)
    {
        node->right1=insertUtility(node->right1, data);
    }
    else
    {
        return node;
    }

    node->height=1+max1(height(node->left1), height(node->right1));

    int balance=getBalance(node);

    if(balance>1 && data < node->left1->key)
    return rightRotate(node);

    if(balance < -1 && data > node->right1->key)
    return leftRotate(node);

    if(balance>1 && data > node->left1->key)
    {
        node->left1=leftRotate(node->left1);
        return rightRotate(node);
    }

    if(balance < -1 && data < node->right1->key)
    {
        node->right1=rightRotate(node->right1);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert1()
{
    int data;
    cout<<"Enter the key to be inserted in AVL tree:\n";
    cin>>data;

    root=insertUtility(root, data);
}

int AVLTree::getMinValue(TreeNode* node)
{
    TreeNode *current=node;
    while(current->left1!=NULL)
        current=current->left1;

    return current->key;
}

TreeNode* AVLTree::deleteUtility(TreeNode* node, int data)
{
    if(node==NULL)
    return node;

    if(node->key > data)
    node->left1=deleteUtility(node->left1, data);
    else if(node->key < data)
    node->right1=deleteUtility(node->right1, data);
    else
    {
        if(node->left1==NULL && node->right1==NULL)
        {
            TreeNode* temp=node;
            node=NULL;
            delete temp;
        }
        else if(node->left1==NULL)
        {
            TreeNode* temp=node;
            node=node->right1;
            delete temp;
        }
        else if(node->right1==NULL)
        {
            TreeNode* temp=node;
            node=node->left1;
            delete temp;
        }
        else
        {
            int min1=getMinValue(node->right1);
            node->key=min1;
            node->right1=deleteUtility(node->right1, min1);
        }
    }

    if(node==NULL)
    return node;

    node->height=1+max1(height(node->left1), height(node->right1));

    int balance=getBalance(node);

    if(balance>1 && getBalance(node->left1)>=0)
    return rightRotate(node);

    if(balance < -1 && getBalance(node->right1)<=0)
    return leftRotate(node);

    if(balance>1 && getBalance(node->left1)<0)
    {
        node->left1=leftRotate(node->left1);
        return rightRotate(node);
    }

    if(balance < -1 && getBalance(node->right1)>0)
    {
        node->right1=rightRotate(node->right1);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::delete1()
{
    int data;
    cout<<"Enter the key to be inserted in AVL tree:\n";
    cin>>data;

    root=deleteUtility(root, data);
}

void AVLTree::searchUtility(TreeNode* node, int data)
{
    if(node==NULL)
    {
        cout<<data<<" is not present in AVL tree\n";
        return;
    }

    if(node->key > data)
    {
        searchUtility(node->left1, data);
    }
    else if(node->key < data)
    {
        searchUtility(node->right1, data);
    }
    else
    {
        cout<<data<<" is present in AVL tree\n";
    }

}

void AVLTree::search1()
{
    int data;
    cout<<"Enter data to be searched in AVL tree:\n";
    cin>>data;

    searchUtility(root, data);
}

void AVLTree::preOrderUtility(TreeNode* node)
{
    if(node)
    {
        cout<<node->key<<" ";
        preOrderUtility(node->left1);
        preOrderUtility(node->right1);
    }
}

void AVLTree::preOrder()
{
    preOrderUtility(root);
}

void AVLTree::postOrderUtility(TreeNode* node)
{
    if(node)
    {
        postOrderUtility(node->left1);
        postOrderUtility(node->right1);
        cout<<node->key<<" ";
    }
}

void AVLTree::postOrder()
{
    postOrderUtility(root);
}

void AVLTree::inOrderUtility(TreeNode* node)
{
    if(node)
    {
        inOrderUtility(node->left1);
        cout<<node->key<<" ";
        inOrderUtility(node->right1);
    }
}

void AVLTree::inOrder()
{
    inOrderUtility(root);
}

int main()
{
    AVLTree* myTree=NULL;
    myTree=new AVLTree;
    int input;

    do
    {
        cout<<"\nEnter the operation want to be done:\n";
        cout<<"1. Insert\n2. Delete\n3. Search\n4. Print Inorder\n5. Print Preorder\n6. Print Postorder\n7. Exit\n";
        cin>>input;

        switch(input)
        {
            case 1:
                myTree->insert1();
                break;
            case 2:
                myTree->delete1();
                break;
            case 3:
                myTree->search1();
                break;
            case 4:
                myTree->inOrder();
                break;
            case 5:
                myTree->preOrder();
                break;
            case 6:
                myTree->postOrder();
                break;
            case 7:
                break;
            default:
                cout<<"Invalid selection";
        }
    }while(input!=7);

    return 0;
}
