# include <stdio.h>

int number (int *n){
    int a = 0;
    scanf("%d", n);
    while (*n != 8 && *n != 9 && *n != 0){
        a = a * 10 + *n;
        scanf("%d", n);
    }
    return a;
}

int main(){
    int n = 0, num;
    int a = 0, b = 0;
    a = number(&n);
    while (n != 0){
        if (n == 9){
            b = number(&n);     //printf("%d\n", b);
            a *= b;
        }
        else if (n == 8){
            b = number(&n);     //printf("%d\n", b);
            int c = 0;
            while (n != 8 && n != 0){
                c = number(&n);     //printf("%d\n", c);
                b *= c;
            }
            a += b;
        }
        //scanf("%d", &n);
    }
    printf("%d", a);
    return 0;
}