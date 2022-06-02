#include<list>
#include<vector>
#include<utility>
#include<functional> 

using namespace std;

namespace Hashtable{

template<typename Key, typename Value>
class HashTable{
private:

    size_t size;
    vector<list<pair<Key, Value>>> table;

    size_t hashCode(const Key& key){
        hash<Key> hashFunction;
        size_t result = hashFunction(key);
        return result % size;
    }
public:
    HashTable<Key, Value>(int tableSize){
        list<pair<Key, Value>> alist;
        for(int i = 0; i < tableSize; i++){
            table.push_back(alist);
        }
        size = tableSize;
    }

    void put(Key& key, Value& value){
        size_t index = hashCode(key);
        pair<Key, Value> tempPair(key, value);
        table[index].emplace_back(tempPair);
    }

    Value find(Key& key){
        size_t index = hashCode(key);
        auto iter = table[index].begin();
        while(iter != table[index].end()){
            if((*iter).first == key) return (*iter).second;
            iter++;
        } 
        return 0;
    }

    size_t getSize(){return size;}
};

}