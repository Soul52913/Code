#include <iostream>
#include <vector>

using namespace std;

vector <vector <long long> > discomfortValue;
vector <vector <long long> > Nightmares; //Init Nightmares
vector <vector <int> > Check; //Init Check

void Discomfort (vector <long long> &sleep, int N){
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
    for (int i = 0; i < N; ++i){
        for (int j = i + 1; j < N; ++j){
            long long combineSum = maxToEnd[i][j - 1] + sleep[j];
            discomfortValue[i][j] = max (combineSum, max (discomfortValue[i][j - 1], sleep[j]));
            if (discomfortValue[i][j] == sleep[j]){
                maxToEnd[i][j] = sleep[j];
            }
            else {
                maxToEnd[i][j] = combineSum;
            }
        }
    }
    return;
}

long long MinDiscomfort (int Cut, int end, int N, int K){
    long long minValue = INT64_MAX;
    for (int i = end; i > Cut - 1; --i){
        long long length = (end - i) + 1;
        if (Check[Cut - 1][i - 1] == 0){
            Nightmares[Cut - 1][i - 1] = MinDiscomfort (Cut - 1, i - 1, N, K);
            Check[Cut - 1][i - 1] = 1;
        }
        long long curMin = discomfortValue[i][end] * length + Nightmares[Cut - 1][i - 1];
        if (curMin < minValue) minValue = curMin;
    }
    for (int i = 0; i < K; ++i){
        for (int j = 0; j < N; ++j){
            cout << Nightmares[i][j] << ' ';
        }
        cout << '\n';
    }
    return minValue;
}
//
int main(){
    int N {}, K {};
    cin >> N >> K;
    vector <long long> sleep;
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
    Discomfort (sleep, N);
    /*for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N ; ++j) {
            cout << discomfortValue[i][j] << ' ';
        }
        cout << '\n';
    }cout << '\n';*/
    for (int i = 0; i < K; ++i) {
        vector<long long> vec;
        for (int j = 0; j < N; ++j) {
            vec.push_back(0);
        }
        Nightmares.push_back(vec);
    }
    for (int i = 0; i < K; ++i) {
        vector<int> vec;
        for (int j = 0; j < N; ++j) {
            vec.push_back(0);
        }
        Check.push_back(vec);
    }
    for (int j = 0; j < N; ++j) { //Init first row
        Check[0][j] = 1;
        int length = (j - 0) + 1;
        Nightmares[0][j] = discomfortValue[0][j] * length;
    }
    Nightmares[K - 1][N - 1] = MinDiscomfort (K - 1, N - 1, N, K); //Recusion
    for (int i = 0; i < K; ++i){
        for (int j = 0; j < N; ++j){
            cout << Nightmares[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << Nightmares[K - 1][N - 1]; //Answer
    return 0;
}