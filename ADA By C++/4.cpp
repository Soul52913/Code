#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector <vector <int>>A, B;
vector <long long> seq;
vector <int> processed;
vector <bool> traversed;

int pN {};
long long total {}, answer {};

void dfs (int p) {
    traversed[p] = true;
    for (int i = 0; i < A[p].size(); ++i) {
        if(!traversed[A[p][i]]) {
            dfs(A[p][i]);
        }
    }
    processed.push_back(p);
    return;
}
void reverseDfs (int p, long long  pp) {
    traversed[p] = true;
    seq[p] = pp;
    for (int i = 0; i < B[p].size(); ++i){
        if(!traversed[B[p][i]]) {
            reverseDfs(B[p][i], pp);
        }
    }
    return;
}
void kosaraju () {
    for (int i = 1; i <= pN; ++i) {
        if (!traversed[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i <= pN; ++i) traversed[i] = false;
    long long pp {};
    for(int i = processed.size() - 1; i >= 0; --i) {
        if (!traversed[seq[i]]) {
            reverseDfs(seq[i], ++pp);
        }
    }
    return pp;
}

int main() {
    int readIn {};
    cin >> pN >> readIn;
    vector <int> temp(2, 0);
    vector <int> tempp;
    for(int i = 0; i <= pN; ++i){
        A.push_back(tempp);
        B.push_back(tempp);
    }
    for(int i = 0; i < readIn; ++i){
        cin >> temp[0] >> temp[1];
        A[temp[0]].push_back(temp[1]);
        B[temp[1]].push_back(temp[0]);
    }
    traversed.resize(pN + 1);
    seq.resize(pN + 1);
    answer = kosaraju();
    cout << answer;
    return 0;
}