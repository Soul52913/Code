#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long

typedef struct spell{
    char *word;
    ll rkm;
    ll compare;
    int id;
    int similar;
    bool copy;
    bool copy2;
}Spell;

Spell **slist;

int cmp (const void *a, const void *b){
    if((*(Spell **)a)->compare > (*(Spell **)b)->compare){
        return 1;
    }
    else if ((*(Spell **)a)->compare == (*(Spell **)b)->compare){
        return 0;
    }else {
        return -1;
    }
}

void fordd(ll *dd, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 9223372036854775807ll / d;
    ll power = 1;
    for(int i = len - 1; i >= 0; i--){
        dd[i] = power;
        power = (power * d) % q;
    }
    return;
}

void fordd2(ll *dd, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 2147483647 / d;
    ll power = 1;
    for(int i = len - 1; i >= 0; i--){
        dd[i] = power;
        power = (power * d) % q;
    }
    return;
}

ll RKM(char *spell, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 9223372036854775807ll / d;
    ll spellrkm = 0;
    for(int i = 0; i < len; i++){
        spellrkm = ((d * spellrkm) % q + (spell[i] - '!')) % q;
    }
    return spellrkm;
}

ll RKM2(char *spell, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 2147483647 / d;
    ll spellrkm = 0;
    for(int i = 0; i < len; i++){
        spellrkm = ((d * spellrkm) % q + (spell[i] - '!')) % q;
    }
    return spellrkm;
}

void compare(ll *dd, int num, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 9223372036854775807ll / d;
    for(int i = len - 1; i >= 0; i--){
        for(int j = 0; j < num; j++){
            slist[j]->compare = (slist[j]->rkm - (dd[i] * (slist[j]->word[i] - '!')) % q) % q;
            if (slist[j]->compare < 0) {slist[j]->compare += q;}
        }
        qsort(slist, num, sizeof(Spell *), cmp);
        for(int j = 0; j < num - 1; j++){
            if(slist[j]->compare == slist[j + 1]->compare){
                slist[j]->copy = true, slist[j + 1]->copy = true;
            }
        }
    }
    return;
}

void compare2(ll *dd, int num, int len){
    ll d = (int)'~' - (int)'!' + 1;
    ll q = 2147483647 / d;
    for(int i = len - 1; i >= 0; i--){
        for(int j = 0; j < num; j++){
            slist[j]->compare = (slist[j]->rkm - (dd[i] * (slist[j]->word[i] - '!')) % q) % q;
            if (slist[j]->compare < 0) {slist[j]->compare += q;}
        }
        qsort(slist, num, sizeof(Spell *), cmp);
        for(int j = 0; j < num - 1; j++){
            if(slist[j]->compare == slist[j + 1]->compare){
                if(slist[j]->copy && slist[j + 1]->copy){
                    slist[j]->copy2 = true, slist[j + 1]->copy2 = true;
                    slist[j]->similar = slist[j + 1]->id;
                    slist[j + 1]->similar = slist[j]->id;
                }
            }
        }
    }
    return;
}

int main(){
    int num = 0, len = 0, flag = 0;
    scanf("%d%d%d", &num, &len, &flag);
    slist = malloc(sizeof(Spell*) * (num + 10));
    for(int i = 0; i < num; i ++){
        slist[i] = (Spell *)malloc(sizeof(Spell));
        slist[i]->id = i, slist[i]->copy = false, slist[i]->similar = -1, slist[i]->rkm = 0, slist[i]->compare = 0, slist[i]->copy = true;
        slist[i]->word = malloc(sizeof(char) * len + 10);
        scanf("%s", slist[i]->word);
        slist[i]->rkm = RKM(slist[i]->word, len);
    }
    ll *dd;
    dd = malloc(sizeof(ll) * (len + 10));
    fordd(dd, len);
    compare(dd, num, len);
    for(int i = 0; i < num; i ++){
        slist[i]->rkm = RKM2(slist[i]->word, len);
    }
    fordd2(dd, len);
    compare2(dd, num, len);
    if (flag == 0){
        int copypos = 0;
        bool check = false;
        for(int i = 0; i < num; i++){
            if (slist[i]->copy2){
                check = true;
                copypos = i;
                break;
            }
        }
        if(check == true){
            printf("Yes\n");
            printf("%d %d", slist[copypos]->id, slist[copypos]->similar);
        }
        else {printf("No");}
    }
    else {
        ll anscount = 0;
        for(int i = 0; i < num; i++){
            if (slist[i]->copy2){
                anscount++;
            }
        }
        if (anscount > 0){
            printf("Yes\n");
            printf("%lld", anscount);
        }
        else {printf("No");}
    }
    return 0;
}