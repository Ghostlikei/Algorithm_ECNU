#include "CountingSort.h"
#include "RadixSort.h"
#include<fstream>
#include<chrono>

using namespace std;

void test_sort(int number, int maxNum, ofstream& stream){
    CountingSort::Array testArray1(number, maxNum);
    RadixSort::Array testArray2(number, maxNum);

    auto startTime1 = chrono::high_resolution_clock::now();
    testArray1.counting();
    testArray1.sort();
    auto endTime1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime1 = endTime1 - startTime1;

    auto startTime2 = chrono::high_resolution_clock::now();
    testArray2.radixSort();
    auto endTime2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diffTime2= endTime2 - startTime2;

    stream<<fixed<<number<<","<<diffTime1.count()<<","<<diffTime2.count()<<endl;
    // stream<<fixed<<number<<","<<diffTime1.count()<<endl;
}

int main(){
    const long SIZE = 10000000;
    const int MAXNUM = 100000;

    ofstream csvStream;
    csvStream.open("timeData3.csv", ios::out|ios::trunc);
    csvStream<<"size"<<","<<"sortTime1"<<","<<"sortTime2"<<endl;
    // csvStream<<"size"<<","<<"sortTime1"<<endl;
    for(long i = 0; i <= SIZE; i += 1000){
        cout<<"Sorting size: "<<i<<endl;
        test_sort(i, MAXNUM, csvStream);
    }
    csvStream.close();
}
