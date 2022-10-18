#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct treap{
    struct treap *l, *r;
    int pri, key, siz;
    long long val, mx, lazy;
    bool rev;
}Treap;

Treap *root = NULL, **treaps;
int total = 0, time = 0;

Treap* newTreap(int k, int time){
    Treap *newnode = malloc(sizeof(Treap));
    newnode->l = NULL, newnode->r = NULL;
    newnode->pri = rand(), newnode->key = k, newnode->siz = 1;
    newnode->val = time, newnode->mx = time, newnode->rev = false;
    newnode->lazy = 0;
    treaps[k] = newnode;
    return newnode;
}

int Size(Treap *t){
    return t == NULL ? 0 : t->siz;
}

long long Mx(Treap *t){
    return t == NULL ? 0 : t->mx;
}

void push(Treap *t){
    if (t == NULL) return;
    if (t->rev)
    {
        Treap *temp = t->l;
        t->l = t->r; t->r = temp;
        if (t->l != NULL)
            t->l->rev ^= true;
        if (t->r != NULL)
            t->r->rev ^= true;
        t->rev = false;
    }
    if (t->lazy != 0)
    {
        if (t->val > t->lazy)
            t->val = t->lazy;
        if (t->l != NULL)
        {
            if (t->l->lazy == 0)
                t->l->lazy = t->lazy;
            else 
            {
                if (t->l->lazy > t->lazy)
                    t->l->lazy = t->lazy;
            }
        }
        if (t->r != NULL)
        {
            if (t->r->lazy == 0)
                t->r->lazy = t->lazy;
            else 
            {
                if (t->r->lazy > t->lazy)
                    t->r->lazy = t->lazy;
            }
        }
        t->lazy = 0;
    }
}

void pull(Treap *t){
    t->siz = 1 + Size(t->l) + Size(t->r);
    t->mx = t->val + Mx(t->l) + Mx(t->r);
}

int kth(Treap *t, int k){
    int lsz = Size(t->l) + 1;
    if (lsz < k) return kth(t->r, k - lsz);
    else if(lsz == k) return t->key;
    else return kth(t->l, k);
}

int kthtime(Treap *t, int k){
    int lsz = Size(t->l) + 1;
    time += Mx(t->l) + t->val;
    if (lsz < k)
    {
        return kth(t->r, k - lsz);
    } 
    else if(lsz == k)
    {
        return t->key;
    }
    else 
    {
        time -= Mx(t->l) + t->val;
        return kth(t->l, k);
    }
}

Treap* merge(Treap* a, Treap* b){
    push(a), push(b);
    if (a == NULL || b == NULL) return a ? a : b;
    if (a->pri > b->pri){
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else{
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

void split(Treap* t, int k, Treap** a, Treap** b){
    if (t == NULL){
        *a = *b = NULL;
        return;
    }
    push(t);
    if (Size(t->l) >= k){
        *b = t;
        push(*b);
        split(t->l, k, a, &((*b)->l));
        pull(*b);
    }
    else{
        *a = t;
        push(*a);
        split(t->r, k - Size(t->l) - 1, &((*a)->r), b);
        pull(*a);
    }
}

void insert(int k, int key, long long time){
    Treap *lt, *rt;
    split(root, k, &lt, &rt);
    root = merge(merge(lt, newTreap(key, time)), rt);
}

void rremove(int k){
    Treap *lt, *rt;
    split(root, k - 1, &lt, &root);
    split(root, k - Size(lt), &root, &rt);
    root = merge(lt, rt);
}

void one(int p, long long k){
    total++;
    insert (p, total, k);
}

void two(int p){
    rremove (p);
}

void three(int l, int r){
    Treap *lt, *t, *rt;
    split(root, r, &lt, &rt);
    split(lt, l - 1, &lt, &t);
    t->rev = true;
    root = merge(merge(lt, t), rt);
    return;
}

void four(int l, int r, int x, int y){
    int a = l, b = r, c = x, d = y;
    if (l > x)
    {
        a = x, b = y, c = l, d = r;
    }
    Treap *lt, *t, *rt, *g, *rg;
    split(root, d, &lt, &rg);
    split(lt, c - 1, &lt, &g);
    split(lt, b, &lt, &rt);
    split(lt, a - 1, &lt, &t);
    root = merge(merge(merge(merge(lt, g), rt), t), rg);
    return;
}

void five(int l, int r, long long k){
    Treap *lt, *t, *rt;
    split(root, r, &lt, &rt);
    split(lt, l - 1, &lt, &t);
    if (t->lazy == 0)
        t->lazy = k;
    else 
    {
        if (t->lazy > k)
            t->lazy = k;
    }
    root = merge(merge(lt, t), rt);
    return;
}

void six (int l, int r){
    Treap *lt, *rt;
    split(root, l - 1, &lt, &root);
    split(root, r - Size(lt), &root, &rt);
    printf("%lld\n", Mx(root));
    root = merge(merge(lt, root), rt);
}

void runcmd(void){
    int op;
    scanf("%d", &op);
    switch (op)
    {
    case 1: {int p, k; scanf("%d%d", &p, &k); one(p, k); break; }
    case 2: {int p; scanf("%d", &p); two(p); break; }
    case 3: {int l, r; scanf("%d%d", &l, &r); three(l, r); break; }
    case 4: {int l, r, x, y; scanf("%d%d%d%d", &l, &r, &x, &y); four(l, r, x, y); break; }
    case 5: {int l, r, k; scanf("%d%d%d", &l, &r, &k); five(l, r, k); break; }
    case 6: {int l, r; scanf("%d%d", &l, &r); six(l, r); break; }
    default: break;
    }/*for (int j = 1; j <= total; j++){
            if (treaps[j]->l != NULL){
                printf("%d ", treaps[j]->l->key);
            }else printf("  ");
            if (treaps[j]->r != NULL){
                printf("%d ", treaps[j]->r->key);
            }else printf("  ");
            printf("%d %d %d\n", treaps[j]->key, treaps[j]->mx, treaps[j]->val);
        }*/
}

int main(){
    int N, Q;
    scanf("%d%d", &N, &Q);
    treaps = malloc(sizeof(Treap *) * (200000 + 1 + 10));
    for (int i = 1; i <= N; i++)
    {
        int input; total++;
        scanf("%d", &input);
        treaps[i] = newTreap(i, input);
        root = merge(root, treaps[i]);
    }
    for (int i = 0; i < Q; i++)
    {
        runcmd();
        
    }
    return 0;
}