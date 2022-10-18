#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    int parent;
} DisjointSet;

DisjointSet ds[1 << 24];
bool set[1 << 24] = {};

int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(const char* s){
    int i = hash(s);
    ds[i].parent = i;
    return;
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {
        makeset(s);
        set[i] = 1;
    }
}

int find_set(const char* s) {
    init(s);
    int i = hash(s), temp = i;
    while(ds[temp].parent != temp){
        temp = ds[temp].parent;
    }
    int current = i;
    while (ds[current].parent != current){
        int point = current;
        current = ds[current].parent;
        ds[point].parent = temp;
    }
    return temp;
}

bool same_set(const char*a, const char* b) {
    int aint = find_set(a), bint = find_set(b);
    if(aint == bint){
        return true;
    }
    else{
        return false;
    }
}

void group(const char *ra, const char *rb) {
    int a = find_set(ra), b = find_set(rb);
    if(a != b){
        ds[b].parent = a;
    }
    return;
}

int main() {
    int line = 0;
    scanf("%d", &line);
    for (int i = 0; i < line; i++){
        char input[100];
        scanf("%s", input);
        if(strcmp(input, "group") == 0){
            char a[100], b[100];
            scanf("%s%s", a, b);
            group(a, b);
        }
        else if(strcmp(input, "test") == 0){
            char a[100], b[100];
            scanf("%s%s", a, b);
            if(same_set(a, b)){
                printf("Positive");
            }
            else{
                printf("Negative");
            }
            if (i == line - 1) continue;
            printf("\n");
        }
    }
    return 0;
}