#include <stdio.h>

int main(){
    int r, c;
    scanf("%d%d", &r, &c);
    int t[r][c];
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            scanf("%d", &t[i][j]);
        }
    }
    int count = 0;
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if (t[i][j] == 0) continue;
            if (j + 1 < c && t[i][j] == t[i][j + 1]) {
                if (j + 2 < c && t[i][j] == t[i][j + 2]) {
                    t[i][j] = 0, t[i][j + 1] = 0, t[i][j + 2] = 0;
                    j += 2;
                }
                else if (i + 1 < r && t[i][j] == t[i + 1][j + 1]) {
                    t[i][j] = 0, t[i][j + 1] = 0, t[i + 1][j + 1] = 0;
                    ++j;
                }
                else if (i + 1 < r && t[i + 1][j] == t[i][j]) {
                    t[i][j] = 0, t[i][j + 1] = 0, t[i + 1][j] = 0;
                }
            }
            else if (i + 1 < r && t[i + 1][j] == t[i][j]) {
                if (i + 2 < r && t[i + 2][j] == t[i][j]) {
                    t[i][j] = 0, t[i + 1][j] = 0, t[i + 2][j] = 0;
                }
                else if (j + 1 < c && t[i][j] == t[i + 1][j + 1]) {
                    t[i][j] = 0, t[i + 1][j] = 0, t[i + 1][j + 1] = 0;
                }
                else if (j - 1 < c && t[i][j] == t[i + 1][j - 1]) {
                    t[i][j] = 0, t[i + 1][j] = 0, t[i + 1][j - 1] = 0;
                }
            }
        }
    }
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }
    return 0;
}