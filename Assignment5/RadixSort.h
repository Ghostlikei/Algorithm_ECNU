#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#define OJ false
using namespace std;

namespace RadixSort{
class Array{
private:
    int size;
    int radix = 0;
    vector<int> array;
    const long digits[9]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

public:
    Array(int newSize, int maxSize);
    int getSize();

    void input();
    void generateArray(int maxSize);

    void radixSort();
    void printArray();

};

}