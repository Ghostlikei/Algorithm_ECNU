#include<vector>
#include<algorithm>

using namespace std;

class UnionFind{
private:
    vector<size_t> _root;
    vector<size_t> _size;
    size_t number_of_sets;

    size_t findRoot(const size_t& item){
        size_t temp = item - 1;
        while(temp != _root[temp]){
            temp = _root[temp];
        }    
        return temp;        
    }

public:
    UnionFind(const size_t& size){
        for(size_t i = 0; i < size; i++){
            _root.push_back(i);
            _size.push_back(1);
        }
        number_of_sets = size;
    }

    bool connected(const size_t& lhs, const size_t& rhs){
        return findRoot(lhs) == findRoot(rhs);
    }

    size_t getNumber(){
        return number_of_sets;
    }

    size_t getSize(const size_t& index){
        return _size[findRoot(index)];
    }

    void set_union(const size_t& lhs, const size_t& rhs){
        size_t Lroot = findRoot(lhs);
        size_t Rroot = findRoot(rhs);

        if(findRoot(lhs) != findRoot(rhs)) number_of_sets--;
        _root[Lroot] = Rroot;
        _size[Rroot] += _size[Lroot];
        
    }
};