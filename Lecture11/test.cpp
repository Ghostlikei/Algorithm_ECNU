#include "DTable.h"

using namespace std;

int main(){

    DTable<DTable<int>> tables;

    for(int i = 0; i < 5; i++){
        DTable<int> t;
        t.setFactor(0.1);
        for(int j = 0; j < 8; j++){
            t.push_back(j);
        }
        tables.push_back(t);
    }

    for(int i = 0; i < 5; i ++){
        for(int j = 0 ; j < 8; j++){
            cout<<tables[i][j]<<endl;

        }
    }
    

}