# **华东师范大学数据科学与工程学院上机实践报告**

***

### 课程名称：算法设计与分析      

### 上机实验名称：排序算法     

### 编号：No.01

### 年级：21级            

### 日期：2022年2月25号

***

## 1.实验目的

- 本实验主要围绕排序算法展开，主要关于以下两种算法：
  - 插入排序
  - 归并排序
- 本实验主要分析两种算法的原理，时间复杂度，空间复杂度，算法优缺点，以及算法的使用场景
- 实验用的所有源码和文件已上传至GitHub：https://github.com/Ghostlikei/Algorithm_ECNU/tree/master/Assignment1

## 2.算法思路

### 2.1 插入排序（Insertion Sort）

- **算法原理**

​		插入排序有点类似于打牌时用的理牌方法，遍历数组，将已遍历的称为**有序组**，未遍历的称为**无序组**

​		把无序组的第一个元素和有序组依次进行比较，找到比前面大，后面小（既有序的位置）然后放入，此过程称为插入

​		例如：有序组为12 45 67 89 无序组为 13 53 43 24，那么无序组的第一个13 应该放在12和45之间，以此类推

- 提交oj的源码如下：

```cpp
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
```



- **时间复杂度**

  最优情况：遍历的时候每个无序组的第一个元素恰好排到有序组的第一个元素，所以为**O(n)**

  最坏情况：每个无序组的第一个元素要把有序组全遍历一遍才能排入，遍历为n，有序组遍历为1~n，所以为**O(n^2)**

  关于插入排序的稳定性在后面会讨论

  

-  **空间复杂度**

​      由于比较时只有单个数字之间比较，所以空间复杂度为**O(1)**



### 2.2 归并排序（Merge Sort)

- **算法原理**

​	  归并排序本质用的是分治法，先将数组分为两部分（左半，右半）然后再对两部分进行同样的递归操作，直到每个部分都只剩下一个元素，在进行**归并**，递归部分的代码如下：

```cpp
MergeSort(Arr[], left, mid)
MergeSort(Arr[], mid+1, right)
Merge(Arr[], left, mid, right)
```

​     上面`MergeSort`表示“分”的过程，而 `Merge`表示归并的过程

​	 算法归并的过程中会碰到讲两个升序数组合并成一个升序数组的问题，这时候我们用最典型的双指针法，定义两个数组的头指针，把数值小的指针记录到数组中，然后把该指针后移，再进行比较，直到其中一个指针指到该数组的尾部，最后将剩下的数组拼接到尾部即可

- 提交oj的代码如下：

  ```cpp
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
  ```

  

- **时间复杂度**

  最好情况：双指针归并时只移动一个指针，比较次数为**n log(n)/2** ，时间复杂度为**O(n log(n))**

  最坏情况：双指针交替移动，比较次数为**n log(n) + n**，时间复杂度为**O(n log(n))**

  由此看出，归并排序是一种**稳定**排序方式，不管原数组如何，比较的次数都是相对稳定的

- **空间复杂度**

​      最大使用空间为最后一次归并，所以空间复杂度为**O(n)**

## 3.算法比较

### 3.1 排序算法比较

- 归并排序是一种稳定的排序算法，相比于时间复杂度相同的快速排序，归并排序用的时间十分稳定，但是占用的内存比较大

​      由于其稳定性，适合处理**较大规模的数据**

- 选择排序因为其最优时间复杂度为n，所以在处理**小规模数据以及结构较好的数据**的时候更有优势

  由于插入排序算法的最优和最劣时间复杂度差别较大，所以不适合处理大规模数据

### 3.2 排序算法的示意图

- 借用了Matplotlib绘制了两种算法面对不同数据量时所用的时间，由此看出，当数据量上升时，归并排序具有明显的优势
- 此图也可以很明显的看出，选择排序具有不稳定性

![Li_2.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment1/Li_2.png?raw=true)

- 数据规模比较小的时候，选择排序会比较快

![l1_4.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment1/l1_4.png?raw=true)

### 3.3 补充

- 归并排序可以应用于很多经典问题，特别是数组结构不好的时候（逆序很多），比如**小和问题**，**逆序对问题**
- 当**递归深度过大**时，归并排序会占用大量内存，此时不应该继续使用归并，而是选择堆排序等空间复杂度较小的算法
- 选择排序适用于**数据规模小**，**结构较好**的情况，比如c++标准库中的`std::sort`，当数据量较小的时候就会使用选择排序



## 4.总结

- 本次实验为大一下的第一次实验课，也是第一次用报告的形式交作业，所以想尝试用Markdown+GitHub的形式来提交报告，可能比单纯的.doc文件更加简洁美观一点
- 提交oj还是跟上学期类似，写两种算法的时候都碰到了一点小问题，不过最后都解决了
- 尝试用matplotlib画一个直观的图，但是当时间t很小的时候差别不是很明显，可能是设置精度上的问题，也有可能是数据量太小的时候，算法本身已经不是影响时间的主要因素了
- c++真的比python快很多，快很多很多





































