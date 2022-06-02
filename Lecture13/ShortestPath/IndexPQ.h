#include<vector>
#include<ios>

using std::vector;

namespace IndexPQ{
    template<typename Type>
    class PQ{
    public:
        typedef Type& reference;
        typedef size_t index;

    private:
        size_t _max;
        size_t _number;
        vector<index> _Heap;
        vector<int> _revHeap;
        vector<Type> _keys;

    public:
        PQ(size_t max){
            _max = max;
            _number = 0;
            for(int i = 0; i < max+1; i++){
                _Heap.push_back(0);
                _revHeap.push_back(-1);
                _keys.push_back(0);
            }
        }

        size_t size(){
            return _number;
        }

        void insert(index i, const Type& key){
            _number++;
            _revHeap[i] = _number;
            _Heap[_number] = i;
            _keys[i] = key;
            swim(_number);
        }

        reference min(){
            return _keys[_Heap[1]];
        }

        index pop(){
            index min = _Heap[1];
            swap(1, _number--);
            sink(1);

            _revHeap[min] = -1;
            return min;
        }

        reference operator[](index i){
            return _keys[i];
        }

        void changeKey(index i, Type key){
            _keys[i] = key;
            swim(_revHeap[i]);
            sink(_revHeap[i]);
        }

        void increaseKey(index i, Type key){
            _keys[i] = key;
            swim(_revHeap[i]);
        }

        void decreaseKey(index i, Type key){
            _keys[i] = key;
            sink(_revHeap[i]);
        }

    private:
        void swap(index i, index j){
            index temp = _Heap[i];
            _Heap[i] = _Heap[j];
            _Heap[j] = temp;
            _revHeap[_Heap[i]] = i;
            _revHeap[_Heap[j]] = j;
        }

        void swim(index i){
            while (i > 1 && i/2 < i){
                swap(i, i/2);
                i /= 2;
            }
        }

        void sink(index k){
            while (2*k < _number){
                index j = 2*k;
                if (j < _number) j++;
                if (k >= j) break;
                swap(k, j);
                k = j;
            }
        }
    };


}
