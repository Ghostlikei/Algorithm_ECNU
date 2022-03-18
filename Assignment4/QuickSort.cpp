#include "QuickSort.h"
using namespace std;


Array::Array(int newSize){
        if(OJ){
            for(int i = 0; i < newSize; i++){
                int temp;
                cin>>temp;
                array.push_back(temp);
            }
            isRandom = true;
            size = newSize;
            return;
        }
        
        generateArray(newSize);

    }

    void Array::generateArray(int newSize){
        srand((int)time(NULL));
        for(int i = 0; i < newSize; i++){
            array.push_back(rand());
        }
        isRandom = true;
        size = newSize;

    }

    void Array::setRandom(bool set){
        isRandom = set;
    }

    int Array::getSize(){return size;}

    void Array::shuffle() {
        srand(time(NULL));
        for (int i = size - 1; i > 0; i--) {
            int j = rand()%(i + 1);
            swap(array[i], array[j]);
        }
    }


    int Array::Partition(int low, int high) {
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

    int Array::RandomPivotPartition(int low, int high){
        int pvt, n, temp;
        n = rand();
        pvt = low + n % (high-low+1);
        swap(array[high], array[pvt]);
        return Partition(low, high);

    }

    void Array::quickSort(int p, int q) {
        int pindex;

        if(p < q) {
            if(isRandom) pindex = RandomPivotPartition(p, q);
            else pindex = Partition(p,q);
            quickSort(p, pindex-1);
            quickSort(pindex+1, q);
        }

    }
    
    void Array::printArray(){
        for(int i = 0; i < size; i++){
            printf("%d ", array[i]);    
        }    
    }


// int main(){
//     int size;
//     cin>>size;
//     Array myArray(size);
//     myArray.quickSort(0, myArray.getSize()-1);
//     myArray.printArray();
// }

