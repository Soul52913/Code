#include <iostream>
#include <vector>

using namespace std;

void Discomfort (vector <long long> &sleep, vector <vector <long long> > &discomfortValue, int N){
    vector <vector <int> > minSequenceEnd;
    for (int i = 0; i < N; ++i) {
        vector<int> vec;
        for (int j = 0; j < N ; ++j) {
            vec.push_back(0);
        }
        minSequenceEnd.push_back(vec);
    }
    for (int i = 0; i < N; ++i){
        discomfortValue[i][i] = sleep[i];
        minSequenceEnd[i][i] = i;
    }
    for (int l = 2; l <= N; ++l){
        for (int i = 0; i <= N - l; ++i){
            int j = i + l - 1;
            long long combineSum {INT64_MAX};
            if (minSequenceEnd[i][j - 1] == (j - 1)) combineSum = discomfortValue[i][j - 1] + sleep[j];
            discomfortValue[i][j] = min (combineSum, min (discomfortValue[i][j - 1], sleep[j]));
            if (((minSequenceEnd[i][j - 1] == (j - 1)) && (discomfortValue[i][j] == combineSum)) || (discomfortValue[i][j] == sleep[j])){
                minSequenceEnd[i][j] = j;
            }
        }
    }
    return;
}

long long MinDiscomfort (vector <long long> &sleep, vector <vector <long long> > &discomfortValue){
    long long minDiscomfort {};
    return minDiscomfort;
}

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
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cout << discomfortValue[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}