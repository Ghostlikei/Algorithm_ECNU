#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class PriorityQueue{
private:
    vector<int> data;
    int size0;
public:
    PriorityQueue() {size0 = 0;};
    PriorityQueue add(int entry);
    PriorityQueue swapDown(size_t parent);
    PriorityQueue remove();
    PriorityQueue swapUp(size_t child);
    bool empty();
    int size();
    int get(); 
};



int PriorityQueue::size(){
    return size0;
}

bool PriorityQueue::empty(){
    return data.size() == 0;
}

PriorityQueue PriorityQueue::add(int entry){
    data.push_back(entry);
    swapUp(data.size() - 1);
    size0++;
    return *this;
}

int PriorityQueue::get(){
    if (data.empty()) return 0;
    int result = data[0];
    
    return result;
}

PriorityQueue PriorityQueue::remove(){
    if (data.empty()) return *this;
    swap(data[0], data[size0 - 1]);
    data.pop_back();
    size0--;
    swapDown(0);
    
    return *this;
}

PriorityQueue PriorityQueue::swapUp(size_t child){
    if (child >= data.size()) return *this;
		
		while (child) {
            size_t parent = (child - 1) / 2;
			if (data[parent] > data[child]) {
				swap(data[parent], data[child]);
				child = parent;
			}
			else return *this;
        }
        return *this;
}

PriorityQueue PriorityQueue::swapDown(size_t parent){
    size_t child = parent * 2 + 1;
	while (child < data.size()) {
		if (child + 1 < data.size() && data[child] > data[child + 1]) {
			child++;
		}
 
		if (child < data.size() && data[parent] > data[child]) {
			swap(data[parent], data[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else return *this;
    }			
    return *this;
}

int main(){
    PriorityQueue PQ;
    // string op;
    // while(cin>>op){
    //     if (op[0] == 'a'){
    //         int entry;
    //         cin>>entry;
    //         PQ.add(entry);
    //         continue;

    //     }

    //     if (op[0] == 'r') {PQ.remove(); continue;}

    //     if (op[0] == 'g') {
    //         int result;
    //         result = PQ.get();
    //         cout<<result<<endl;
    //         continue;
    //     }
    // }

    long m,n;
    cin>>m>>n;
    
    for(int i = 0; i < m; i ++){
        int temp;
        cin>>temp;
        PQ.add(temp);
    }

    for(int i = 0; i < n - 1; i++){
        int temp = PQ.get();
        PQ.remove();
        cout<<temp<<" ";
    }

    int temp = PQ.get();
    cout<<temp;

    return 0;
}




