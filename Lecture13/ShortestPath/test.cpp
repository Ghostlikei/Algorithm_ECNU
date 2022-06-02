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
//    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
//    Edge e(1, 2, 3);
//    Edge f(4, 5, 6);
//    pq.push(e);
//    pq.push(f);
//
//    cout<<pq.top().weight()<<endl;
}