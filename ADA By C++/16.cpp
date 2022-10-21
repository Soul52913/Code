#include <iostream>
#include <vector>
#include <string>

using namespace std;

int minDistance(string x, string y) {
    int xLen = x.size(), yLen = y.size();
    vector< vector<int>> dp(xLen + 1, vector<int>(yLen + 1, 0));
    for (int i = 0; i < xLen + 1; ++i) {
        for (int j = 0; j < yLen + 1; ++j) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (x[i - 1] == y[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = min (dp[i - 1][j - 1], min (dp[i - 1][j], dp[i][j - 1])) + 1;
        }
    }
    return dp[xLen][yLen];
}
int main(){
    string A;
    cin >> A;
    cout << minDistance(A);
    return 0;
}
