#include <stdio.h>

int main(){
    int k = 0, L = 0, n = 0;
    scanf("%d%d%d", &k, &L, &n);
    int left = L;
    while (n != 0){
        int t = n % k;
        int length = 0, dec = 1;
        while (n / dec != 0){
            ++length;
            dec *= 10;
        }
        if ((length * t) > left){
            if ((length * t) <= L){ 
                printf("\n");
                for (int i = 0; i < t; ++i) printf("%d", n);
                left = L - length * t;
            }
        }
        else {
            left -= length * t;
            for (int i = 0; i < t; ++i) printf("%d", n);
        }
        scanf("%d", &n);
    }

    return 0;
}