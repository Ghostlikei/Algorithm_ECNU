#include<iostream>
#include<vector>

using namespace std;

class Solution{
private:
    vector<int> next;
    void getNext(vector<int>& price, int size){
        for(int i = 0; i < size - 1; i++){
            next.push_back(price[i+1] - price[i]);
        }
    }

public:
    Solution& solution1(vector<int>& price, int size){
        int result = 0;
        int temp = 0;
        getNext(price, size);
        for(int i : next){
            if (i >= 0) temp += i;
            else {
                result = temp > result ? temp : result;
                temp = 0;
            }
        }

        if (temp > 0) result = temp > result ? temp : result;
        cout<<result<<endl;
        return *this;
    }

    Solution& solution2(vector<int>& price, int size){
        int result = 0;
        getNext(price, size);
        for(int i : next){
            if (i >= 0) result += i;
        }

        cout<<result<<endl;
        return *this;
    }
   
};

int main(){
    int n;
    cin>>n;
    Solution solution;
    vector<int> price;
    for(int i = 0; i < n; i++){
        int temp;
        cin>>temp;
        price.push_back(temp);
    }

    solution.solution1(price, n);
}