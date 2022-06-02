# **华东师范大学数据科学与工程学院上机实践报告**

***

课程名称：算法设计与分析      

上机实验名称：单源最短路径算法  

编号：No.13

年级：21级        

日期：2022年5月30号

***

## 1.实验目的

- 本实验主要实现以下两种算法：
  - Bellman-Ford算法
  - Dijkstra算法

## 2. 算法思路

- 报告中主要讲讲这两个算法的实现，至于其余数据结构的实现会在总结过后提出，包括提交oj的代码，因为和算法的核心没有多大关系，所以前面就省略了

### 2.1 Bellman-Ford

Bellman-Ford算法是解决单源最短路径的一种，具体的流程和证明上课已经讲的很详细了，我认为这个算法的本质其实是一种“巧妙的穷举”，通过最多二次的时间内就可以解决问题的遍历，在（v-1）次遍历之后，通过收敛性和路径松弛的最小路径“扩张”来实现整个算法（不用在意这个描述，只是个人对于算法的理解，具体内容课上都有）

下面来看看这个算法的实现

- 前置定义，后面的Dijkstra是通用的

```cpp
static const int NIL = INT16_MIN;
static const int INF = INT16_MAX;

int shortestPath = -1;
```

- 算法内容

```cpp
//@params: graph输入图， s是源, final是目标位置，可以不加
bool Bellman_Ford(Graph& graph, size_t s, size_t final){
    // 获得V和E的个数
    static const size_t V = graph.vertices();
    static const size_t E = graph.edges();

    //获得所有的有向边
    vector<Edge> edges = graph.allEdges();

    //建立点的距离容器和前驱容器
    vector<int> distance;
    vector<int> from;

    // 初始化
    for(int i = 0; i < V; i++){
        distance.push_back(INF);
        from.push_back(NIL);
    }

    distance[s] = 0;

    // 路径松弛操作
    // 第一层v-1次遍历
    for(int i = 1; i <= V - 1; i++){
        // 第二层遍历所有顶点
        for(int j = 0; j < E; j++){
            // 获得边和起点，终点
            Edge curEdge(edges[j]);
            size_t u = curEdge.from();
            size_t v = curEdge.to();
            
            // 路径松弛
            if(distance[v] > distance[u] + curEdge.weight() ){
                distance[v] = distance[u] + curEdge.weight();
                from[v] = u;
            }
        }
    }

	// 判断有没有负环路
    for(int j = 0; j < E; j++){
        Edge curEdge(edges[j]);
        size_t u = curEdge.from();
        size_t v = curEdge.to();
        if(distance[v] > distance[u] + curEdge.weight()){
            return false;
        }
    }

    //判断是不是连接到源点
    if(distance[final] == INF) return false;
    
    //记录结果
    shortestPath = distance[final];
    return true;
}
```



### 2.2 Dijkstra

同样具体证明和算法不再重复，个人理解Dijkstra是一种类似于贪心算法的最短路径算法，特点是判断的参数是**和源点的距离**，这是区别于其他运用贪心的最短路径算法的地方

- 算法内容

```cpp
bool Dijkstra(Graph graph, size_t s, size_t final){
    size_t V = graph.vertices();

    vector<Edge> edges = graph.allEdges();

    vector<int> distance;
    vector<int> from;
    vector<Edge> searched;

    for(int i = 0; i < V; i++){
        distance.push_back(INF);
        from.push_back(NIL);
    }

    distance[s] = 0;
    // 和前面一样的初始化

    // 用一下std::pq,这里用Edge作为typename必须要重载比较函数，或者新写一个比较函数
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    for(auto edge : graph.getEdges(s)){
        pq.push(edge);
    }// 先把源点连的所有边放进去

    while (!pq.empty()){
        Edge min(pq.top());// 拿出最小的边
        pq.pop();
        searched.push_back(min);// 记录一下已经搜过了的边

        size_t u = min.from();

        // 找新点的所有边，放进优先队列里
        for(auto edge : graph.getEdges(u)){
            size_t v = edge.to();
            for(auto edge : graph.getEdges(v)){
                pq.push(edge);
            }
            // 路径松弛
            if(distance[v] > distance[u] + edge.weight() ){
                distance[v] = distance[u] + edge.weight();
                from[v] = u;
            }
        }
    }

    // 和前面一样
    if(distance[final] == INF) return false;
    shortestPath = distance[final];
    return true;

}
```



## 3.算法分析

- 时间复杂度

  Bellman-Ford算法的时间复杂度很明显，是通过两层遍历来得出的，也就是(v-1)*e，$\Theta(nm)$

  Dijkstra算法取决于while循环，这里由于使用的最小堆的实现方法，而pop方法的复杂度是O(logn)，由于记录数组的存在，最多进行v次，这里需要注意的就是书上的decrease-key的存在，由于本次是采用了**空间换时间**的做法，也就是再放入to()是相同的边的时候没有进行缩小操作，所以没有decrease-key的存在；但是实际上也可以写一下这个操作，只要在优先队列**找到这个点 **O1 ，改变这个值，然后实现pq里的**swim()** O(logn) 这一步，就可以完成，所以总体上还是O(mlogn)



