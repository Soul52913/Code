#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "price.h"
#define ull unsigned long long

ull *stack, *stacktwo;
int position = 0;

void push(ull value){
    stack[position] = value;
    position++;
}

void merging(int low, int mid, int high) {
    int l1, l2, i;
    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(stack[l1] <= stack[l2])
            stacktwo[i] = stack[l1++];
        else
            stacktwo[i] = stack[l2++];
    }
   
    while(l1 <= mid)    
        stacktwo[i++] = stack[l1++];

    while(l2 <= high)   
        stacktwo[i++] = stack[l2++];

    for(i = low; i <= high; i++)
        stack[i] = stacktwo[i];
}

void sort(int low, int high) {
    int mid;
    if(low < high) {
        mid = (low + high) / 2;
        sort(low, mid);
        sort(mid+1, high);
        merging(low, mid, high);
    }else { 
        return;
    }   
}

int main(){
    int A = 0, Q = 0, N = 0;
    scanf("%d%d%d", &A, &Q, &N);
    ull stock[A];
    stack = malloc(sizeof(ull) * 100000000);
    stacktwo = malloc(sizeof(ull) * 100000000);
    for(int i = 0; i < A; i++){
        stock[i] = 0;
        scanf("%llu", &stock[i]);
    }
    for(int i = 0; i < 100000000;i++){
        stack[i] = 0;
        stacktwo[i] = 0;
    }
    for(ull t = 1; t < 1500000; t++){
        for(int i = 0; i < A; i++){
            ull result = 0;
            result = price(stock[i], t);
            push(result);
        }
    }
    /*for(ull t = 0; t < position; t++){
        printf("%llu\n", stack[t]);
    }*/
    sort(0, position - 1);
    /*for(ull t = 0; t < position; t++){
        printf("%llu\n", stack[t]);
    }*/
    
    for(int i = 0; i < Q; i++){
        int s = 0, request = 0;
        scanf("%d%d", &s, &request);
        printf("%llu\n", stack[request - 1]);
    }
    return 0;
}