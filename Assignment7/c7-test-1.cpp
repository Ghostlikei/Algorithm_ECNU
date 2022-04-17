//
// Created by wyz on 13/04/2022.
//
#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

typedef int DataType;

class TreeNode;

class BST;

void deleteNode(TreeNode *node);

class TreeNode
{
public:
    DataType key;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(DataType key)
    {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    ~TreeNode()
    {
        deleteNode(this);
    }
};

class BST
{
public:
    TreeNode *root;

    BST(TreeNode *root)
    {
        this->root = root;
    }

    ~BST()
    {
        deleteNode(root);
    }
};

void deleteNode(TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->left != nullptr)
    {
        deleteNode(node->left);
    }

    if (node->right != nullptr)
    {
        deleteNode(node->right);
    }

    delete node;
}

/**
 * 根据一个字符串构建二叉树
 * @param 1,null,2,3
 * @return
 */
BST *stringToBinaryTree(string input)
{

    if (input.empty())
    {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    // 数据保证起码有一个元素，先要取出一个来做跟节点
    getline(ss, item, ',');

    queue<TreeNode *> q;
    TreeNode *root = nullptr;

    if (item != "null")
    {
        root = new TreeNode(stoi(item));
        q.push(root);
    }
    else
    {
        return nullptr;
    }

    while (1)
    {
        TreeNode *head = q.front();

        // 尝试去拿左边的
        if (!getline(ss, item, ','))
        {
            break;
        }

        if (item != "null")
        {
            TreeNode *tmp = new TreeNode(stoi(item));
            head->left = tmp;
            tmp->parent = head;
            q.push(tmp);
        }

        // 尝试去拿右边的
        if (!getline(ss, item, ','))
        {
            break;
        }

        if (item != "null")
        {
            TreeNode *tmp = new TreeNode(stoi(item));
            head->right = tmp;
            tmp->parent = head;
            q.push(tmp);
        }

        q.pop();
    }
    return new BST(root);
}

/**
 * 请实现先序遍历，直接将结果打印即可，无需返回
 * @return
 */
void preOrder(TreeNode *node)
{
    if (node == nullptr) return;
    cout<<node->key<<" ";
    preOrder(node->left);
    preOrder(node->right);
}

/**
 * 请实现搜索关键字
 * @return
 */
void search(TreeNode *node, DataType data)
{
    TreeNode* searchNode = node;

    while(searchNode){
        if (searchNode->key > data) searchNode = searchNode->left;
        else if (searchNode->key < data) searchNode = searchNode->right;
        else{
            cout<<"yes"<<endl;
            return;
        }
                        
    }

    cout<<"no"<<endl;
}

/**
 * 请实现查询最小关键字
 * @return
 */
void min(TreeNode *node)
{
    TreeNode* searchNode = node;
    while(searchNode->left) searchNode = searchNode->left;
    cout<<searchNode->key<<endl;
}

/**
 * 请实现查询最大关键字
 * @return
 */
void max(TreeNode *node)
{
    TreeNode* searchNode = node;
    while(searchNode->right) searchNode = searchNode->right;
    cout<<searchNode->key<<endl;
}

/**
 * 请实现查询前驱
 */
void pre(TreeNode *node, DataType num)
{
    TreeNode* searchNode = node;

    while(searchNode){
        if (searchNode->key > num) searchNode = searchNode->left;
        else if (searchNode->key < num) searchNode = searchNode->right;
        else break;            
    }

    if (searchNode->left != nullptr){
        searchNode = searchNode->left;
        while(searchNode->right) searchNode = searchNode->right;
        cout<<searchNode->key<<endl;
        return;
    }

    else{
        if (searchNode->parent && searchNode->parent->right && searchNode->parent->right->key == num){
            cout<<searchNode->parent->key<<endl;
            return;
        }
        else{
            while(searchNode->parent){
                if(searchNode->parent->right == nullptr) searchNode = searchNode->parent;
                else if(searchNode->parent->right->key != searchNode->key) searchNode = searchNode->parent;
                else {
                    searchNode = searchNode->parent;
                    break;
                }
            }
            cout<<searchNode->key<<endl;
        }
    }

}

/**
 * 请实现查询后驱
 */
void suc(TreeNode *node, DataType num)
{
    TreeNode* searchNode = node;

        while(searchNode){
            if (searchNode->key > num) searchNode = searchNode->left;
            else if (searchNode->key < num) searchNode = searchNode->right;
            else break;            
        }

    if (searchNode->right != nullptr){
        searchNode = searchNode->right;
        while(searchNode->left) searchNode = searchNode->left;
        cout<<searchNode->key<<endl;
        return;
    }

    else{
        if (searchNode->parent && searchNode->parent->left && searchNode->parent->left->key == num){
            cout<<searchNode->parent->key<<endl;
            return;
        }
        else{
            while(searchNode->parent){
                if(searchNode->parent->left == nullptr) searchNode = searchNode->parent;
                else if(searchNode->parent->left->key != searchNode->key) searchNode = searchNode->parent;
                else {
                    searchNode = searchNode->parent;
                    break;
                }
            }
            cout<<searchNode->key<<endl;
        }
    }
}

int main()
{
    string line;
    getline(cin, line);
    BST *bst = stringToBinaryTree(line);

    preOrder(bst->root);
    cout<<endl;// modified
    min(bst->root);
    max(bst->root);

    int n;
    int num;
    
    cin >> n;
    while (n--)
    {
        cin >> num;
        search(bst->root, num);
    }
    
    cin >> n;
    while (n--)
    {
        cin >> num;
        pre(bst->root, num);
        suc(bst->root, num);
    }

    return 0;
}
// 1,null,2,3
