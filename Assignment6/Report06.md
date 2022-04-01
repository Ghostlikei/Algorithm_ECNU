# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：哈希  

编号：No.06

年级：21级          

日期：2022年4月1号

***

## 1.实验目的

- 本实验主要设计以下部分：
  - 哈希算法 
  - 哈希冲突的解决

本实验所有源码（算法源码，构图源码）已上传至个人Github：

https://github.com/Ghostlikei/Algorithm_ECNU/tree/master/Assignment6

## 2. 算法思路

### 2.1 哈希表

- **哈希表**是一种非常经典的键值对（Key，Value）储存方式，而且运用非常广泛，其最大的特点为：
  - 存储的无序性
  - 查找的高效性

### 2.2 哈希函数

- 哈希函数也叫**散列函数**，散列，顾名思义就是要把数据根据数据的**键**，**均匀分布**在哈希表中，完全均匀是哈希函数的最高要求，但是实际上不可能打到完全的均匀分配，所以会不可避免地出现**哈希冲突**的情况，既两个不一样的KEY通过散列函数得到了同样的结果。

- 散列函数有非常多的形式，在《算法导论》上都有讨论，事实上，高级语言库也自带散列函数可以调用，本次实验采取了除法散列法

### 2.3 哈希冲突的解决 

- 拉链法

​      把哈希表的每个位置看做单向链表的头结点，当发生冲突的时候，就在当前位置向下延伸一节链表用于存储数据，特点是**不需要扩充哈希表**，但是当单个链表太长的时候**查找会变慢**。

- 探测法

​      当哈希冲突发生的时候，通过**探针（Probe）**按照**一定的方法**来监测哈希表中还有没有空位可以存放数据，实验中测试了线性探测（按数组顺序往后找）以及二次探测（同样是往后找，但是往后的速度二次增长），特点是**空间固定在原表上**，但是当表满的时候要进行**扩充和重新分配（rehash）**



## 3.代码分析

### 拉链法

使用了STL，明显减小了代码量，而且方法更加安全高效

为了测试方便，同样把哈希表封装成一个类，方便进行调用，这次参考了课上的要求直接用注释来分析代码：

```cpp
template<typename Key, typename Value>
class HashTable{
private:
    
    int divitor; // 除法散列法的除数
    size_t capacity; // 哈希表的容积
    size_t size; // 当前表内的数据大小
    vector<list<pair<Key, Value>>> table; // 哈希表，直接调用STL的链表，对于泛型更容易操作
    int Hash(const Key& key)//哈希函数
        
public:
    HashTable<Value>(int div, size_t tableSize); // 构造函数

    void put(const pair&<Key, Value>); // 数据的插入
    bool find(const Key& key);// 数据的查找
    int getSize();

    //以下为时间测试的接口
    void generateData(size_t number);
    void timeTest(size_t Number, ofstream& stream);

};
```



- 我们来看其中比较关键的算法

#### 哈希函数

```cpp
int Hash(Key& key){
    return val % divitor > 0 ? val % divitor : -val % divitor;
    // 除法哈希，防止出现取模为负的情况，所以取绝对值
}// ！注意这里，对于不同类型的数据要进行函数重载
```



#### 存放数据

```cpp
void put(const pair<Key, Value>& val){
    int index = Hash(val.first);
    table[index].emplace_back(val);// 对于哈希得到的位置在链表的尾部插入
}
```



#### 数据查找

```cpp
bool find(const Key& element){
    int index = Hash(element);
    auto iter = table[index].begin();// 直接用List的迭代器进行查找，更加安全
    while(iter != table[index].end()){
        if(*iter.first == element) return true;// ！重载的第二个地方，对于不同的数据类型要把==重写
        iter++;
    } 
    return false;
}
```



### 探测法

方便测试，这里省去了Key值，直接用Value进行运算，和上面相同的部分不再分析

这里并没有测试需要rehash的情况，如果需要其实只需要在put函数内加入对于size和capacity大小的判断，因为vector容器会有自动扩容的操作，只需要把扩容后的元素重新分配即可

```cpp
template<typename Value>
class HashTable{
private:
    
    int divitor;
    size_t capacity;
    size_t size;
    int Index;// 控制指数，线性为1，二次为2
    vector<pair<Value, bool>> table; // 通过多加入一个变量来判断是否这个位置被利用
    int Hash(Value val);
    int pow(int num, int index);// 控制查找时增量的函数
        
public:
    HashTable<Value>(int div, size_t tableSize, int Index); // 构造函数

    void put(const Value& val); // 数据的插入
    bool find(const Value& element);// 数据的查找
    int getSize();

    //以下为时间测试的接口
    void generateData(size_t number);
    void timeTest(size_t Number, ofstream& stream);

};
```



- 我们来看其中比较关键的算法


#### 存放数据

```cpp
void put(const Value& val){
    int index = Hash(val);// 通过哈希函数获得位置
    int cnt = 0;// 增量计数
    while(cnt < capacity && table[(index + pow(cnt,x)) % (capacity - 1)].second == true){
        cnt++;
    }// 通过index和cnt的组合作为探针，其中pow控制探针的类型        
    table[(index + pow(cnt,x)) % (capacity - 1)].first = val;
    table[(index + pow(cnt,x)) % (capacity - 1)].second = true;//放入操作，并把位置封闭        
}
```



