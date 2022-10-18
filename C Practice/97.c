#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int parks[n][4];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            parks[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        scanf("%d%d%d", &parks[i][0], &parks[i][1], &parks[i][2]);
    }
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        int x = 0, y = 0, comp[n][2];
        scanf("%d%d", &x, &y);
        for (int j = 0; j < n; j++){
            int dist = 0;
            dist += (x - parks[j][0] > 0) ? x - parks[j][0] : parks[j][0] - x;
            dist += (y - parks[j][1] > 0) ? y - parks[j][1] : parks[j][1] - y;
            comp[j][0] = j, comp[j][1] = dist;
        }
        int key = 0, num = 0, k = 0;//for (int s = 0; s < n; s++){printf("%d %d\n", comp[s][0], comp[s][1]);}
        for (int j = 1; j < n; j++) {
            num = comp[j][0], key = comp[j][1];
            k = j - 1;
            while (k >= 0 && comp[k][1] >= key) {
                if (comp[k][1] == key){
                    if (parks[comp[k][0]][0] > parks[num][0]){
                        comp[k + 1][0] = comp[k][0];
                        comp[k + 1][1] = comp[k][1];
                    }
                    else if (parks[comp[k][0]][0] == parks[num][0]){
                        if (parks[comp[k][0]][1] > parks[num][1]){
                            comp[k + 1][0] = comp[k][0];
                            comp[k + 1][1] = comp[k][1];
                        }
                        else break;
                    }
                    else break;
                }
                else {
                    comp[k + 1][0] = comp[k][0];
                    comp[k + 1][1] = comp[k][1];
                }
                k--;
            }
            comp[k + 1][0] = num, comp[k + 1][1] = key;//for (int s = 0; s < n; s++){printf("%d %d\n", comp[s][0], comp[s][1]);}
        }
        int seq = 0;
        while (seq < n && parks[comp[seq][0]][3] >= parks[comp[seq][0]][2]) seq++;
        parks[comp[seq][0]][3]++;
    }
    for (int i = 0; i < n; i++){
        printf("%d\n", parks[i][3]);
    }
    return 0;
}
