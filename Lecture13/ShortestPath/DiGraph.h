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