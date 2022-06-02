#include<vector>
#include<unordered_map>
#include<utility>
#include<algorithm>

using namespace std;

namespace Array{
template<typename Key, typename Value>
class array{
private:
    vector<pair<Key, Value>> table;

public:
    array(){}

    // Keys must be put in order
    void put(Key& key, Value& value){
        
        pair<Key, Value> __pair(key, value);  
        table.push_back(__pair);      
    }

    Value find(int index){
        auto iter = table.begin();
        for(int i = 0; i < index; i++){
            iter++;
        }
        if (iter != table.end()) return iter->second;
        return 0;
    }

};

}