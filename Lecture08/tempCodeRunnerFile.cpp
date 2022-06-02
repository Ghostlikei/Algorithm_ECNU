#include<iostream>
#include<vector>

using namespace std;

class Solution{
private:
    int size;
    int max(int a, int b){
        return a > b ? a : b;
    }

public:
    // 滚动数组法
    Solution& solution1(vector<int>& prices, vector<int>& value, int n, int m){
        size = n;
        vector<int> dp(m+1, 0);
        for(int i = 0; i < n; i++){
            for(int j = m; j >= prices[i]; j--){
                dp[j] = (max(dp[j], dp[j - prices[i]] + value[i]));
            }
        }

        cout<<dp[m]<<endl;
        return *this;
    }

};

int main(){
    Solution solution;
    int n,m;
    cin>>n>>m;
    vector<int> prices;
    vector<int> val;
    for(int i = 0; i < n; i++){
        int temp1, temp2;
        cin>>temp1>>temp2;
        prices.push_back(temp1);
        val.push_back(temp2);
    }

    solution.solution1(prices, val, n, m);
}