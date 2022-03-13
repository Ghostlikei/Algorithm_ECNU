# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：堆   

编号：No.03

年级：21级         

日期：2022年3月13号

***

## 1.实验目的

- 本实验主要设计以下算法和数据结构：
  - 堆 
  - 优先队列
  - 堆排序算法
- 分析和比较两种算法的实现原理，算法复杂度，算法时间消耗

本实验所有源码（算法源码，构图源码）已上传至个人Github：

https://github.com/Ghostlikei/Algorithm_ECNU/tree/master/Assignment3

## 2. 算法思路

### 2.1 堆

- 数据结构

​      **堆**(Heap)是一种基于**完全二叉树**的数据结构，具体的建堆原理请见算法导论，由于数组的特性，实际操作的时候并不需要建树，只需要通过2n和2n+1来找到自己的子节点，找父节点只需要n/2即可

​	  **优先队列**(PriorityQueue)是一种基于堆的数据结构，本质上也是队列，但是队列中元素按照顺序排列，其排序算法使用的是堆排序

- 算法

​	  **堆排序算法**是在建立堆的基础上，把堆顶的元素和堆底的互换然后在向下建堆，重复直到每个元素都被取出为止

​      本次oj中的topK问题就是堆排序的简易版本，只需要取出前K个后停止即可

​      

- 算法源码：

### 建堆/优先队列

```cpp
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
```

建堆的难点在于写出向上建堆和向下建堆两个函数，需要注意终止条件以及找子节点的时候不要写错

如果需要用到泛式编程，只需要引入类模板和重写比较函数，由于oj中并没有要求，所以这里让代码简化就没有泛式编程

### 堆排序算法

```
priority_queue<int,vector<int>,greater<int>> PQ;
        
for(int j = 0; j < i; j++){
	PQ.push(rand());
}

for(int j = 0; j < i; j++){
    PQ.pop();
}
```

由于后续需要时间测试，所以直接调用经过硬件优化的STL



- 时间复杂度：

  详见算法导论，在建堆过程中，由于存在取整的问题，所以 nlogn并不是紧确界，而是**O(n)**

  而堆排序算法中，需要对每个元素遍历，而且向下翻转的次数最多为logn(完全二叉树每一层容积指数递增)，所以是**O(nlogn)**



- 空间复杂度

​	  因为交换的时候只需要对两个变量操作，所以建堆的时候复杂度为**O(n)**，而堆排序算法的复杂度是**O(1)**



## 3.算法测试

- 由于自己写的优先队列效率太低，所以直接调用STL进行时间测试

- 这次采用数据流的方式绘图，用c++实现时间测试之后导入csv，用matplotlib绘图，因为c++的效率会有明显的优势

  

  ![img02.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment3/img02.png?raw=true)

  基本符合时间复杂度的预测，详细数据请见github



## 5.总结

- 本次实验在上机的过程中主要碰到的TLE的问题（topk），分析下来是自己写的优先队列效率太低，最后直接采用STL中的优先队列，就能达到时间标准，自己写的队列还有很大的优化空间
















​	  



















​    

