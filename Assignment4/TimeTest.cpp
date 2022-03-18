#include "QuickSort.h"
#include<fstream>
#include<chrono>

using namespace std;

void test_sort(int number, ofstream& stream){
    srand((int)time(NULL));
    Array testArray(number);
    testArray.setRandom(true);

    auto startTime1 = chrono::high_resolution_clock::now();
    testArray.setRandom(false);
    testArray.quickSort(0, number - 1);
    auto endTime1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;

    auto startTime2 = chrono::high_resolution_clock::now();
    testArray.setRandom(false);
    testArray.quickSort(0, number - 1);
    auto endTime2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime2= endTime2 - startTime2;

    stream<<fixed<<number<<","<<diffTime1.count()<<","<<diffTime2.count()<<endl;
}

int main(){
    const int NUMBER = 100000;

    ofstream csvStream;
    csvStream.open("timeData1.csv", ios::out|ios::trunc);
    csvStream<<"size"<<","<<"sortTime1"<<","<<"sortTime2"<<endl;
    for(int i = 0; i <= NUMBER; i += 1000){
        cout<<"Sorting size: "<<i<<endl;
        test_sort(i, csvStream);
    }
    csvStream.close();
}
