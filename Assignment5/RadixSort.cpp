#include "RadixSort.h"
using namespace RadixSort;

    Array::Array(int newSize, int maxSize){
        size = newSize;
        if(OJ) input();
        else generateArray(maxSize);
    }

    int Array::getSize(){return size;}

    void Array::generateArray(int maxSize){
        srand((int)time(NULL));
        for(int i = 0; i < size; i++){
            array.push_back(rand() % maxSize);
        }
    }

    void Array::input(){
        for(int i = 0; i < size; i++){
        int temp;
        cin>>temp;
        radix = temp % 10 > radix ? temp % 10 : radix;
        array.push_back(temp);
        }
    }

    void Array::radixSort(){
        for(int i = 0; i < radix; i++){
            auto cmp = [&](int a, int b){
                int aDigit = (a % digits[i]) / (digits[i] / 10);
                int bDigit = (b % digits[i]) / (digits[i] / 10);
                return a < b;
            };
            sort(array.begin(), array.end(), cmp);
        }
    }

    void Array::printArray(){
        for(int i : array){
        cout<<i<<" ";
        }
    }

// int main(){
//     int n;
//     cin>>n;
//     Array testArray(n);
//     testArray.radixSort();
//     testArray.printArray();
// }