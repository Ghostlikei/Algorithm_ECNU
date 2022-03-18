# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：快速排序  

编号：No.04

年级：21级         

日期：2022年3月18号

***

## 1.实验目的

- 本实验主要设计以下算法：
  - 快速排序 
  - 随机快速排序

本实验所有源码（算法源码，构图源码）已上传至个人Github：

https://github.com/Ghostlikei/Algorithm_ECNU/tree/master/Assignment4

## 2. 算法思路

### 2.1 快速排序

- **快速排序**运用递归的方式，将数组以最后一个元素为支点，分为比该支点大的一组数组，以及比支点小的一组数组，最后将最后一个元素放到两数组当中的位置，对大小两数组进行递归操作，最后即可得到排序

- 由于二分和递归的存在，快速排序的预期时间复杂度为O(nlogn)

### 2.2 随机快速排序

- 随机快速排序就是把支点的元素随机化选择，以此来避免数组较坏的情况（若整个数组都是逆序的，则普通快速排序需要O(n^2)的时间来进行排序，因为只存在一个小数组，不存在另一个

- 算法源码：

### 快速排序、随机快速排序

为了测试方便，这里讲两种排序算法封装成一个类，方便在另一个文件里面进行调用：

```cpp
class Array{
private:
    vector<int> array;
    int size;
    bool isRandom;

public:
    Array(int newSize);
    
    void generateArray(int newSize);
    void setRandom(bool set);
    int getSize();

    void shuffle();

    int Partition(int low, int high);
    int RandomPivotPartition(int low, int high);
    void quickSort(int p, int q);

    void printArray();
};
```



- 我们来看其中比较关键的算法

### 分割数组

```
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
```

上述分割步骤的实现



### 随机分割数组

```cpp
int Array::RandomPivotPartition(int low, int high){
    int pvt, n, temp;
    n = rand();
    pvt = low + n % (high-low+1);
    swap(array[high], array[pvt]);
    return Partition(low, high);

}
```

随机选择支点，然后进行普通的分割算法



### 快速排序

```cpp
void Array::quickSort(int p, int q) {
    int pindex;

    if(p < q) {
        if(isRandom) pindex = RandomPivotPartition(p, q);
        else pindex = Partition(p,q);
        quickSort(p, pindex-1);
        quickSort(pindex+1, q);
    }

}
```

在这里可以调用`setRandom()`函数来对数组的随机化进行控制，默认随机化为true

## 3.算法测试

- 由于1e8的数据规模太大，算法没法在普通电脑上跑出来，所以将数据减小为1e5，方便观察（2e5之后算法直接被系统回收，而且耗时太长（不随机））

- 这次采用数据流的方式绘图，用c++实现时间测试之后导入csv，用matplotlib绘图

- 本次绘图的效果并不是很好，因为算法之间差异实在太大，因此仅做参考，详细数据请见仓库内

#### 普通快速排序的两种情况

  ![img02.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment4/img02.png?raw=true)

明显看出快速排序的最坏情况会变的非常慢



#### 快排和随机快排的对比

![img03.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment4/img03.png?raw=true)

数据之间差了1e3左右的数量级，差距一目了然



## 5.总结

- 本次上机实验过程中还是碰到了很多问题
  - 一开始想用拷贝构造来美化代码，但是拷贝构造太花时间了，要把数组的每一个元素全复制一遍，所以最后还是把返回值改成了void
  - 采用随机化的快排比非随机化的要飞速很多，差了好几个数量级
  - 数组元素一多之后，iostream就变得很慢，所以最后用的cstdio进行输入输出的控制



- 时间测试的时候也碰到了一些问题，本次第一次尝试代码之间的分离，在过程中遇到了很多麻烦
  - 一个项目中只能有一个main函数
  - 直接编译main文件不再有效，需要分开编译，比如`g++ A.cpp B.cpp -o out`，如果文件更多的话会非常麻烦，所以这次学习并写了一个简单的Makefile，以后编译只需要`make`即可
  - 头文件可以把所有导入的库，类声明和宏定义写好，非常清楚，具体写的时候只需要对每个函数单独编写即可



- 这次实验中采用了oop编程，编写好类之后，继续使用非常方便，例如时间测试的时候就可以调用`setRamdom()`来控制随机化，不需要对核心代码进行改动



- *下次最好测试这么大的数据量，根本就跑不出来，跑一个也跑不出来，特别是数据不好的情况*
















​	  



















​    

