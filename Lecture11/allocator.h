#include<iostream>
template<typename Type>
class allocator{
public:
    allocator() = default;
    Type* allocate(size_t size){
        return static_cast<Type*>(operator new(sizeof(Type) * size));
    }

    void deallocate(Type* ptr, size_t size){
        ::operator delete(ptr);
    }

    void construct(Type* ptr, const Type& value){
        new (ptr) Type(value);
    }

    void destory(Type* ptr){
        ptr->~Type();
    }

    void _destroy(Type* firstIterator, Type* lastIterator){
        for(; firstIterator < lastIterator; firstIterator++){
            destory(&*firstIterator);
        }
    }
};
