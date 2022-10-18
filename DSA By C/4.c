#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char input[1000000], S1[2000000], space = ' ';
long long int S2[1000000], anst[1000000];
int ipos = 0, acount = 0;

long long int llipop(long long int *chart){
    long long int num = chart[ipos - 1];
    chart[ipos - 1] = 0;
    ipos--;
    return num;
}

void llipush(long long int *chart, long long int num){
    chart[ipos] = num;
    chart[ipos + 1] = 0;
    ipos++;
    return;
}

void push(char *chart, char c){
    int pos = strlen(chart);
    chart[pos] = c;
    chart[pos + 1] = '\0';
    return;
}

char peep(char *chart){
    int pos = strlen(chart) - 1;
    return chart[pos];
}

char pop(char *chart){
    int pos = strlen(chart) - 1;
    char c = chart[pos];
    chart[pos] = '\0';
    return c;
}

bool isempty(char *chart){
    if (strlen(chart) == 0){
        return true;
    }
    return false;
}

int classify(char op){
    switch (op){
        case '+' : case '-':
            return 1;
        case '*' : case '/': case '%':
            return 2;
    }
}

bool isop(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        return true;
    return false;
}

bool higher_same(char peep_op, char input_op){
    int p_o_level = classify(peep_op);
    int i_o_level = classify(input_op);
    if (p_o_level >= i_o_level){
        return true;
    }
    else{
        return false;
    }
}

int parent(char *input, char *S1, int i){
    char operator2[100000] = {};
    while(input[i] != ')' && i < strlen(input)){
        if(isdigit(input[i])){
            push(S1, input[i]);
        }
        else if (input[i] == '('){
            i++;
            i = parent(input, S1, i);
        }
        else if (isop(input[i])){
            push(S1, space);
            char peep_op = peep(operator2);
            while(!(isempty(operator2)) && higher_same(peep_op, input[i])){
                char pop_op = pop(operator2);
                push(S1, pop_op);
                push(S1, space);
                peep_op = peep(operator2);
            }
            push(operator2, input[i]);
        }
        i++;
    }
    while(!(isempty(operator2))){
        push(S1, space);
        char pop_op = pop(operator2);
        push(S1, pop_op);
        push(S1, space);
    }
    return i;
}

long long int process(char c, long long int a, long long int b){
    long long int ans = 0;
    switch (c){
        case '+':{
            ans = a + b;
            return ans;
            break;
        }
        case '-':{
            ans = a - b;
            return ans;
            break;
        }
        case '*':{
            ans = a * b;
            return ans;
            break;
        }
        case '/':{
            ans = a / b;
            if((a < 0) ^ (b < 0)){
                ans--;
            }
            return ans;
            break;
        }
        case '%':{
            ans = a % b;
            return ans;
            break;
        }
        default:{
            return ans;
            break;
        }
    }
}

void postfix(char *input, char *S1){
    static char operator[1000010];
    operator[0] = '\0';
    for (int i = 0; i < strlen(input); i++){
        if(isdigit(input[i])){
            push(S1, input[i]);
        }
        else if (input[i] == '('){
            i++;
            i = parent(input, S1, i);
        }
        else if (input[i] == '='){
            while(!(isempty(operator))){
                push(S1, space);
                char pop_op = pop(operator);
                push(S1, pop_op);
                push(S1, space);
            }
            push(S1, input[i]);
        }
        else if(isop(input[i])){
            push(S1, space);
            char peep_op = peep(operator);
            while(!(isempty(operator)) && higher_same(peep_op, input[i])){
                char pop_op = pop(operator);
                push(S1, pop_op);
                push(S1, space);
                peep_op = peep(operator);
            }
            push(operator, input[i]);
        }
    }
    while(!(isempty(operator))){
        push(S1, space);
        char pop_op = pop(operator);
        push(S1, pop_op);
        push(S1, space);
    }
    return;
}

void calculate_print(char *S1, long long int *S2){
    for (int i = 0; i < strlen(S1); i++){
        if(isdigit(S1[i])){
            long long int index = 0; 
            while(S1[i] != ' '){
                index *= 10;
                index += ((int)S1[i] - '0');
                i++;
            }
            llipush(S2, index);
        }else if(isop(S1[i])){
            long long int b = llipop(S2);
            long long int a = llipop(S2);
            long long int result = process(S1[i] , a, b);
            llipush(S2, result);
        }else if(S1[i] == '='){
            long long int answer = S2[ipos - 1];;
            anst[acount] = answer;
            acount++;
        }
    }
    return;
}

int main(){
    scanf("%s", input);
    postfix(input, S1);
    calculate_print(S1, S2);
    for (int i = 0; i < acount - 1; i++){
        printf("Print: %lld\n", anst[i]);
    }
    printf("Print: %lld", anst[acount - 1]);
    return 0;
}