#include<iostream>
#include<vector>

using namespace std;

class TSP{
public:
    typedef vector<vector<int>> Graph;
    static const int INF = INT32_MAX;
    static const int NIL = 0;
private:
    Graph graph;
    vector<vector<int>> dp;
    size_t _size;
    int solution;

public:
    TSP() = default;
    TSP(size_t size1, istream& in){
        _size = size1;

        for(int i = 0; i < _size; i++){
            vector<int> edges;
            vector<int> nullvec(1 << (_size - 1));
            for(int j = 0; j < _size; j++){
                int temp;
                in>>temp;
                edges.push_back(temp);
            }
            graph.push_back(edges);
            dp.push_back(nullvec);
        }

    }

    size_t size() const{
        return _size;
    }

    void solve(){
        for(int i = 0; i < size(); i++){
            dp[i][0] = graph[i][0];
        }

        for(int i = 1; i < (1 << (size() - 1)); i++){
            for(int j = 0; j < size(); j++){
                dp[j][i] = INF;
                //node j not visited
                if( ((i >> (j - 1)) & 1) == 0){
                    for(int k = 1; k < size(); k++){
                        // k in j set
                        if(((i >> (k - 1)) & 1) != 0){
                            if(dp[j][i] > graph[j][k] + dp[k][i - (1 << (k-1))]){
                                dp[j][i] = graph[j][k] + dp[k][i - (1 << (k-1))];
                            }
                        }
                    }
                }
            }
        }

        solution = dp[0][(1 << (size()-1)) - 1];
    }

    int result() const{
        return solution;
    }
};

int main(){
    int n;
    cin>>n;
    TSP tsp(n, cin);
    tsp.solve();
    cout<<tsp.result()<<endl;
}
