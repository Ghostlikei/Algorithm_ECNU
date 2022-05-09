#include "Array.h"
#include "BST.h"
#include "Hashtable.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#include<random>
#include<ctime>
#include<chrono>
using namespace std;

void test(){
    // test case
    vector<string> keys = {"a","b","c"};
    vector<string> values = {"aa","bb", "cc"};
    vector<int> p = {6, 3, 2};

    // samples of three APIs
    OptimalBST::BST<string, string> bst(keys.size(), p, keys, values);
    cout<<bst.find(0)<<endl;

    Array::array<string, string> myArray;
    for(int i = 0; i < keys.size(); i++){
        myArray.put(keys[i], values[i]);
    }
    cout<<myArray.find(0)<<endl;
    cout<<myArray.find(1)<<endl;

    Hashtable::HashTable<string, string> table(keys.size());
    for(int i = 0; i < keys.size(); i++){
        table.put(keys[i], values[i]);
    }
    cout<<table.find(keys[0])<<endl;
    cout<<table.find(keys[1])<<endl;
}

class TimeTest{
private:
    size_t size;
    vector<string> names;
    vector<string> infos;
    vector<int> freq;
    ofstream csvStream;
    
public:
    TimeTest(int n, string file){
        size = n;
        ifstream ifs(file);
        readInfo(ifs);        
        csvStream.open("time.csv", ios::out|ios::trunc);
        csvStream<<"queryNumber"<<","<<"OptimalBST"<<","<<"Array"<<","<<"HashTable"<<endl;
        
                
    }

    ~TimeTest(){
        csvStream.close();
    }

    void readInfo(ifstream& in){
        for(int i = 0; i < size; i++){
            string name;
            in>>name;
            names.push_back(name);

            string info;
            getline(in, info);
            istringstream record(info);
            infos.push_back(info);
        }

        freq = {6,5,5,4,4,4,3,3,3,3,2,2,2,2,1};

        in.close();
    }

    int __rand(){
        default_random_engine engine(time(0));
        uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
        return u(engine) % size;
    }

    void timetest(int times){
        OptimalBST::BST<string, string> testBST(size, freq, names, infos);

        Array::array<string, string> testArray;
        for(int i = 0; i < size; i++){
            testArray.put(names[i], infos[i]);
        }

        Hashtable::HashTable<string, string> testTable(size);
        for(int i = 0; i < size; i++){
            testTable.put(names[i], infos[i]);
        }
        
        for (int i = 0; i < times; i+=1000){
            csvStream<<i<<",";
            
            cout<<"Testing: "<<i<<endl;

            auto startTime1 = chrono::high_resolution_clock::now();
            for(int j = 0; j < i; j++){
                int index = __rand(); 
                string str = testBST.find(index);
            }    
            auto endTime1 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
            csvStream<<fixed<<diffTime1.count()<<",";

            auto startTime2 = chrono::high_resolution_clock::now();
            for(int j = 0; j < i; j++){
                int index = __rand(); 
                string str = testArray.find(index);
            }
            auto endTime2 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> diffTime2 = endTime2 - startTime2;
            csvStream<<fixed<<diffTime2.count()<<",";

            auto startTime3 = chrono::high_resolution_clock::now();
            for(int j = 0; j < i; j++){
                int index = __rand(); 
                string str = testTable.find(names[index]);
            }
            auto endTime3 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> diffTime3 = endTime3 - startTime3;
            csvStream<<fixed<<diffTime3.count()<<endl;
        }
    }




    
};

int main(){
    TimeTest test(16, "flower-info.txt");
    test.timetest(1000000);
}