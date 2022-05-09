#include<vector>
#include<utility>
#include<iostream>
using namespace std;

namespace OptimalBST{


struct Node{
    int index;
    Node* left;
    Node* right;
    Node(int Index): index(Index), left(nullptr), right(nullptr){}
};



template<typename Key, typename Value>
class BST{
protected:
    vector<pair<Key, Value>> data;

private:
    size_t n;
    int* freq;
    size_t** root;
    double** w;
    double** e;
    Node* rNode;
    

    

public:
    // initialize BST
    BST(size_t size, vector<int>& p, vector<Key>& keys, vector<Value>& values){
        n = size;
        freq = new int[n+1];
        root = new size_t* [n+2];
        w = new double* [n+2];
        e = new double* [n+2];
        for (int i = 0;i < n + 2;i++){
            root[i] = new size_t[n + 1];
            w[i] = new double[n + 1];
            e[i] = new double[n + 1];
	    }

        for (int i = 0; i < n; i++){
            freq[i] = p[i];
        }
        
        saveData(keys, values);
        
        createBST();
        
        rNode = new Node(root[1][n]);
        build(rNode, 1, n);
    }

    ~BST(){
        delete[] freq;
        for (int i = 0;i < n + 2;i++){
            delete[] root[i];
            delete[] w[i];
            delete[] e[i];
	    }
        delete[] root;
        delete[] w;
        delete[] e;
    }

    void build(Node* rootNode, int i, int j){
        if (i < j){
            int r = root[i][j];
            if(root[i][r-1] > 0){
                Node* leftNode = new Node(root[i][r-1]);
                rootNode->left = leftNode;
                build(leftNode, i, r-1);
            }

            if(root[r+1][j] > 0){
                Node* rightNode = new Node(root[r+1][j]);
                rootNode->right = rightNode;
                build(rightNode, r+1, j);
            } 
	    }
    }

    void saveData(vector<Key>& keys, vector<Value>& values){
        for(int i = 0; i < keys.size(); i++){
            pair<Key, Value> temp(keys[i], values[i]);
            data.push_back(temp);
        }
    }

    void createBST(){
        double temp = 0; //这里的temp相当于取多个值的min操作
        

        for (int i = 1; i <= n + 1; i++) {
		    w[i][i - 1] = 0;
		    e[i][i - 1] = 0;
	    }

        int i = 0;// 起始点
        int j = 0;// 终止点
        int r = 0;// 根节点

        for(int len = 0; len < n; len++){
            for (i = 1; i <= n-len; i++){
                j = len + i;
                w[i][j] = w[i][j - 1] + freq[j];

                // 计算每一个节点是根节点的情况
                e[i][j] = e[i + 1][j];
                root[i][j] = i;

                for(r = i + 1; r <= j; r++){
                    temp = e[i][r-1] + e[r+1][j];
                    if (temp < e[i][j]){
                        e[i][j] = temp;
                        root[i][j] = r;
                    }
                }
                e[i][j] += w[i][j];
            }
        }
    }

    // 常规BST的搜索
    Value find(int index){
        if (index == 0) return data[0].second;
        Node* sNode = rNode;
        while(sNode){
            if (sNode->index > index) sNode = sNode->left;
            else if (sNode->index < index) sNode = sNode->right;
            else return data[index].second;
        }

        return 0;

    }

};

}