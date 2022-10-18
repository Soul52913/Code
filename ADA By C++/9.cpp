#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mine (int W, vector<int> &a, vector<int> &b, int i, int left){
    b.push_back(left);
    for (auto &j : a){
        if (i - j < 0) break;
        else{
            if (b[i - j] < b[i]) b[i] = b[i - j];
        }
    }
    return;
}

int zck (int left, vector<int> &a, int N){
    for (int i = N - 1; i >= 0; --i){
        left = left % a[i];
    }
    return left;
}

int main(){
    int N, W;
    cin >> N >> W;
    vector <int> a, b;
    a.resize(N), b.push_back(0);
    for (int i = 0; i < N; ++i) cin >> a[i];
    int z {}, m {};
    sort(a.begin(), a.end());
    for (int i = 1; i <= W; ++i){
        z = zck(i, a, N);
        mine(W, a, b, i, z);
        cout << z - b[i] << '\n';
    }
    //for (auto &i : a) cout << i << '\n';
    return 0;
}