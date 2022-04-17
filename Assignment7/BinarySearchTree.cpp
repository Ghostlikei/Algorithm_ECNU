#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<ctime>
#include<fstream>
#include<chrono>


using namespace std;

template<typename T>
struct Node{
    T __value;
    Node* __leftnode;
    Node* __rightnode;

    Node(T value): __value(value), __leftnode(nullptr), __rightnode(nullptr) {}
    Node(T value, Node& left, Node& right): __value(value), __leftnode(left), __rightnode(right) {}
    // Node& operator=(Node& rhs){
    //     __value = rhs.value;
    //     __leftnode = rhs.__leftnode;
    //     __rightnode = rhs.__rightnode;
    //     return *this;
    // }

    // int compareTo(Node& lhs, Node& rhs){
    //     if(lhs.val == rhs.val) return 0;
    //     int result = lhs.val < rhs.val ? -1 : 1;
    //     return result;
    // } 
};


template<typename T>
class BST{
private:
    typedef Node<T> BNode;
    BNode* root;
    vector<T> __IterableArray;
    void inOrder(BNode* node){
        if (node == nullptr) return;
        inOrder(node->__leftnode);
        __IterableArray.push_back(node->__value);
        inOrder(node->__rightnode);
    }


public:
    BST(){
        root = nullptr;
        __IterableArray = {};
    }

    BST& put(const T& value){
        BNode* searchNode = root;
        BNode* parent = nullptr;

        if(!searchNode){
            root = new BNode(value);
            return *this;
        }

        while(searchNode){
            parent = searchNode;
            if (searchNode->__value > value) searchNode = searchNode->__leftnode;
            else if (searchNode->__value < value) searchNode = searchNode->__rightnode;
            else return *this;            
        }

        searchNode = new BNode(value);
        if (parent->__value > value) parent->__leftnode = searchNode;
        else parent->__rightnode = searchNode;
        return *this;
    }

    bool find(const T& value){
        BNode* searchNode = root;

        while(searchNode){
            if (searchNode->__value > value) searchNode = searchNode->__leftnode;
            else if (searchNode->__value < value) searchNode = searchNode->__rightnode;
            else return true;            
        }

        return false;
    }

    BST& del(const T& value){
        BNode* searchNode = root;
        BNode* parent = nullptr;
        while(searchNode){
            if (searchNode->__value == value) break;
            parent = searchNode;
            if (searchNode->__value > value) searchNode = searchNode->__leftnode;
            else searchNode = searchNode->__rightnode;
        }

        if (searchNode == nullptr) return *this;

        if (searchNode->__leftnode == nullptr && searchNode->__rightnode == nullptr){
            if(searchNode == root) root = nullptr;
            else{
                if (parent->__rightnode == searchNode) parent->__leftnode = nullptr;
                else parent->__rightnode = nullptr;
            }
            delete searchNode;            
        }

        else if(searchNode->__leftnode == nullptr){
            if (searchNode == root) root = nullptr;
            else{
                if (parent->__leftnode == searchNode) parent->__leftnode = searchNode->__rightnode;
                else parent->__rightnode = searchNode->__rightnode;
            }
            delete searchNode;
        }

        else if(searchNode->__rightnode == nullptr){
            if (searchNode == root) root = nullptr;
            else{
                if (parent->__leftnode == searchNode) parent->__leftnode = searchNode->__leftnode;
                else parent->__rightnode = searchNode->__leftnode;
            }
            delete searchNode;
        }

        else
		{
			BNode *leftRightMost = searchNode->__leftnode;
			parent = searchNode;

			while (leftRightMost->__rightnode)
			{
				parent = leftRightMost;
				leftRightMost = leftRightMost->__rightnode;
			}

			swap(searchNode->__value, leftRightMost->__value);

			if (parent->__leftnode == leftRightMost) parent->__leftnode = leftRightMost->__leftnode;
			else parent->__rightnode = leftRightMost->__leftnode;

			delete leftRightMost;
		}

        return *this;

    }

    vector<T> IterableArray(){
        inOrder(root);
        return __IterableArray;
    }

    void testInput(const size_t size, ofstream& csvstream){
        default_random_engine engine(time(0));
        uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
        auto startTime1 = chrono::high_resolution_clock::now();
        for(int i = 0; i < size; i++){
            int temp = u(engine);
        }
        auto endTime1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
        csvstream<<fixed<<diffTime1.count();
    }

    void testQuery(ofstream& csvstream){
        auto startTime2 = chrono::high_resolution_clock::now();
        default_random_engine engine(time(0));
        uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
        for(int i = 0; i < 100; i++){
            int temp = u(engine);
            bool result = find(temp);
        }    
        auto endTime2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diffTime2 = endTime2 - startTime2;
        csvstream<<fixed<<","<<diffTime2.count()<<endl;
    }
};



int main(){
    const int NUMBER = 1000000;
    ofstream csvStream;
    csvStream.open("Data.csv", ios::out|ios::trunc);
    csvStream<<"queryNumber"<<","<<"InsertTime"<<","<<"QueryTime"<<endl;
    for(int i = 0; i <= NUMBER; i += 100){
        cout<<"Testing size: "<<i<<endl;
        csvStream<<i<<",";
        BST<int> testBST;
        testBST.testInput(i, csvStream);
        testBST.testQuery(csvStream);        
    }
    csvStream.close();
}

