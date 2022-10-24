#include <iostream>
#include <vector>

using namespace std;

long long Picture (int N, int K, long long M, vector <vector <long long> > &preStep, vector <vector <long long> > &curStep){
    for (int i = 0; i <= K; ++i){
        preStep[i][i] = 1;
    }
    for (int n = 1; n <= N; ++n){
        for (int l = K; l >= 0; --l){
            long long accumulate {};
            for (int k = 0; k <= K - l; ++k){
                int h = k + l;
                accumulate = (accumulate + preStep[h][k] >= M)? accumulate + preStep[h][k] - M: accumulate + preStep[h][k];
                curStep[h][k] = (accumulate + curStep[h][k] >= M)? accumulate + curStep[h][k] - M: accumulate + curStep[h][k];
            }
        }
        for (int l = 1; l <= K; ++l){
            long long accumulate {};
            for (int h = 0; h <= K - l; ++h){
                int k = h + l;
                accumulate = (accumulate + preStep[h][k] >= M)? accumulate + preStep[h][k] - M: accumulate + preStep[h][k];
                curStep[h][k] = (accumulate + curStep[h][k] >= M)? accumulate + curStep[h][k] - M: accumulate + curStep[h][k];
            }
        }
        for (int k = 0; k <= K; ++k){
            long long accumulate {};
            for (int h = K; h > 0; --h){
                accumulate = (accumulate + preStep[h][k] >= M)? accumulate + preStep[h][k] - M: accumulate + preStep[h][k];
                curStep[h - 1][k] = (accumulate + curStep[h - 1][k] >= M)? accumulate + curStep[h - 1][k] - M: accumulate + curStep[h - 1][k];
            }
        }
        for (int h = 0; h <= K; ++h){
            for (int k = 0; k <= K; ++k){
                preStep[h][k] = curStep[h][k];
                curStep[h][k] = 0;
            }
        }/*
        for (int h = 0; h <= K; ++h){
            for (int k = 0; k <= K; ++k){
                cout << preStep[h][k] << ' ';
            }
            cout << endl;
        }cout << endl; */ 
    }
    long long ans {};
    for (int k = 0; k <= K; ++k) ans = (ans + preStep[0][k] >= M)? ans + preStep[0][k] - M: ans + preStep[0][k];
    return ans;
}

int main(){
    int N {}, K {};
    long long M{};
    cin >> N >> K >> M;
    vector <vector <long long> > preStep ((K + 1), vector <long long> (K + 1));
    vector <vector <long long> > curStep ((K + 1), vector <long long> (K + 1));
    cout << Picture (N, K, M, preStep, curStep);
    return 0;
}