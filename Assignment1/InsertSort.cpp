#include<iostream>
#include<vector>
using namespace std;

void InsertSort(vector<int>& arr, int size){
	for (int i=0; i<size; i++){
		int key = arr[i];
		int j = i - 1;
		while(j >= 0 && key > arr[j]){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

int main(){
	int size;
	cin>>size;
	vector<int> arr;
	for (int i = 0; i < size; i++){
		int k = 0;
		cin>>k;
		arr.push_back(k);
	}
	InsertSort(arr, size);
	for (int i = 0; i < size; i++){
		cout<<arr[i]<<" ";
	}
}
