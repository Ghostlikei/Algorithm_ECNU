# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：动态规划  

编号：No.08

年级：21级          

日期：2022年4月27号

***

## 1.实验目的

- 本实验主要解决以下问题：
  - 0-1背包问题
  - 背包问题

## 2. 算法思路

### 0-1背包问题

```cpp
Solution& solution1(vector<int>& prices, vector<int>& value, int n, int m){
    // 滚动数组法
    vector<int> dp(m+1, 0); // 初始化dp数组
    for(int i = 0; i < n; i++){ // 第一层循环，遍历给定的条件
        for(int j = m; j >= prices[i]; j--){// 第二层循环
            dp[j] = (max(dp[j], dp[j - prices[i]] + value[i]));// 状态转移方程
        }
    }

    cout<<dp[m]<<endl;
    return *this;
}
```

- 我们来看一下第二层循环和状态转移方程是怎么来的

首先，第一层循环是把给定的物品，按照价格从小到大依次放入考虑范围之内，例如i=0就是只看第一个，i=1就是前两个都考虑

其次，dp[j]表示背包容量为j的时候所背的最大价值，这里从大到小是因为只能拿一个，因为占钱越多满意度越高

之后就有两种选择，拿i和不拿i，不放i就是还取自己本身dp[j]，放i就是把i的占用大小减掉，把之前得到的dp[j-prices[i]]再加上i的价值，从而得到上面的状态转移方程。最优解就是两种情况的最大值。

**动态规划**的思想就体现在拿i的情况，用dp数组记录dp[j - prices[i]]就能避免重复计算。

### 完全背包问题

```cpp
Solution& solution2(vector<int>& prices, vector<int>& value, int n, int m){
    vector<int> dp(m+1, 0);
    for(int i = 0; i < n; i++){
        for(int j = prices[i]; j <= m; j++){// 唯一的不同之处
            dp[j] = (max(dp[j], dp[j - prices[i]] + value[i]));
        }
    }

    cout<<dp[m]<<endl;
    return *this;
}
```

- 为什么这里的j从小到大考虑了？

因为倒序遍历只会放进去一次，而正序就可以放进去多次，具体的原因是倒序的时候前面的dp元素是没有考虑过放i的，但是正序的时候就考虑过，比如prices[0] = 1，value[0] = 20

如果正序遍历

dp[1] = dp[1 - prices[0]] + value[0] = 20

dp[2] = dp[2 - prices[0]] + value[0] = 40 这里dp1被i影响了，相当于放了两个i

倒序

dp[2] = dp[2 - prices[0]] + value[0] = 20 

dp[1] = dp[1 - prices[0]] + value[0] = 20
















​	  



















​    

