#include "CountingSort.h"
using namespace CountingSort;

    Array::Array(int newSize, int maxNumber){
        size = newSize;
        if(OJ) {input();}
        else {generateArray(maxNumber);}
        max = INT32_MIN;
        memset(count, 0, sizeof(count));
    }

    void Array::generateArray(int maxNum){
        srand((int)time(NULL));
        for(int i = 0; i < size; i++){
            array.push_back(rand() % maxNum);
        }
    }

    int Array::getSize(){
        return size;
    }

    void Array::input(){

        for(int i = 0; i < size; i++){
            int temp;
            cin>>temp;
            array.push_back(temp);
        }
    }

    void Array::counting(){
        for(int i : array){
            if (i > max){
                max = i;
            }
            count[i]++;       
        }
    }

    void Array::sort(){
        int reversedIndex = size - 1;
        for(int i = max; i >= 0; i--){
            while (count[i] != 0){
                array[reversedIndex--] = i;
                count[i]--;
            }
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
//     testArray.counting();
//     testArray.sort();
//     testArray.printArray();
// }