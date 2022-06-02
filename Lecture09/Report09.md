# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：贪心算法  

编号：No.09

年级：21级        

 

日期：2022年4月30号

***

## 1.实验目的

- 本实验主要解决以下问题：
  - 股票买卖问题

## 2. 算法思路

### 单次买卖股票

```cpp
class Solution{
private:
    vector<int> next;// private一个next数组，存储当天和后一天的差值
    void getNext(vector<int>& price, int size){
        for(int i = 0; i < size - 1; i++){
            next.push_back(price[i+1] - price[i]);
        }
    }// 计算next数组

public:
    Solution& solution1(vector<int>& price, int size){
        int result = 0;
        int temp = 0;
        getNext(price, size);// 先记一下next数组
        for(int i : next){
            if (i >= 0) temp += i;// 贪心算法的体现，具体下面讲解a
            else {
                result = temp > result ? temp : result;// b
                temp = 0;
            }
  
        }
        if (temp > 0) result = temp > result ? temp : result; // 防止最后一个也是正的，但是没有被记录
        cout<<result<<endl;
        return *this;
    }
}
```

- 我们来看一下贪心算法的思想是怎么在这道题里面运用的

贪心算法的本质是**局部最优累计获得整体最优**

这道题里的局部最优指的是，第一天买，第二天卖得到正收益，那就是好的，得到负收益，就是不好的，实现在代码的a处

解决这道题的思路就是把**连续**的正收益全部加起来，就可以得到一个总体的收益，再把这些**连续的正收益组**取最大的一个就是整体收益最大。实现在代码的b处

算法的正确性证明相当简单，这里进行一个粗糙的文字证明，首先证明连续正收益累加是局部最大的，分情况讨论：

1、前，后出现负收益，加上比不加上局部收益要小

2、前，后出现正收益，加上比不加上收益要大

其次证明局部最优累计获得整体最优，因为前后之间收益计算都是独立的，没有关联度，不会对最优结果产生影响。



### 多次买卖问题

```cpp
Solution& solution2(vector<int>& price, int size){
    int result = 0;
    getNext(price, size);// 同样记录next数组
    for(int i : next){
        if (i >= 0) result += i;// 只要收益就买
    }

    cout<<result<<endl;
    return *this;
}
```

多次买卖的情况相比于之前的要更加简单，同样的局部最优得到全局最优，

我们先把问题拆分成多个独立的子问题：当成每日都进行一次买卖操作，例如d1买d3卖拆分为d1买，d2卖和d2买d3卖，结果是相同的，收益是独立的。

所以我们把所有的正收益加起来就是总体的收益最高，证明就是只要赚钱就买，不赚钱就不买，总收益一定是最大的。
















​	  



















​    

