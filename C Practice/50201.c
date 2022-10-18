#include <stdio.h>
#include <stdlib.h>

int main(){
    int r, c;
    scanf("%d%d", &r, &c);
    int t[r][c];
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            scanf("%d", &t[i][j]);
        }
    }
    int ty, k, rs = 0, re = r - 1, cs = 0, ce = c - 1;
    while (scanf("%d%d", &ty, &k) != EOF) {int tk = k;
        if (ty == 1){
            for (int i = rs; i <= rs + tk - 1; ++i){
                for (int j = cs; j <= ce; ++j){
                    t[i + (2 * k - 1)][j] += t[i][j];
                    t[i][j] = 0;
                }
                --k;
            }
            rs += tk;
        }
        else if (ty == 2) {
            for (int j = ce; j >= ce - tk + 1; --j){
                for (int i = rs; i <= re; ++i){
                    t[i][j - (2 * k - 1)] += t[i][j];
                    t[i][j] = 0;
                }
                k--;
            }
            ce -= tk;
        }
        else{--tk;
            int cone = ce - tk, ctwo = rs + tk, count = 0;
            for(int i = rs; i <= re + tk - 1; ++i){
                for (int j = ce - tk + count + 1; j <= ce; ++j){
                    int dtwo = j - (ce - tk + count);
                    t[i + dtwo][ce - tk + count] += t[i][j];
                    t[i][j] = 0;
                }
                ++count;
            }
        }
    }
    for(int i = rs; i <= re; ++i){
        for(int j = cs; j <= ce; ++j){
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }
    return 0;
}