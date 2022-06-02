#include "DTable.h"
using namespace std;

#include<iostream>
#include<string>
#include<fstream>

#include<random>
#include<ctime>
#include<chrono>

int __rand(){
    default_random_engine engine(time(0));
    uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
    return u(engine);
}

void insertTimeTest(ofstream& csvStream, size_t times){
    DTable<DTable<int>> tables;
    for(int i = 0; i < 5; i++){
        DTable<int> table;
        table.setFactor((float)((2*i+1.0)/10));
        tables.push_back(table);
    }

    for(int index = 0; index < tables.size(); index++){
        auto startTime1 = chrono::high_resolution_clock::now();
        for(int i = 0; i < times; i++){
            tables[index].push_back(__rand());
        }
        auto endTime1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
        csvStream<<fixed<<diffTime1.count()<<",";
    }
}

void popTimeTest(ofstream& csvStream, size_t times){
    DTable<DTable<int>> tables;
    for(int i = 0; i < 5; i++){
        DTable<int> table;
        
        table.setFactor((2*i+1.0)/10);
        tables.push_back(table);
    }

    for(int index = 0; index < tables.size(); index++){
        for(int i = 0; i < times; i++){
            tables[index].push_back(__rand());
        }
        auto startTime1 = chrono::high_resolution_clock::now();
        for(int i = 0; i < times; i++){
            tables[index].pop_back();
        }
        auto endTime1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
        csvStream<<fixed<<diffTime1.count()<<",";
    }
}

void memoryTest(ofstream& csvStream, size_t times){
    DTable<size_t> memories;
    DTable<DTable<int>> tables;
    for(int i = 0; i < 5; i++){
        DTable<int> table;
        table.setFactor((2*i+1.0)/10);
        tables.push_back(table);
    }

    for(int index = 0; index < tables.size(); index++){
        for(int i = 0; i < times; i++){
            tables[index].push_back(__rand());
        }

        for(int i = 0; i < (times/5)*4; i++){
            tables[index].pop_back();
        }
        
        memories.push_back(tables[index].capacity());
    }
    
    for(int i = 0; i < tables.size() - 1; i++){
        csvStream<<memories[i]<<",";
    }
    csvStream<<memories[tables.size()-1]<<endl;
}

int main(){
    const size_t testTimes = 100000;
    ofstream csv;
    csv.open("test2.csv", ios::out|ios::trunc);
    for(int i = 0; i < 15; i++){
        csv<<i<<",";
    }

    csv<<15<<endl;
    for(int i = 0; i < testTimes; i+= 1000){
        cout<<"testing..."<<i<<endl;
        insertTimeTest(csv, i);
        popTimeTest(csv, i);
        memoryTest(csv, i);
    }
    csv.close();


}