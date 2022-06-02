#include<iostream>

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