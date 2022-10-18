#include <stdio.h>
#include <string.h>
#include <stdbool.h>
# define STRINTGLEN 260

int x_len = 0, y_len = 0;

void swap(int *x, int *y){
    for(int i = 0; i < y_len; i++){
        int temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
    int lentemp = x_len;
    x_len = y_len;
    y_len = lentemp;
    return;
}
void intandflip(char *x, int *y){
    for(int i = 0; i < strlen(x); i++){
        y[strlen(x) - 1 - i] = (int)x[i] - 48;
    }
    return;
}
void maxandmin(int *x, int *y){
    if(x_len > y_len){
        return;
    }else if(y_len > x_len){
        swap(x, y);
        return;
    }
    else if(x_len = y_len){
        for(int i = x_len - 1; i >= 0; i--){
            if(y[i] > x[i]){
                swap(x, y);
                return;
            }else if (x[i] > y[i]){
                return;
            }
        }
    }return;
}
bool iszero(int *z, int len){
    for (int i = 0; i < len; i++){
        if(z[i] != 0){
            return 0;
        }
    }return 1;
}
void dividetwo(int *z, int *len){
    int left = 0;
    for(int i = *len - 1; i >= 0; i--){
        int object = z[i] + (left * 10);
        int quo = object / 2;
        left = object % 2;
        z[i] = quo;
    }if(z[*len - 1] == 0){
        *len -= 1;
    }return;
}
void minus(int *x, int *y){
    for(int i = 0; i < x_len; i++){
        if(x[i] >= y[i]){
            x[i] -= y[i];
        }else{
            x[i + 1]--;
            x[i] = 10 + x[i] - y[i]; 
        }
    }for(int i = x_len - 1; i >= 0; i--){
        if(x[i] != 0){
            break;
        }else{
            x_len--;
        }
    }return;
}
void multitwo(int *z){
    int dec = 0, result = 0, remain = 0, count = y_len;
    for(int i = 0; i < count; i++){
        result = 2 * z[i];
        remain = result % 10;
        z[i] = remain + dec;
        dec = result / 10;
        if(i == y_len - 1 && dec != 0){
            z[y_len] = dec;
            y_len++;
        }
    }return;
}
bool backbigger(int *x, int *y){
    if(x_len > y_len){
        return 0;
    }else if(y_len > x_len){
        return 1;
    }else if(x_len == y_len){
        for (int i = x_len - 1; i >= 0; i--){
            if(y[i] > x[i]){
                return 1;
            }else if (x[i] > y[i]){
                return 0;
            }
        }return 0;
    }
}
void binary(int *x, int *y, int *ans){
    maxandmin(x, y);
    int count = 0;
    while(!iszero(x, x_len) && !iszero(y, y_len)){
        if(x[0] % 2 == 0 && y[0] % 2 == 0){
            count++;
            dividetwo(x, &x_len);
            dividetwo(y, &y_len);
        }
        else if(x[0] % 2 == 0 && y[0] % 2 != 0){
            dividetwo(x, &x_len);
        }
        else if(x[0] % 2 != 0 && y[0] % 2 == 0){
            dividetwo(y, &y_len);
        }
        if(backbigger(x, y)){
            swap(x, y);
        }
        minus(x, y);
    }
    for (int i = 0; i < count; i++){
        multitwo(y);
    }
    for (int i = y_len - 1, j = 0; i >= 0; i--,j++){
        ans[i] = y[j];
    }
    return;
}
int main(){
    char x[STRINTGLEN];
    char y[STRINTGLEN];
    int a[STRINTGLEN] = {0};
    int b[STRINTGLEN] = {0};
    int ans[STRINTGLEN] = {0};
    scanf("%s", x);
    x_len += strlen(x);
    scanf("%s", y);
    y_len += strlen(y);
    intandflip(x, a);
    intandflip(y, b);
    binary(a, b, ans);
    for(int i = 0; i < y_len; i++){
        printf("%d", ans[i]);
    }
    return 0;
}