#include "threadtools.h"

void fibonacci(int id, int arg) {
    thread_setup(id, arg);

    for (RUNNING->i = 1; ; RUNNING->i++) {
        if (RUNNING->i <= 2)
            RUNNING->x = RUNNING->y = 1;
        else {
            /* We don't need to save tmp, so it's safe to declare it here. */
            int tmp = RUNNING->y;  
            RUNNING->y = RUNNING->x + RUNNING->y;
            RUNNING->x = tmp;
        }
        printf("%d %d\n", RUNNING->id, RUNNING->y);
        sleep(1);

        if (RUNNING->i == RUNNING->arg) {
            thread_exit();
        }
        else {
            thread_yield();
        }
    }
}

void collatz(int id, int arg) {
    // TODO
    thread_setup(id, arg);

    for (RUNNING->i = 1; ; ){
        if (arg % 2 == 1){
            arg = arg * 3 + 1
        }
        else {
            arg = arg / 2;
        }
        printf("%d %d", RUNNING->id, arg);
        sleep(1);
        if (arg == 1) {
            thread_exit();
        }
        else {
            thread_yield();
        }
    }
}

void max_subarray(int id, int arg) {
    if (arg > 0) {
        read(RUNNING->fd, RUNNING->buf, N * 6);
        int temp[arg];
        for(RUNNING->i = 0; RUNNING->i < N; ++RUNNING->i){
            sscanf(RUNNING->buf, "%d", &temp[RUNNING->i]);
        }
        int tempp = temp[0];
        int Max = temp[0];
        printf("%d %d", RUNNING->id, Max);
        thread_yield();
        sleep(1);
        for (RUNNING->i = 0; RUNNING->i < N; ++RUNNING->i) {
            if (temp[RUNNING->i] >= temp[RUNNING->i] + tempp)
                tempp = temp[RUNNING->i];
            else
                tempp = temp[RUNNING->i] + tempp;
            if (tempp > Max)
                Max = tempp;
            printf("%d %d", RUNNING->id, Max);
            sleep(1);
            thread_yield();
        }
    }
    else {
        printf("%d %d", RUNNING->id, 0);
        sleep(1);
        thread_yield();
    }
    sleep(1);
    thread_exit();
}
