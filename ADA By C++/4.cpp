#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

struct Point {
  vector <int> A;
  vector <int> revA;
};

stack <int> S;
vector <bool> traversed;
vector<Point> B;
int pN {};
long long total {}, answer {};

void dfs (int p) {
    traversed[p] = true;
    for (int i = 0; i < B[p].A.size(); ++i) {
        if(!traversed[B[p].A[i]]) {
            dfs(B[p].A[i]);
        }
    }
    S.push(p);
    return;
}
void reverseDfs (int p) {
    traversed[p] = true;
    ++total;
    for (int i = 0; i < B[p].revA.size(); ++i){
        if(!traversed[B[p].revA[i]]) {
            reverseDfs(B[p].revA[i]);
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
    B.resize(pN + 1);
    for(int i = 0; i < readIn; ++i){
        cin >> temp[0] >> temp[1];
        B[temp[0]].A.push_back(temp[1]);
        B[temp[1]].revA.push_back(temp[0]);
    }
    traversed.resize(pN + 1);
    kosaraju();
    cout << answer;
    return 0;
}