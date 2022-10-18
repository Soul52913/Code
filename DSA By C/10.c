#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct disjointSet{
    int parent;
    int init;
} DisjointSet;

DisjointSet **stores;
int **commands, *preboom, *daytotal, boomsum = 1;
int total = 0;

int find_set(int x) {
    int temp = x;
    while(stores[boomsum + 1][temp].parent != temp){
        temp = stores[boomsum + 1][temp].parent;
    }
    int current = x;
    while (stores[boomsum + 1][current].parent != current){
        int temp2 = current;
        current = stores[boomsum + 1][current].parent;
        stores[boomsum + 1][temp2].parent = temp;
    }
    return temp;
}

int merge(int ra, int rb, int total) {
    int a = find_set(ra), b = find_set(rb);
    if(a != b){
        stores[boomsum + 1][b].parent = a;
        total--;
    }
    return total;
}

void init(int shop){
    for (int i = 1; i <= shop; i++){
        stores[0][i].parent = i;
        stores[boomsum + 1][i].parent = i;
    }
    return;
}

void print (int day, int shop){
    init (shop);
    for (int i = 1; i <= day; i++){
        if (commands[i][0] == 1){
            total = merge(commands[i][1], commands[i][2], total);
        }
        else if (commands[i][0] == 2){
            int boomnum = commands[i][1];
            if (boomnum != 0){
                for (int j = 1; j <= shop; j++){
                    stores[boomsum + 1][j].parent = stores[preboom[boomnum]][j].parent;
                    total = daytotal[boomnum];
                }
            }
            else {
                for (int j = 1; j <= shop; j++){
                    stores[boomsum + 1][j].parent = stores[0][j].parent;
                    total = daytotal[0];
                }
            }
        }
        else if (commands[i][0] == 3){
            printf("%d\n", total);
        }
        if (preboom[i] != 0){ 
            for (int j = 1; j <= shop; j++){
                stores[preboom[i]][j].parent = stores[boomsum + 1][j].parent;
            }
            daytotal[i] = total;
        }
    }
}

void inputboom (int day){
    int i = 1;
    while (i <= day){
        if (commands[i][0] == 2){
            if (preboom[commands[i][1]] == 0){
                preboom[commands[i][1]] = boomsum;
                boomsum++;
            }
        }
        i++;
    }
    boomsum--;
}

int main(){
    int shop = 0, day = 0;
    scanf("%d%d", &shop, &day);
    total = shop;
    commands = malloc(sizeof(int *) * (day + 1));
    for (int i = 1; i <= day; i++){
        commands[i] = malloc(sizeof(int) * 3);
        char temp[6];
        scanf("%s", temp);
        if (strcmp(temp, "merge") == 0){
            commands[i][0] = 1;
            scanf("%d%d", &commands[i][1], &commands[i][2]);
        }
        else if (strcmp(temp, "boom") == 0){
            scanf("%d", &commands[i][1]);
            commands[i][0] = 2, commands[i][2] = -1;
        }
        else {
            commands[i][0] = 3, commands[i][1] = -1, commands[i][2] = -1;
        }
    }
    preboom = malloc(sizeof(int) * (day + 1));
    for (int i = 0; i <= day; i++){
        preboom[i] = 0;
    }
    inputboom(day);
    stores = malloc(sizeof(DisjointSet *) * (boomsum + 2));
    for(int i = 0; i <= boomsum + 1; i++){
        stores[i] = malloc(sizeof(DisjointSet) * (shop + 1));
    }
    daytotal = malloc(sizeof(int) * (day + 1));
    daytotal[0] = shop;
    for(int i = 1; i <= boomsum ; i++){
        daytotal[i] = -1;
    }
    stores[0][0].parent = -1;
    init(shop);
    print(day, shop);
    return 0;
}