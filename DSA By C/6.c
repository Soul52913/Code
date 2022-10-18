#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pretreenode{
    int id;
    struct pretreenode **relation;
    int rela_count;
} Pretreenode;

Pretreenode **pretreearray, **pretreequeue;
int enqueuecount = 0, max = 0, dequeuecount = 0;

typedef struct treenode{
    int id;
    struct treenode *parent;
    bool resortpass;
    int largest;
} Treenode;

Treenode **treearray, *capital; //root is capital

void enqueue(Pretreenode *node){
    pretreequeue[enqueuecount] = node;
    if(enqueuecount + 1 > max){
        enqueuecount = 0;
    }
    else{
        enqueuecount++;
    }
    return;
}

Pretreenode* dequeue(void){
    Pretreenode *temp = pretreequeue[dequeuecount];
    pretreequeue[dequeuecount] = NULL;
    if(dequeuecount + 1 > max){
        dequeuecount = 0;
    }
    else{
        dequeuecount++;
    }
    return temp;
}

void buildsubtree(int city, int N){
    int lastcount = 0, check = 0;
    while(check < N - 1){
        for (int i = 0; i < pretreearray[city]->rela_count; i++){
            int iid = 0;
            iid = pretreearray[city]->relation[i]->id;
            if(treearray[city]->parent != NULL && iid == treearray[city]->parent->id){
                continue;
            }
            else{
                treearray[iid]->parent = treearray[city];
                enqueue(pretreearray[city]->relation[i]);
            }
        }
        Pretreenode *node = dequeue();
        if(node == NULL){
            break;
        }
        else{
            city = node->id;
            check++;
        }
    }
    return;
}

void buildtree(int N, int S){
    pretreearray[0] = NULL;
    for(int i = 1; i <= N; i++){
        pretreearray[i] = (Pretreenode *)malloc(sizeof(Pretreenode));
        pretreearray[i]->relation = malloc(sizeof(Pretreenode*) * 10);
        for (int j = 0; j < 10; j++){
            pretreearray[i]->relation[j] = NULL;
        }
        pretreearray[i]->rela_count = 0;
        pretreearray[i]->id = i;
    }
    for(int i = 1; i <= (N - 1); i++){
        int a = 0, b = 0;
        scanf("%d%d", &a, &b);
        Pretreenode *Anode = pretreearray[a], *Bnode = pretreearray[b];
        Anode->relation[Anode->rela_count] = Bnode;
        Anode->rela_count++;
        Bnode->relation[Bnode->rela_count] = Anode; 
        Bnode->rela_count++;
    }
    treearray[0] = NULL;
    for(int i = 1; i <= N; i++){
        treearray[i] = (Treenode *)malloc(sizeof(Treenode));
        treearray[i]->id = i;
        treearray[i]->parent = NULL;
        treearray[i]->resortpass = false;
        treearray[i]->largest = 0;
    }
    capital = treearray[S];
    buildsubtree(S, N);
    return;
}

void getlargest(int N){
    for(int i = 1; i <= N; i++){
        Treenode *now = treearray[i];
        if(now->largest != 0){
            continue;
        }
        else{
            int largest_i = 0;
            while(now->largest == 0){
                now = now->parent;
            }
            largest_i = now->largest;
            now = treearray[i];
            while(now->largest == 0){
                now->largest = largest_i;
                now = now->parent;
            }
        }
    }
    return;
}

int main(){
    int N = 0, Q = 0, S = 0, R = 0;
    scanf("%d%d%d%d", &N, &Q, &S, &R);
    max = N;
    treearray = malloc(sizeof(Treenode*) * (N + 1));
    pretreearray = malloc(sizeof(Pretreenode*) * (N + 1));
    pretreequeue = malloc(sizeof(Pretreenode*) * (N + 1));
    for (int i = 0; i < N + 1; i++){
        treearray[i] = NULL, pretreearray[i] = NULL, pretreequeue[i] = NULL;
    }
    buildtree(N, S);
    /*for(int i = 1; i < N + 1; i++){
        if(i == S){
            printf("%d\n", treearray[i]->id);
            continue;
        }
        printf("%d %d\n", treearray[i]->id, treearray[i]->parent->id);
    }*/
    Treenode *now = treearray[R];
    while(now->parent != NULL){
        now->resortpass = true;
        now->largest = now->id;
        now = now->parent;
    }
    now->resortpass = true;
    now->largest = now->id;
    getlargest(N);
    for (int i = 0; i < Q; i++){
        int C = 0;
        scanf("%d", &C);
        printf("%d", treearray[C]->largest);
        if(i != Q - 1) printf("\n");
    }
    return 0;
}