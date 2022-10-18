#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct xorlist{
    int id;
    struct xorlist *next;
} Xorlist;

Xorlist **head, **tail, ***groups, ***groupl;
int **sequencefront, **sequenceafter, *pos, *closeornot, *firstgroup, totalroom = 0;

Xorlist *xor(Xorlist *a, Xorlist *b){
    return (Xorlist*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void printlist(int room){
    for(int i = 0; i < room; i++){
        if(closeornot[i] == 1){
            if(i != room - 1){
                printf("\n");
            }
            continue;
        }
        Xorlist *current = head[i];
        Xorlist *previous = NULL;
        Xorlist *nextp;
        while(current != NULL){
            printf("%d ", current->id);
            nextp = xor(previous, current->next);
            previous = current;
            current = nextp;
        }
        if(i != room - 1){
            printf("\n");
        }
    }
    return;
}

void enter(int ggroup, int id, int line){
    Xorlist *newnode = (Xorlist *)malloc(sizeof(Xorlist));
    newnode->id = id;
    int temp = pos[line];
    if (head[line] == NULL){
        newnode->next = NULL;
        head[line] = newnode;
        tail[line] = newnode;
        groups[line][ggroup] = newnode;
        groupl[line][ggroup] = newnode;
        pos[line] = ggroup;
        firstgroup[line] = ggroup;
    }
    else{
        if(groups[line][ggroup] == NULL || groupl[line][ggroup] == NULL){
            newnode->next = xor(tail[line], NULL);
            tail[line]->next = xor(newnode, xor(tail[line]->next, NULL));
            tail[line] = newnode;
            groups[line][ggroup] = newnode;
            groupl[line][ggroup] = newnode;
            sequenceafter[line][temp] = ggroup;
            sequencefront[line][ggroup] = temp;
            pos[line] = ggroup;
        }
        else if(ggroup == temp){
            newnode->next = xor(tail[line], NULL);
            tail[line]->next = xor(newnode, xor(tail[line]->next, NULL));
            tail[line] = newnode;
            groupl[line][ggroup] = newnode;
        }
        else{
            int groupbehind = sequenceafter[line][ggroup];
            Xorlist *cut = groupl[line][ggroup], *aftercut = groups[line][groupbehind];
            newnode->next = xor(cut, aftercut);
            cut->next = xor(newnode, xor(aftercut, cut->next));
            aftercut->next = xor(newnode, xor(cut, aftercut->next));
            groupl[line][ggroup] = newnode;
        }
    }
    return;
}

void leave(int line){
    int temp = pos[line];
    int frontgroup = sequencefront[line][temp];
    if(tail[line] != NULL){
        Xorlist *last = tail[line];
        int lastbelong = temp;
        Xorlist *previous = xor(last->next, NULL);
        if(previous == NULL){
            head[line] = NULL;
            groups[line][lastbelong] = NULL;
            groupl[line][lastbelong] = NULL;
            pos[line] = -1;
            firstgroup[line] = -1;
        }
        else{
            if(previous == groups[line][lastbelong]){
                groupl[line][lastbelong] = previous;
            }
            else if(previous == groupl[line][frontgroup]){
                groups[line][lastbelong] = NULL;
                groupl[line][lastbelong] = NULL;
                sequencefront[line][temp] = -1;
                sequenceafter[line][frontgroup] = -1;
                pos[line] = frontgroup;
            }
            else{
                groupl[line][lastbelong] = previous;
            }
            previous->next = xor(xor(previous->next, last), NULL);
        }
        tail[line] = previous;
    }
    return;
}

void go(int line){
    if(head[line] != NULL){
        Xorlist *first = head[line];
        int firstbelong = firstgroup[line];
        int behindgroup = sequenceafter[line][firstbelong];
        Xorlist *after = xor(head[line]->next, NULL);
        if(after == NULL){
            tail[line] = NULL;
            groups[line][firstbelong] = NULL;
            groupl[line][firstbelong] = NULL;
            firstgroup[line] = -1;
            pos[line] = -1;
        }
        else{
            if(head[line] == groupl[line][firstbelong]) {
                groups[line][firstbelong] = NULL;
                groupl[line][firstbelong] = NULL;
                sequenceafter[line][firstbelong] = -1;
                sequencefront[line][behindgroup] = -1;
                firstgroup[line] = behindgroup;
            }
            else{
                groups[line][firstbelong] = after;
            }
            after->next = xor(xor(after->next, first), NULL);
        }
        head[line] = after;
    }
    return;
}

void move(int ggroup, int line, Xorlist *start, Xorlist *secondstart, Xorlist *last, Xorlist *secondlast){
    int temp = pos[line];
    if (head[line] == NULL) {
        if(start == last){
            start->next = NULL;
        }
        else{
            start->next = xor(NULL, secondstart);
            last->next = xor(NULL, secondlast);
        }
        head[line] = start;
        tail[line] = last;
        groups[line][ggroup] = start;
        groupl[line][ggroup] = last;
        pos[line] = ggroup;
        firstgroup[line] = ggroup;
    }
    else{
        if(groups[line][ggroup] == NULL || groupl[line][ggroup] == NULL){
            if(start == last){
                start->next = xor(tail[line], NULL);
            }
            else{
                start->next = xor(tail[line], secondstart);
                last->next = xor(NULL, secondlast);
            }
            tail[line]->next = xor(start, xor(tail[line]->next, NULL));
            tail[line] = last;
            groups[line][ggroup] = start;
            groupl[line][ggroup] = last;
            sequenceafter[line][temp] = ggroup;
            sequencefront[line][ggroup] = temp;
            pos[line] = ggroup;
        }
        else if(ggroup == temp){
            if(start == last){
                start->next = xor(tail[line], NULL);
            }
            else{
                start->next = xor(tail[line], secondstart);
                last->next = xor(NULL, secondlast);
            }
            tail[line]->next = xor(start, xor(tail[line]->next, NULL));
            tail[line] = last;
            groupl[line][ggroup] = last;
        }
        else{
            int groupbehind = sequenceafter[line][ggroup];
            Xorlist *cut = groupl[line][ggroup], *aftercut = groups[line][groupbehind];
            if(start == last){
                start->next = xor(cut, aftercut);
            }
            else{
                start->next = xor(cut, secondstart);
                last->next = xor(aftercut, secondlast);
            }
            cut->next = xor(start, xor(aftercut, cut->next));
            aftercut->next = xor(last, xor(cut, aftercut->next));
            groupl[line][ggroup] = last;
        }
    }
    return;
}

void close(int line){
    if(head[line] == NULL){
        closeornot[line] = 1;
        return;
    }
    int find = 0;
    find = line;
    if((find - 1) < 0){
        find = totalroom - 1;
    }
    else{
        find--;
    }
    while(closeornot[find] != 0){
        if((find - 1) < 0){
            find = totalroom - 1;
        }
        else{
            find--;
        }
    }
    Xorlist *last = NULL, *secondlast = NULL, *start = NULL, *secondstart = NULL, *frontlast = NULL;
    int movegroup = 0, temp = pos[line];
    if(groups[line][temp] == groupl[line][temp]){
        movegroup = temp;
        temp = sequencefront[line][temp];
        last = groupl[line][movegroup];
        secondlast = groupl[line][movegroup];
        start = groupl[line][movegroup];
        secondstart = groupl[line][movegroup];
        move(movegroup, find, last, secondlast, start, secondstart);
    }
    else{
        movegroup = temp;
        temp = sequencefront[line][temp];
        last = groupl[line][movegroup];
        secondlast = xor(last->next, NULL);
        start = groups[line][movegroup];
        if(temp == -1){
            secondstart = xor(NULL, groups[line][movegroup]->next);
        }
        else{
            frontlast = groupl[line][temp];
            secondstart = xor(frontlast, groups[line][movegroup]->next);
        }
        move(movegroup, find, last, secondlast, start, secondstart);
    }
    while(temp != -1){
        if(groups[line][temp] == groupl[line][temp]){
            movegroup = temp;
            temp = sequencefront[line][temp];
            last = groupl[line][movegroup];
            secondlast = groupl[line][movegroup];
            start = groupl[line][movegroup];
            secondstart = groupl[line][movegroup];
            move(movegroup, find, last, secondlast, start, secondstart);
        }
        else{
            movegroup = temp;
            temp = sequencefront[line][temp];
            last = groupl[line][movegroup];
            secondlast = xor(last->next, start);
            start = groups[line][movegroup];
            if(temp == -1){
                secondstart = xor(NULL, groups[line][movegroup]->next);
            }
            else{
                frontlast = groupl[line][temp];
                secondstart = xor(frontlast, groups[line][movegroup]->next);
            }
            move(movegroup, find, last, secondlast, start, secondstart);
        }
    }
    closeornot[line] = 1;
    return;
}

void read(char *command){
    if(strcmp(command, "enter") == 0){
        int ggroup = 0, id = 0, line = 0;
        scanf("%d%d%d", &ggroup, &id, &line);
        enter(ggroup, id, line);
    }
    else if(strcmp(command, "leave") == 0){
        int line = 0;
        scanf("%d", &line);
        leave(line);
    }
    else if(strcmp(command, "go") == 0){
        int line = 0;
        scanf("%d", &line);
        go(line);
    }
    else if(strcmp(command, "close") == 0){
        int line = 0;
        scanf("%d", &line);
        close(line);
    }
    return;
}

int main(){
    int room = 0, situ = 0, ggroup = 0;
    scanf("%d%d%d", &room, &situ, &ggroup);
    totalroom = room;
    head = malloc(sizeof(Xorlist*)*room);
    tail = malloc(sizeof(Xorlist*)*room);
    groups = malloc(sizeof(Xorlist**)*room);
    groupl = malloc(sizeof(Xorlist**)*room);
    sequencefront = malloc(sizeof(int*) * room);
    sequenceafter = malloc(sizeof(int*) * room);
    pos = malloc(sizeof(int)*room);
    firstgroup = malloc(sizeof(int)*room);
    closeornot = malloc(sizeof(int)*room);
    for (int i = 0; i < room; i++){
        groups[i] = malloc(sizeof(Xorlist*)*(ggroup + 1));
        groupl[i] = malloc(sizeof(Xorlist*)*(ggroup + 1));
        pos[i] = -1, firstgroup[i] = -1, closeornot[i] = 0;
        for (int j = 0; j < ggroup + 1; j++){
            groups[i][j] = NULL;
            groupl[i][j] = NULL;
        }
        head[i] = NULL;
        tail[i] = NULL;
    }
    for (int i = 0; i < room; i++){
        sequencefront[i] = malloc(sizeof(int)*(ggroup + 1));
        sequenceafter[i] = malloc(sizeof(int)*(ggroup + 1));
        for (int j = 0; j < ggroup + 1; j++){
            sequencefront[i][j] = -1;
            sequenceafter[i][j] = -1;
        }
    }
    for (int i = 0; i < situ; i++){
        char s[6];
        scanf("%s", s);
        read(s);
    }
    printlist(totalroom);
    return 0;
}