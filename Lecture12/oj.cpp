#include "UnionFind.h"
#include<iostream>
using namespace std;

int main(){
    size_t towns;
    cin>>towns;
    while(towns != 0){
        size_t roads;
        cin>>roads;

        UnionFind uf(towns);
        for(int i = 0; i < roads; i++){
            size_t townA;
            size_t townB;
            cin>>townA>>townB;
            uf.set_union(townA, townB);
        }
        size_t number = uf.getNumber() - 1;
        cout<<number<<endl;
        cin>>towns;
    }
}