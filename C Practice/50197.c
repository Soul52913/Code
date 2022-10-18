#include <stdio.h>

int main (){
    int k = 0; scanf("%d", &k);
    for (int i = 1000; i < 10000; ++i){
        int a = i % 10000 / 1000, b = i % 1000 / 100, c = i % 100 / 10, d = i % 10, diff = 0;
        diff = (a - b < 0)? b - a: a - b; if (diff > k) continue; 
        diff = (b - c < 0)? c - b: b - c; if (diff > k) continue; 
        diff = (c - d < 0)? d - c: c - d; if (diff > k) continue;
        printf("%d\n", i);
    }
    return 0;
}