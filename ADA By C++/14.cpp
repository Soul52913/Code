#include <iostream>
#include <vector>

using namespace std;
long long minDiscomfort {};

void Discomfort (vector <long long> &sleep, vector <vector <long long> > &discomfortValue, int N){
    vector <vector <int> > maxToEnd;
    for (int i = 0; i < N; ++i) {
        vector<int> vec;
        for (int j = 0; j < N ; ++j) {
            vec.push_back(0);
        }
        maxToEnd.push_back(vec);
    }
    for (int i = 0; i < N; ++i){
        discomfortValue[i][i] = sleep[i];
        maxToEnd[i][i] = sleep[i];
    }
    for (int l = 2; l <= N; ++l){
        for (int i = 0; i <= N - l; ++i){
            int j = i + l - 1;
            long long combineSum = maxToEnd[i][j - 1] + sleep[j];
            discomfortValue[i][j] = max (combineSum, max (discomfortValue[i][j - 1], sleep[j]));
            if ((discomfortValue[i][j] == combineSum) || (discomfortValue[i][j] == sleep[j])){
                maxToEnd[i][j] = discomfortValue[i][j];
            }
            else {
                maxToEnd[i][j] = combineSum;
            }
        }
    }
    return;
}

void MinDiscomfort (vector <vector <long long> > &discomfortValue, vector <vector <long long> > &Nightmares, vector <vector <int> > &Check, int Cut, int N, int start){
    if (Cut == 0) return;
    for (int i = start; i < N - 1 - Cut; ++i){
        int length = (i - 0) + 1;
        if (Check[Cut - 1][i + 1] == 0){
            MinDiscomfort (discomfortValue, Nightmares, Check, Cut - 1, N, i + 1);
        }
        Nightmares[Cut][i] =  discomfortValue[start][i] * length + Nightmares[Cut - 1][i + 1];
        Check[Cut][i] = 1;
    }
    return;
}
//
int main(){
    int N {}, K {};
    cin >> N >> K;
    vector <long long> sleep;
    vector <vector <long long> > discomfortValue;
    sleep.resize(N);
    for (int i = 0; i < N; ++i){
        cin >> sleep[i];
    }
    for (int i = 0; i < N; ++i) {
        vector<long long> vec;
        for (int j = 0; j < N ; ++j) {
            vec.push_back(0);
        }
        discomfortValue.push_back(vec);
    }
    Discomfort (sleep, discomfortValue, N);
    vector <vector <long long> > Nightmares;
    for (int i = 0; i < K; ++i) {
        vector<long long> vec;
        for (int j = 0; j < N - 1; ++j) {
            vec.push_back(0);
        }
        Nightmares.push_back(vec);
    }
    vector <vector <int> > Check;
    for (int i = 0; i < K; ++i) {
        vector<int> vec;
        for (int j = 0; j < N - 1; ++j) {
            vec.push_back(0);
        }
        Check.push_back(vec);
    }
    for (int j = 0; j < N - 1; ++j) {
        Check[0][j] = 1;
        int length = ((N - 1) - j) + 1;
        Nightmares[0][j] = discomfortValue[j][N - 1] * length;
    }
    MinDiscomfort (discomfortValue, Nightmares, Check, K - 1, N, 0);
    long long ans = INT64_MAX;
    for (int i = 0; i < N - 1 - (K - 1); ++i){
        if (Nightmares[K - 1][i] < ans) ans = Nightmares[K - 1][i];
    }
    //cout << ans;
    for (int i = 0; i < K; ++i){
        for (int j = 0; j < N - 1; ++j){
            cout << Nightmares[i][j] << ' ';
        }
        cout << '\n';
    } 
    return 0;
}