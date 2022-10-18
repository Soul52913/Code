#include <stdio.h>

int main(){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int prime_test = 0;
    if(c == 0){
        if(b == 0){
            if(a == 0){
                printf("0");
            }
            else{
                prime_test = a;
            }
        }
        else{
            prime_test = b;
        }
    }
    else{
        prime_test = c;
    }
    int prime_test_p = (prime_test < 0)? -prime_test: prime_test;
    int primes[2 * prime_test_p], prime_count = 0;
    for(int i = 1; i <= prime_test_p; i++){
        if(prime_test_p % i == 0){
            primes[prime_count] = i;
            prime_count++;
        }
    }
    for(int i = 0; i < prime_count; i++){
        primes[i + prime_count] = -primes[i];
    }
    int answers[3], answer_count = 0;
    for(int i = 0; i < 2 * prime_count; i++){
        int result = (primes[i] * primes[i] * primes[i]) + (a * primes[i] * primes[i]) + (b * primes[i]) + c;
        if(result == 0){
            answers[answer_count] = primes[i];
            answer_count++;
        }
    }
    if(answer_count == 2){
        if((answers[0] * answers[0] * answers[1]) == prime_test){
            answers[2] = answers[0];
        }
        else if((answers[0] * answers[1] * answers[1]) == prime_test){
            answers[2] = answers[1];
        }
    }
    else if(answer_count == 1){
        if((answers[0] * answers[0] * answers[0]) == prime_test){
            answers[2] = answers[0];
            answers[1] = answers[0];
        }
        else if((answers[0] * answers[0]) == prime_test){
            answers[1] = answers[0];
        }
    }
    for(int i = 0; i < 3; i++){
        answers[i] = -answers[i];
    }
    for(int k = 0; k < 2; k++){
        for(int j = 0; j < 2; j++){
            if(answers[j] > answers[j + 1]){
                int temp = answers[j];
                answers[j] = answers[j + 1];
                answers[j + 1] = temp;
            }
        }
    }
    printf("%d %d %d", answers[0], answers[1], answers[2]);
    return 0;
}