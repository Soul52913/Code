#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector <int> fenwick, symbol;
vector <char> symbolReverse;
int N;

void frontPlusOne(int pos) {
    ++pos; // start from 1
    while (pos < fenwick.size()) {
        ++fenwick[pos];
        pos += pos & -pos;
    }
    return;
}

int fenwickGet(int pos) {
    ++pos; // start from 1
    int moved {};
    while (pos > 0) {
        moved += fenwick[pos];
        pos -= pos & -pos;
    }
    return moved;
}

void strangestStr(string x, string &y, long long moveValid) {
    N = x.size();
    vector< queue <int>> charQueue;
    for (int i = 0; i < 65; ++i){
        queue <int> temp;
        charQueue.push_back(temp);
    }
    fenwick.resize(N + 1); 
    vector< int> swapped (N);
    for (int i = 0; i < N; ++i) {charQueue[symbol[(int)x[i]]].push(i);}
    while (moveValid > 0 && y.size() < N){
        for (int i = 0; i < 65; ++i){
            if (charQueue[i].empty()) continue;
            int cur = charQueue[i].front();
            long long moveNeeded = cur - fenwickGet(cur - 1);
            if (moveNeeded <= moveValid){
                moveValid -= moveNeeded;
                y.push_back(symbolReverse[i]);
                frontPlusOne (cur);
                swapped[cur] = 1;
                charQueue[i].pop();
                break;
            }
        }
    }
    for (int i = 0; i < N; ++i){
        if (swapped[i] == 0) y.push_back(x[i]);
    }
    return;
}
int main(){
    string A, B;
    symbol.resize(130);
    symbolReverse.resize(65);
    int seq = 0;
    for (int i = '0'; i <= '9'; ++i, ++seq) {symbol[i] = seq; symbolReverse[seq] = (char)i;}
    for (int i = 'A'; i <= 'Z'; ++i, ++seq) {symbol[i] = seq; symbolReverse[seq] = (char)i;}
    for (int i = 'a'; i <= 'z'; ++i, ++seq) {symbol[i] = seq; symbolReverse[seq] = (char)i;}
    long long moveValid;
    cin >> A >> moveValid;
    strangestStr(A, B, moveValid);
    cout << B;
    return 0;
}
