#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<stdio.h>
#include<time.h>
#define OJ false
using namespace std;

class Array{
private:
    vector<int> array;
    int size;
    bool isRandom;

public:
    Array(int newSize);
    void generateArray(int newSize);
    void setRandom(bool set);
    int getSize();

    void shuffle();

    int Partition(int low, int high);
    int RandomPivotPartition(int low, int high);
    void quickSort(int p, int q);

    void printArray();
};