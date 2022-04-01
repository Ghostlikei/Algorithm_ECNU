#include<iostream>
#include<list>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<chrono>
#include<fstream>
#include<map>
#include<cstdlib>

using namespace std;

template<typename Value>
class HashTable{
private:

    int divitor;
    int capacity;
    int size;
    int x;
    vector<pair<Value, bool>> table;
    // Hash function can be overloaded
    int Hash(Value val){
        return val % divitor > 0 ? val % divitor : -val % divitor;
    }
    int pow(int num, int index){
        int result = 1;
        for(int i = 0; i < index; i++){
            result *= num;
        }
        return result;
    }
    
    
public:
    HashTable<Value>(int div, int tableSize, int Index){
        for(int i = 0; i < tableSize; i++){
            pair<Value, bool> origin(0, false);
            table.push_back(origin);
        }
        divitor = div;
        capacity = tableSize;
        size = 0;
        x = Index;
    }

    void put(const Value& val){
        int index = Hash(val);
        int cnt = 0;
        while(cnt < capacity && table[(index + pow(cnt,x)) % (capacity - 1)].second == true){
            cnt++;
        }

        
        table[(index + pow(cnt,x)) % (capacity - 1)].first = val;
        table[(index + pow(cnt,x)) % (capacity - 1)].second = true;        
    }

    bool find(const Value& element){
        int index = Hash(element);
        int cnt = 0;
        while(cnt < capacity){
            if(table[(index + pow(cnt,x)) % (capacity - 1)].first == element) return true;
            cnt++;
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

        if(x == 1) stream<<fixed<<queryNumber<<","<<diffTime1.count()<<",";
        else if(x == 2) stream<<fixed<<diffTime1.count()<<endl;
    }

    int getSize(){return size;}
};

int main(){
    const int NUMBER = 30000;

    // HashTable<long> table(1333, 1334);
    ofstream csvStream;
    csvStream.open("timeData0.csv", ios::out|ios::trunc);
    csvStream<<"queryNumber"<<","<<"LinearProbe"<<","<<"QuadraticProbe"<<endl;
    for(int i = 0; i <= NUMBER; i += 100){
        if(i==0) continue;
        cout<<"Testing size: "<<i<<endl;

        HashTable<long> table1(i-1, i, 1);
        table1.generateData(i);
        table1.timeTest(i, csvStream);

        HashTable<long> table2(i-1, i, 2);
        table2.generateData(i);
        table2.timeTest(i, csvStream);
    }
    csvStream.close();
    
}