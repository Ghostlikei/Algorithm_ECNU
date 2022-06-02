#include<ios>
#include<vector>
#include<list>

using namespace std;

class Graph{
private:
    size_t vertices;
    vector<list<size_t>> _bag;

public:
    Graph(size_t v){
        vertices = v;
        for(int i = 0; i < vertices; i++){
            list<size_t> _temp;
            _bag.push_back(_temp);
        }

    }

    Graph& addEdge(size_t lhs, size_t rhs){
        _bag[lhs].emplace_back(rhs);
        _bag[rhs].emplace_back(lhs);
    }

};