#### 数据查找

```cpp
bool find(const Value& element){
    int index = Hash(element);
    int cnt = 0;
    //同样的探针测定和探针操作
    while(cnt < capacity){
        if(table[(index + pow(cnt,x)) % (capacity - 1)].first == element) return true;        
        cnt++;
    }
    return false;
}
```



## 4.算法测试

- 这次采用数据流的方式绘图，用c++实现时间测试之后导入csv，用matplotlib绘图

- 本次绘图的时候因为哈希查找的波动比较大，所以绘制了散点图

#### 拉链法

![list2.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment6/list2.png?raw=true)

#### 线性探测和二次探测的对比

![probe.png](https://github.com/Ghostlikei/Algorithm_ECNU/blob/master/Assignment6/probe.png?raw=true)

当数据规模扩大的时候，由于可能存在数据分布不均的情况，线性探测法就变得非常吃力

## 5.算法分析和讨论

现在我们来讨论一些查找算法之间的区别

- 数组查询

适用于数据规模非常小的情况，时间复杂度为O(n)，数据规模一大就变得非常慢，优点是简单，不需要额外写算法

- 二分查找

适用于数据有序的情况，当**数据有序**时时间复杂度为O(logn)。无序的情况则需要先把数据进行排序，这个时候二分查找就没有优势了。类似的，其他一些有顺序要求的查找数据结构和算法，具有类似的性质，如三分查找，快速查找，二叉搜索树/二叉平衡树，2-3树，红黑树，B/B+树等等，当面对数据结构**完全无序**的情况下就没有明显的优势。同样，当数据结构具有一定的顺序或者特点，比如时间顺序，字母顺序，大小顺序，这些数据结构和算法会比哈希法和遍历法好很多。

- 哈希法

适用于数据完全无序的情况，例如键值对(pair, tuple...)的存储，字典(dict)，集合(set)等等，平均时间复杂度为O(1)，最坏时间复杂度为O(n)，特点就是高效和高效，特别需要注意的就是解决哈希冲突的办法，哈希函数的设置（散列是不是平均），以及在hash和rehash过程中对于哈希表本身大小的控制，都会影响hash算法整体的效率和空间开销。当面对查找有一定特点的数据的时候（例如文件查找，个人信息查找），哈希法相比上面的一些高效的数据结构会逊色很多。

## 5.总结

- 本次上机实验过程中碰到的问题
  - c/c++ 在负整型在取模的时候会出现负数的情况，如果需要的话要取绝对值。
  - 本来想手写链表，发现不太好用，然后想调用一下`std::forward_list`的单向链表的容器，但是很多操作会出现问题，最后还是采用了比较稳定的`std::list`容器放入哈希表。
  - 尝试了泛型编程，但是没有写哈希表中的iterator。其实重载一下是更加规范的写法，在进行插入和查找的时候调用迭代器操作更符合泛型编程的要求。这里为了测试和提交oj方便也没有去重载比较函数，以及哈希函数，更规范的写法是在使用的时候进行继承或者单独重写。
  - hash算法可以调用c++的自带算法，为了方便还是采用了除法散列。

- 时间测试
  - 其实本次可以测试的变量有很多，数据规模，查找的个数，以及哈希表的大小对于整个算法的影响都是可以测试的，本次要求的是对于插入和查找的测试，所以只进行了这两项
  - 画出来的图像和时间复杂度的预期还是比较吻合的
  
- 关于哈希表大小和数据量的关系(rehash的讨论)，（以下部分有参考其他文章）

  由于测试的要求实验中并没有实现rehash算法，但实际上，对于哈希表的大小和数据量的控制还是非常讲究的。首先，扩容的时候通常进行**移位**操作，效率会很高。

  其次，当数据逐渐占满哈希表的时候，哈希冲突的可能性大大增加（由概率计算就可知），所以会有提出**负载因子(load factor)**这个概念，就是已占满的格子/总容积，得到的这个小数。当负载因子实际值超过阈值的时候，进行扩容和重哈希的操作是比较合适的。一般常用的负载因子控制在[0.6, 0.8]上，例如java语言自带的哈希算法的负载因子就是0.75。至于这个确切值是怎么来的，实际上是源于数学推导得到的经验公式：
  $$
  \lim_{s \to \infty} \frac {\log{2} } {\log{\frac{s}{s-1}}}
  $$
  当数据量无穷大的时候，这个数趋近于log2，那为什么一般选择0.75，或者说哈希表的大小大约是数据量的1.3倍呢？是因为3/4这个小数方便扩容控制，通过简单的移位操作就可以完成扩容，不会出现乘完是小数的情况。

  基于语言，硬件和一些其他的因素，上述的负载因子会出现变化，甚至可能出现大于1的情况，例如Go语言的负载因子是6.5，Redis数据库当中的负载因子为1或者5，这都是基于语言本身和优化角度来考虑的，所以在真正选择负载因子的时候，尤其是底层设计，不能简单地就取0.75这个数，对于效率追求到极致，就要进行实际的测试来进行负载因子的设定。

  

  
















​	  



















​    