- 优缺点和应用场景

  BF的优点就是能处理负环路，能实现负权重图的最短路径查找，缺点就是二次时间的“穷举”，效率不高

  Dijkstra是应对无负权重图的最短路径查找的，相比于BF，时间复杂度更好，(在这里讨论负环路没法处理是不是缺点没有意义，因为这个算法不是为了这个而生的），个人觉得缺点是这个算法**只看到了和源点之间的距离**，在处理**单源到所有点**的时候优势很大，但是处理**单源到单点**的时候，尤其是一些极端情况会显得不够好，因为会有一些极端情况出现，比如一片区域到另一片只有一段边连接这种，不如其他的一些特定算法有优势。



## 4.总结

- 本次实验实现了两种非常经典的单源最短路径算法，总体上还是顺利的
- 由于优点队列在之前的实验课中有实现，这里就不再重复劳动了，直接调用泛用性更好的std::pq，更加安全而且时间消耗更少
- 线性表和斐波那契堆也是实现Dijkstra的结构，但是由于不在要求内而且时间原因就不再实现了，如果要用只需要替换其中的pq即可，



## 5.源码

不再提供注释，应该写的比较清楚了

- DiEdge.h

没有重载赋值运算符，注意后面不能用，使用的时候用拷贝构造

```cpp
class Edge{
private:
    size_t _from;
    size_t _to;
    int _weight;

public:
    Edge() = default;
    Edge(size_t from, size_t to, int weight): _from(from), _to(to), _weight(weight) { }

    Edge(const Edge& that){
        _from = that.from();
        _to = that.to();
        _weight = that.weight();
    }


    size_t from() const{
        return _from;
    }

    size_t to() const{
        return _to;
    }

    int weight() const{
        return _weight;
    }

    bool operator>(Edge rhs) const{
        return weight() > rhs.weight();
    }

    bool operator<(Edge rhs) const{
        return weight() < rhs.weight();
    }

    bool operator>=(Edge rhs) const{
        return weight() >= rhs.weight();
    }

    bool operator<=(Edge rhs) const{
        return weight() <= rhs.weight();
    }
};
```

- DiGraph.h

```cpp
#include "DiEdge.h"
#include<vector>
#include<list>

using std::vector; using std::list;

class Graph{
private:
    size_t _vertices;
    size_t _edges;
    vector<list<Edge>> adj;

public:
    Graph() = default;
    Graph(size_t v){
        _vertices = v;
        for(int i = 0; i < _vertices; i++){
            list<Edge> tempList;
            adj.push_back(tempList);
        }
        _edges = 0;
    }

    Graph(Graph& other){
        adj = other.adj;
        _vertices = other.vertices();
        _edges = other.edges();
    }

    void addEdge(const size_t from, const size_t to, const int length){
        Edge temp(from, to, length);
        adj[from].emplace_back(temp);
        _edges++;
    }

    void addEdge(const Edge& e){
        size_t from = e.from();
        adj[from].emplace_back(e);
        _edges++;
    }

    list<Edge> getEdges(size_t v){
        return adj[v];
    }

    vector<Edge> allEdges(){
        vector<Edge> edges;
        for(int i = 0; i <vertices(); i++){
            for(auto edge : adj[i]){
                edges.push_back(edge);
            }
        }

        return edges;
    }

    size_t vertices() const{
        return _vertices;
    }

    size_t edges() const{
        return _edges;
    }

};
```

- ShortestPath.h

```cpp
#include "DiGraph.h"
#include<queue>

static const int NIL = INT16_MIN;
static const int INF = INT16_MAX;

int shortestPath = -1;

bool Bellman_Ford(Graph& graph, size_t s, size_t final){
    size_t V = graph.vertices();
    size_t E = graph.edges();

    vector<Edge> edges = graph.allEdges();

    vector<int> distance;
    vector<int> from;

    for(int i = 0; i < V; i++){
        distance.push_back(INF);
        from.push_back(NIL);
    }

    distance[s] = 0;

    for(int i = 1; i <= V - 1; i++){
        for(int j = 0; j < E; j++){
            Edge curEdge(edges[j]);
            size_t u = curEdge.from();
            size_t v = curEdge.to();
            if(distance[v] > distance[u] + curEdge.weight() ){
                distance[v] = distance[u] + curEdge.weight();
                from[v] = u;
            }
        }
    }


    for(int j = 0; j < E; j++){
        Edge curEdge(edges[j]);
        size_t u = curEdge.from();
        size_t v = curEdge.to();


        if(distance[v] > distance[u] + curEdge.weight()){
            return false;
        }


    }

    if(distance[final] == INF) return false;
    shortestPath = distance[final];

    return true;


}

// @deprecated
auto cmp = [](Edge lhs, Edge rhs){
    return lhs < rhs;
};

bool Dijkstra(Graph graph, size_t s, size_t final){
    size_t V = graph.vertices();

    vector<Edge> edges = graph.allEdges();

    vector<int> distance;
    vector<int> from;
    vector<Edge> searched;

    for(int i = 0; i < V; i++){
        distance.push_back(INF);
        from.push_back(NIL);
    }

    distance[s] = 0;

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    for(auto edge : graph.getEdges(s)){
        pq.push(edge);
    }

    while (!pq.empty()){
        Edge min(pq.top());
        pq.pop();
        searched.push_back(min);

        size_t u = min.from();

        for(auto edge : graph.getEdges(u)){
            size_t v = edge.to();
            for(auto edge : graph.getEdges(v)){
                pq.push(edge);
            }
            if(distance[v] > distance[u] + edge.weight() ){
                distance[v] = distance[u] + edge.weight();
                from[v] = u;
            }
        }
    }

    if(distance[final] == INF) return false;
    shortestPath = distance[final];
    return true;

}
```

- main.cpp

提交oj的代码，要手动include一下

```cpp
#include "ShortestPath.h"
#include<iostream>
using namespace std;

int main(){
    size_t v;
    size_t e;
    cin>>v>>e;
    Graph graph(v);
    for(int i = 0; i < e; i++){
        size_t x,y;
        int z;
        cin>>x>>y>>z;
        Edge temp(x-1,y-1,z);
        graph.addEdge(temp);
    }

    bool result = Dijkstra(graph, 0, v-1);
    if(result) cout<<shortestPath<<endl;
    else cout<<"-1"<<endl;
}
```
















​	  



















​    

