#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void put(vector <long long> &S, vector <long long> &sum){
    long long in {}, pop {};
    cin >> in;
    pop = sum[sum.size() - 1];
    S.push_back(in);
    in += pop;
    sum.push_back(in);
    return;
}

void take(vector <long long> &S, vector <long long> &sum){
    cout << S[S.size() - 1] << endl;
    S.pop_back();
    sum.pop_back();
    return;
}

void cc (vector <long long> &S, vector <long long> &sum){
    vector <long long> takeOut, sorted;
    long long x {}, k{}, top {}, min {}, add {};
    cin >> x >> k;
    for (int i = 0; i < x; ++i){
        top = S[S.size() - 1];
        takeOut.push_back(top);
        sorted.push_back(top);
        S.pop_back();
        sum.pop_back();
    }
    if (x % k == 0) k = x / k;
    else k = x / k + 1;
    sort(sorted.begin(), sorted.end());
    int a = sorted.size() - 1, b = sorted.size() - k;
    for(int i = a; i >= b; i--){
        add += sorted[i];
        if (i == sorted.size() - k) min = sorted[i];
    }
    for(int i = takeOut.size() - 1; i >= 0 ; --i){
        if (takeOut[i] < min){
            long long pop {}, in {takeOut[i]};
            pop = sum[sum.size() - 1];
            S.push_back(in);
            in += pop;
            sum.push_back(in);
        }
    }
    cout << add << endl;
    return;
}

void dd (vector <long long> &S, vector <long long> &sum){
    int x {};
    cin >> x;
    cout << sum[sum.size() - 1] - sum[sum.size() - x - 1] << endl;
    return;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int M {};
    cin >> M;
    vector <long long> S, sum;
    sum.push_back(0);
    for (int i = 0; i < M; ++i){
        string cmd;
        cin >> cmd;
        if (cmd == "PUT"){
            put(S, sum);
        }
        else if (cmd == "TAKE"){
            take(S, sum);
        }
        else if (cmd == "CC"){
            cc(S, sum);
        }
        else if (cmd == "DD"){
            dd(S, sum);
        }
    }
    return 0;
}