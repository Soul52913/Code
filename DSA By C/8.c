#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int computepi(char *P, int len){
    int *pi;
    pi = malloc(sizeof(int) * 20000020);
    for(int i = 0; i < 20000020; i++) {pi[i] = 0;}
    int k = 0;
    for(int i = 1; i < len; i++){
        int check = 0;
        while (k > 0 && P[k] != P[i] && check < (len + 10)){
            k=pi[k - 1]; check++;
        }
        if (P[k] == P[i]){
            k++;
        }
        pi[i] = k;
    }
    return pi[len - 1];
}


int main(){
    char *spell, *oppsite, *test;
    spell = malloc(sizeof(char) * 10000010);
    scanf("%s", spell);
    int len = strlen(spell);
    oppsite = malloc(sizeof(char) * len);
    for(int i = 0; i < len; i++){
        oppsite[len - 1 - i] = spell[i];
    }
    oppsite[len] = '\0';
    test = malloc(sizeof(char) * 20000020);
    for(int i = 0; i < len; i++){
        test[i] = spell[i];
        test[i + len] = oppsite[i];
    }
    test[2 * len] = '\0';
    int front = computepi(test, len * 2);
    for(int i = 0; i < len; i++){
        test[i] = oppsite[i];
        test[i + len] = spell[i];
    }
    test[2 * len] = '\0';
    int back = computepi(test, len * 2);
    free(test);
    char *fronttemp, *backtemp;
    if (front > len) {front = len;}
    if (back > len) {back = len;}
    fronttemp = malloc(sizeof(char) * (len - front + 10));
    backtemp = malloc(sizeof(char) * (len - back + 10));
    for(int i = 0; i < len - front; i++){
        fronttemp[i] = oppsite[i];
    }
    fronttemp[len - front] = '\0';
    for(int i = back, j = 0; i < len; i++, j++){
        backtemp[j] = oppsite[i];
    }
    backtemp[len - back] = '\0';
    if (front == back){
        int add = len - front;
        printf("%d\n", add);
        printf("%s%s\n", fronttemp, spell);
        if (add != 0){printf("%s%s", spell, backtemp);}
    }
    else if(front > back){
        int add = len - front;
        printf("%d\n", add);
        printf("%s%s", fronttemp, spell);
    }
    else{
        int add = len - back;
        printf("%d\n", add);
        printf("%s%s", spell, backtemp);
    }
    return 0;
}