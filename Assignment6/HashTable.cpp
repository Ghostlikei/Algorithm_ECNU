#include<iostream>
#include<list>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<chrono>
#include<fstream>

using namespace std;

template<typename Value>
class HashTable{
private:

    int divitor;
    int capacity;
    int size;
    vector<list<Value>> table;
    // Hash function can be overloaded
    int Hash(Value val){
        return val % divitor > 0 ? val % divitor : -val % divitor;
    }
    
    
public:
    HashTable<Value>(int div, int tableSize){
        list<Value> alist;
        for(int i = 0; i < tableSize; i++){
            table.push_back(alist);
        }
        divitor = div;
        capacity = tableSize;
        size = 0;
    }

    void put(const Value& val){
        int index = Hash(val);
        table[index].emplace_back(val);
    }

    bool find(const Value& element){
        int index = Hash(element);
        auto iter = table[index].begin();
        while(iter != table[index].end()){
            if(*iter == element) return true;
            iter++;
        } 
        return false;
    }

    void generateData(int number){
        srand((long)time(NULL));
        for(int i = 0; i < number; i++){
            long temp = rand() % 1000000;
            put(temp);
            size++;
        }
    }

    void timeTest(int queryNumber, ofstream& stream){
        auto startTime1 = chrono::high_resolution_clock::now();
        srand((long)time(NULL));
        for(int i = 0; i < queryNumber; i++){
            bool result = find(rand() % 1000000);
        }
        auto endTime1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;

        stream<<fixed<<queryNumber<<","<<diffTime1.count()<<endl;
    }

    int getSize(){return size;}
};

int main(){
    const int NUMBER = 100000;

    // HashTable<long> table(1333, 1334);
    ofstream csvStream;
    csvStream.open("timeData1.csv", ios::out|ios::trunc);
    csvStream<<"queryNumber"<<","<<"Time"<<endl;
    for(int i = 0; i <= NUMBER; i += 100){
        cout<<"Testing size: "<<i<<endl;
        HashTable<long> table(1333, 1334);
        table.generateData(i);
        table.timeTest(i, csvStream);
    }
    csvStream.close();
    
}