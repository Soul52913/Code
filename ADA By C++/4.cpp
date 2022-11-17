#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;
vector <vector <int>>A, B;
stack <int> S;
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
    S.push(p);
    return;
}
void reverseDfs (int p) {
    traversed[p] = true;
    ++total;
    for (int i = 0; i < B[p].size(); ++i){
        if(!traversed[B[p][i]]) {
            reverseDfs(B[p][i]);
        }
    }
    return;
}
void kosaraju () {
    for (int i = 0; i < pN; ++i) {
        if (!traversed[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < pN; ++i) traversed[i] = false;

    while (!S.empty()){
        int i = S.top();
        S.pop();
        if (!traversed[i]) {
            total = 0;
            reverseDfs(i);
            if (total >= 2)
                answer += (total * (total - 1) / 2);
        }
    }
    return;
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
    traversed.resize(pN);
    kosaraju();
    cout << answer;
    return 0;
}