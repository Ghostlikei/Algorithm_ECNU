#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<time.h>

using namespace std;

class Array{
private:
    vector<int> array;
    int size;
    bool isRandom;

public:
    Array(){
        cin>>size;
        for(int i = 0; i < size; i++){
            int temp;
            cin>>temp;
            array.push_back(temp);
        }
        isRandom = false;
    }

    Array setRandom(bool set){
        isRandom = set;
        return *this;
    }

    int getSize(){return size;}

    Array shuffle() {
        srand(time(NULL));
        for (int i = size - 1; i > 0; i--) {
            int j = rand()%(i + 1);
            swap(array[i], array[j]);
        }
        return *this;
    }


    int Partition(int low, int high) {
        int pivot, index;
        index = low;
        pivot = high;
        for(int i = low; i < high; i++) {
            if(array[i] < array[pivot]) {
                swap(array[i], array[index]);
                index++;
            }
        }
        swap(array[pivot], array[index]);
        return index;
    }

    int RandomPivotPartition(int low, int high){
        int pvt, n, temp;
        n = rand();
        pvt = low + n % (high-low+1);
        swap(array[high], array[pvt]);
        return Partition(low, high);
    }

    Array quickSort(int p, int q) {
        int pindex;

        if(p < q) {
            if(isRandom) pindex = RandomPivotPartition(p, q);
            else pindex = Partition(p,q);
            quickSort(p, pindex-1);
            quickSort(pindex+1, q);
        }

        return *this;
    }
    
    Array printArray(){
        for(int i = 0; i < size; i++){
            cout<<array[i]<<" ";    
        }
        return *this;    
    }
};

int main(){
    Array myArray;
    myArray.shuffle().quickSort(0, myArray.getSize()-1).printArray();
}

