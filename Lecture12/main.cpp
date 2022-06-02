#include "UnionFind.h"
#include "WQUnionFind.h"

#include<iostream>
#include<string>
#include<fstream>

#include<random>
#include<ctime>
#include<chrono>

int __rand(size_t division){
    default_random_engine engine(time(0));
    uniform_int_distribution<int> u(0, INT32_MAX);
    return (u(engine) % division) + 1;
}

void WQUFtest(ofstream& csv, size_t times){
    auto startTime1 = chrono::high_resolution_clock::now();

    WQUnionFind wquf(times);
    for(int i = 0; i < times; i++){
        size_t left = __rand(times);
        size_t right = __rand(times);
        wquf.set_union(left, right); 
    }

    const size_t testConnect = times > 1000 ? 1000 : times;
    for(int i = 0; i < times; i++){
        size_t left = __rand(times);
        size_t right = __rand(times);
        bool result = wquf.connected(left, right);
    }


    auto endTime1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
    csv<<fixed<<diffTime1.count()<<",";
}

void UFtest(ofstream& csv, size_t times){
    auto startTime1 = chrono::high_resolution_clock::now();

    UnionFind uf(times);
    for(int i = 0; i < times; i++){
        size_t left = i+1;
        size_t right = i+2;
        uf.set_union(left, right); 
    }

    const size_t testConnect = times;
    for(int i = 0; i < times; i++){
        size_t left = __rand(times);
        size_t right = __rand(times);
        bool result = uf.connected(left, right);
    }


    auto endTime1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;
    csv<<fixed<<diffTime1.count()<<endl;
}

int main(){
    const size_t testTimes = 20000;
    ofstream csv;
    csv.open("time2.csv", ios::out|ios::trunc);

    csv<<"WQUF"<<","<<"UF"<<endl;

    for(int i = 0; i < testTimes; i+=100){
        cout<<"testing "<<i<<endl;
        WQUFtest(csv, i);
        UFtest(csv, i);
    }

    csv.close();
}