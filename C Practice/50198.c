#include <stdio.h>

int main(){
    int a, b, x;
    while (scanf("%d%d%d", &a, &b, &x) != EOF){
        while (1){
            int check = 1;
            int s = x % 10, ss = -1, mod = 100, div = 10;
            //printf("%d%d/n", s, ss);
            while (x / div != 0){
                int temp = x % mod / div;
                if (temp != s){
                    if (ss == -1) ss = temp;
                    else if (temp != ss) check = 0;
                }
                mod *= 10, div *= 10;
            }
            if (check == 1) {
                printf("%d\n", x);
                break;
            }
            x = a * x % b;
        }
    }
    return 0;
}