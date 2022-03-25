#include<iostream>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include<time.h>
#define OJ false
using namespace std;

namespace CountingSort{
class Array{
private:        
    vector<int> array;
    int size;
    int max;
    int count[100010];

public:
    Array(int newSize, int maxNumber);
    void generateArray(int maxNum);
    int getSize();
    void input();
    void counting();
    void sort();

    void printArray();
};
}