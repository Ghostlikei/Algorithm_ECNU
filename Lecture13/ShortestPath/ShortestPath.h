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





