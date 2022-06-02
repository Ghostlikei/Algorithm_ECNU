#include "allocator.h"
template<typename Type>
class DTable{
public:
    typedef allocator<Type> _Alloc;
    typedef Type* pointer;
    typedef Type* Iterator;
    typedef Type& reference;

protected:
    _Alloc _malloc;
    Iterator start;
    Iterator finish;
    Iterator endOfCapacity;

private:
    float _loadFactor;
    void resize(const size_t& newSize);

public:       
    Iterator begin() { return start; }
    Iterator end() { return finish; }
    size_t size()  { return size_t(end() - begin()); }
    size_t capacity()  { return size_t( endOfCapacity - begin()); }
    bool empty() const { return begin() == end(); }
    reference operator[](size_t index){ return *(begin() + index); }
    reference front(){ return *begin(); }
    reference back(){ return *(end() - 1); }

    DTable();
    ~DTable();
    void setFactor(float fact);
    void push_back(const Type& value);
    void pop_back();

};

template<typename Type>
void DTable<Type>::resize(const size_t& newSize){
    size_t tempSize = size();
    Iterator tempPtr = _malloc.allocate(newSize);
    for(int i = 0; i < tempSize; i++){;
        _malloc.construct(tempPtr + i, start[i]);       
    }

    for(int i = 0; i < tempSize; i++){
        _malloc.destory(start + i);
    }
    _malloc.deallocate(start, newSize);
    start = tempPtr;
    finish = start + tempSize;
    endOfCapacity = start + newSize;

}

template<typename Type>
DTable<Type>::DTable(){
    const size_t default_size = 8;
    _loadFactor = 0.5;
    Iterator _table = _malloc.allocate(default_size);
    start = _table;
    finish = start;
    endOfCapacity = start + default_size;    
}

template<typename Type>
DTable<Type>::~DTable(){
    size_t tempSize = size();
    _malloc._destroy(start, finish);
    // if(start) _malloc.deallocate(start, tempSize);  
}

template<typename Type>
void DTable<Type>::setFactor(float fact){
    _loadFactor = fact;
}

template<typename Type>
void DTable<Type>::push_back(const Type& value){
    if(size() >= capacity()){
        size_t newSize = capacity()*2;
        resize(newSize);
    } 
    _malloc.construct(start + size(), value);
    finish++;
}

template<typename Type>
void DTable<Type>::pop_back(){
    if(capacity() >= 8 && size() < capacity()*_loadFactor*0.5){
        size_t newSize = capacity()/2;
        resize(newSize);
    }
    _malloc.destory(start + size());
    finish--;
}

