#include <stdio.h>
#include <stdlib.h>

void queen (int **t, int py, int px, int r, int c){
    int count = 0;
    t[px][py] = 0;
    while (px - count >= 0 && t[px - count][py] != -1) {
        t[px - count][py] = -1;
        ++count;
    }count = 1;
    while (px - count >= 0 && py - count >= 0 && t[px - count][py - count] != -1) {
        t[px - count][py - count] = -1;
        ++count;
    }count = 1;
    while (px - count >= 0 && py + count < c && t[px - count][py + count] != -1) {
        t[px - count][py + count] = -1;
        ++count;
    }count = 1;
    while (px + count < r && t[px + count][py] != -1) {
        t[px + count][py] = -1;
        ++count;
    }count = 1;
    while (py - count >= 0 && t[px][py - count] != -1) {
        t[px][py - count] = -1;
        ++count;
    }count = 1;
    while (py + count < c && t[px][py + count] != -1) {
        t[px][py + count] = -1;
        ++count;
    }count = 1;
    while (px + count < r && py + count < c && t[px + count][py + count] != -1) {
        t[px + count][py + count] = -1;
        ++count;
    }count = 1;
    while (px + count < r && py - count >= 0 && t[px + count][py - count] != -1) {
        t[px + count][py - count] = -1;
        ++count;
    }t[px][py] = -1;
    return;
}
void bishop (int **t, int py, int px, int r, int c){
    int count = 0;
    t[px][py] = 0;
    while (px - count >= 0 && py - count >= 0 && t[px - count][py - count] != -1) {
        t[px - count][py - count] = -1;
        ++count;
    }count = 1;
    while (px - count >= 0 && py + count < c && t[px - count][py + count] != -1) {
        t[px - count][py + count] = -1;
        ++count;
    }count = 1;
    while (px + count < r && py + count < c && t[px + count][py + count] != -1) {
        t[px + count][py + count] = -1;
        ++count;
    }count = 1;
    while (px + count < r && py - count >= 0 && t[px + count][py - count] != -1) {
        t[px + count][py - count] = -1;
        ++count;
    }t[px][py] = -1;
    return;
}
void rook (int **t, int py, int px, int r, int c){
    int count = 0;
    t[px][py] = 0;
    while (px - count >= 0 && t[px - count][py] != -1) {
        t[px - count][py] = -1;
        ++count;
    }count = 1;
    while (px + count < r && t[px + count][py] != -1) {
        t[px + count][py] = -1;
        ++count;
    }count = 1;
    while (py - count >= 0 && t[px][py - count] != -1) {
        t[px][py - count] = -1;
        ++count;
    }count = 1;
    while (py + count < c && t[px][py + count] != -1) {
        t[px][py + count] = -1;
        ++count;
    }t[px][py] = -1;
    return;
}

int main(){
    int r, c, p, px, py;
    scanf("%d%d", &r, &c);
    int **t;
    t = malloc(r * sizeof *t);
    for (int i = 0; i < r; ++i){
        t[i] = malloc(c * sizeof(int));
    }
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            t[i][j] = 0;
        }
    }
    while (scanf("%d%d%d", &p, &px, &py) != EOF) {
        if (p == 0) {
            t[py][px] = -1;
        }
        else if (p == 1) queen(t, px, py, r, c);
        else if (p == 2) bishop(t, px, py, r, c);
        else rook(t, px, py, r, c);
    }
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if (t[i][j] == -1) printf("1 ");
            else printf("%d ", t[i][j]);
        }
        printf("\n");
    }
    return 0;
}