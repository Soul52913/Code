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
    long long subTreeC;
    int nodeNum;
    vector <int> child;
};

vector <Tree> forest;
vector <int> roots;
vector <int> seq;
vector <vector <long long>> dp;

void dfs (int index) {
    long long totalC = forest[index].c;
    int totalNode = 1;
    for (int i = 0; i < forest[index].child.size(); ++i){
        dfs(forest[index].child[i]);
        totalC += forest[forest[index].child[i]].subTreeC;
        totalNode += forest[forest[index].child[i]].nodeNum;
    }
    forest[index].subTreeC = totalC;
    forest[index].nodeNum = totalNode;
    seq.push_back(index);
    return;
}

void dpING () {
    for (int i = 0; i <= M; ++i) {
        int index = seq[0];
        if(i >= forest[index].c || i >= forest[index].d)
            dp[index][i] = forest[index].c;
    }
    for(int i = 1; i < seq.size(); ++i) {
        int index = seq[i];
        int prev = seq[i - 1];
        for (int j = 0; j <= M; ++j) {
            dp[index][j] = dp[prev][j];
            long long left = 0;
            if(j >= forest[index].c) {
                left = j - forest[index].c;
                if (forest[index].c + dp[prev][left] > dp[index][j]){
                    dp[index][j] = forest[index].c + dp[prev][left];
                }
            }
            if(j >= forest[index].d) {
                left = j - forest[index].d;
                long long dpleft = 0;
                if (i - forest[index].nodeNum >= 0)
                    dpleft = dp[seq[i - forest[index].nodeNum]][left];
                if (forest[index].subTreeC + dpleft > dp[index][j]){
                    dp[index][j] = forest[index].subTreeC + dpleft;
                }
            }
        }
    }
    return;
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    cin >> N >> M;
    forest.resize(N);
    vector <long long> temp (M + 1, 0);
    for (int i = 0; i < N; ++i)
        dp.push_back(temp);
    for(int i = 0; i < M; ++i){
        cin >> forest[i].parent;
        if (forest[i].parent == -1)
            roots.push_back(i);
        else
            forest[forest[i].parent].child.push_back(i);
    }
    for(int i = 0; i < M; ++i){
        cin >> forest[i].c >> forest[i].d;
    }
    for (int i = 0; i < roots.size(); ++i){
        dfs(roots[i]);
    }
    dpING();
    //for (auto next : forest) cout << next.nodeNum;
    for(int i = 0; i < seq.size(); ++i){
        int index = seq[i];
        for(int j = 0; j <= M; ++j){
            cout << dp[index][j] << " ";
        }cout << endl;
    }
    cout << dp[seq[(seq.size() - 1)]][M];
	return 0;
}