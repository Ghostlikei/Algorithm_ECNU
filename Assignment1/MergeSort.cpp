#include<iostream>
#include<vector>
using namespace std;

void Merge(vector<int>& arr, int head, int mid, int tail){
    vector<int> leftArr(arr.begin() + head, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + tail + 1);
    auto Iter = arr.begin() + head;
    auto leftIter = leftArr.begin();
    auto rightIter = rightArr.begin();

    while(leftIter != leftArr.end() && rightIter != rightArr.end()){
        if(*leftIter > *rightIter){
            *Iter = *rightIter;
            Iter++;
            rightIter++;
        }
        else{
            *Iter = *leftIter;
            Iter++;
            leftIter++;
        }
    }

    if (rightIter != rightArr.end()){
        while(rightIter != rightArr.end()){
            *Iter = *rightIter;
            Iter++;
            rightIter++;
        }
    }

    if (leftIter != leftArr.end()){
        while(leftIter != leftArr.end()){
            *Iter = *leftIter;
            Iter++;
            leftIter++;
        }
    }


}
void MergeSort(vector<int>& arr, int head, int tail){
    if (head >= tail) return;
    int mid = (head + tail)/2;
    MergeSort(arr, head, mid);
    MergeSort(arr, mid + 1, tail);
    Merge(arr, head, mid, tail);
}
int main()
{
    int size;
    cin>>size;
    vector<int> arr;
    for(int i = 0; i < size; i++){
        int number = 0;
        cin>>number;
        arr.push_back(number);
    }
    MergeSort(arr, 0, size-1);
    for (int i = 0; i < size; i++){
		cout<<arr[i]<<" ";
	}
}