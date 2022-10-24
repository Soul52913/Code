#include <iostream>
#include <vector>

using namespace std;

long long Picture (int N, int K, long long M, vector< vector <vector <int> >> &tower){
    for (int k = 1; k <= K; k++){
        for (int i = 0; i <= N; i++){
            for (int j = 0; j <= N; j++){
                
            }
        }
    }
    return 0;
}

int main(){
    int N {}, K {};
    long long M{};
    cin >> N >> K >> M;
    vector< vector <vector <int> >> tower (11, vector < vector <int>>((N + 1), vector <int> (N + 1)));
    Picture (N, K, M, tower);
    for (int a = 1; a <= K; ++a){
        for (int b = 1; b <= N; ++b){
            cout << tower[a][b] << ' '; 
        }
        cout << endl;
    }
    return 0;
}