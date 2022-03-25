# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：线性时间排序 

编号：No.05

年级：21级        

日期：2022年3月25号

***

## 1.实验目的

- 本实验主要设计以下算法：
  - 计数排序 
  - 基数排序

本实验所有源码（算法源码，构图源码）已上传至个人Github：

https://github.com/Ghostlikei/Algorithm_ECNU/tree/master/Assignment5

## 2. 算法思路

### 2.1 计数排序

- **计数排序**就是将数组中每个数出现的次数记录下来，然后通过**倒序**把数组从大到小依次从队尾排列到队首

### 2.2 基数排序

- **基数排序**就是把数组中的每个元素，按照每个元素的每个变量从小到大依次进行排序，例如整数就是从个位数开始排序到最高位，时间就是秒，然后分，最后小时

#### 2.3 算法源码

### 计数排序

避免命名重复，直接采用c++ 的namespace功能进行封装：

```cpp
namespace CountingSort{
    class Array{
    private:        
        vector<int> array;
        int size;
        int max;
        int count[100010];

    public:
        Array(int newSize, int maxNumber);
        void generateArray(int maxNum);
        int getSize();
        void input();
        void counting();
        void sort();

        void printArray();
    };
}
```

- 其中的max记录最大值，count数组就是记录每个元素出现的次数，考虑到只有整数的情况所以用数组效率最高，其实也可以用STL当中的pair<typename1, typename2>进行代替，如果需要对其他类型进行计数排序的话



- 我们来看其中比较关键的算法

上述计数步骤的实现

```cpp
void Array::counting(){
    for(int i : array){
        if (i > max){
            max = i;
        }
        count[i]++;       
    }
}
```



排序步骤的实现，倒序把记录好的元素放入原数组

```cpp
void Array::sort(){
    int reversedIndex = size - 1;
    for(int i = max; i >= 0; i--){
        while (count[i] != 0){
            array[reversedIndex--] = i;
            count[i]--;
        }
    }
}
```



### 基数排序

```cpp
namespace RadixSort{
    class Array{
    private:
        int size;
        int radix = 0;
        vector<int> array;
        const long digits[9]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

    public:
        Array(int newSize, int maxSize);
        int getSize();

        void input();
        void generateArray(int maxSize);

        void radixSort();
        void printArray();

    };

}
```

- `radix`指的是基数的最大值，而`digits`是建立了基数的实际情况，为了加速计算



- 同样，我们来看比较关键的代码

这里使用了c++当中的lambda函数作为比较函数，返回值即为对每个数的当前位数进行比较，然后进行排序，循环选取不同的位数，可以大大减小代码量，增加效率

```cpp
void Array::radixSort(){
    for(int i = 0; i < radix; i++){
        auto cmp = [&](int a, int b){
            int aDigit = (a % digits[i]) / (digits[i] / 10);
            int bDigit = (b % digits[i]) / (digits[i] / 10);
            return a < b;
        };
        sort(array.begin(), array.end(), cmp);
    }
}
```



## 3.排序算法比较

- 同样使用matplotlib进行绘图，由于线性时间排序太快，所以把数据规模扩大到1e6

![img.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment5/img.png?raw=true)

基数排序实在太快，哪怕把整数范围扩充到INT32_MAX也一样全是0，对于更大的数据规模也是如此

计数排序基本符合线性分布，当然也能看出当整数范围大的时候也会出现时间的波动



- 计数排序和快速排序的比较，这里是整数范围在10000以内，可以看出计数排序具有明显的优势，但是当使用随机快排的时候，计数排序就显得非常慢了（数据规模小的时候计数排序波动太大，所以这里没有画图，数据记录在仓库中）

![img02.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment5/img02.png?raw=true)

## 4.算法的适用场景

- 计数排序和基数排序的最大特点是稳定，最优情况为线性时间，对于**数据重复较多**，**范围不大**的情况非常适用，例如对于不同时间的排序，音乐软件的歌单排序这种，更需要在保证时间的同时保留更多的排序信息
- 而其他常规排序如快排堆排这些更适合**数据更离散**，**跨度较大**的情况，适合精度要求高的情况，当然这要分场合进行讨论，这里不下决定性的结论

## 5.总结

- 本次上机实验的过程相对顺利，没有花费很长的时间
- 在画图的时候由于算法之间的差异很大（又是差了几个数量级），只能明显看出算法运用于整数时候的优势，个人建议就是下次测试算法可以采用一些别的数据，比如字符串排序，浮点数排序，结构体排序这些，虽然可能导致代码量的增加，但是相比于整数的测试会更有意义一些
















​	  



















​    

