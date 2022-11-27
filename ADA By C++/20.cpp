#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N {}, M {};

struct Tree {
    int parent;
    long long c;
    long long d;
    vector <int> child;
};

vector <Tree> forest;
vector <int> roots;
vector <vector <int>> dp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
	forest.resize(N);
    vector <int> temp (N, 0);
    for (int i = 0; i <= M; ++i){
        dp.push_back(temp);
    }
    Tree tree;
    for(int i = 0; i < M; ++i){
        cin >> forest[i].parent;
        if (forest[i].parent == -1)
            roots.push_back(i);
    }
    for(int i = 0; i < M; ++i){
        cin >> forest[i].c >> forest[i].d;
    }
    
	return 0;
}