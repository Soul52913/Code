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
        if (RUNNING->arg % 2 == 1){
            RUNNING->arg = RUNNING->arg * 3 + 1;
        }
        else {
            RUNNING->arg = RUNNING->arg / 2;
        }
        printf("%d %d\n", RUNNING->id, RUNNING->arg);
        sleep(1);
        if (RUNNING->arg == 1) {
            thread_exit();
        }
        else {
            thread_yield();
        }
    }
}

void max_subarray(int id, int arg) {
    thread_setup(id, arg);
    if (RUNNING->arg > 0) {
        for (RUNNING->i = 0; RUNNING->i < RUNNING->arg; ++RUNNING->i) {
            async_read(5);
            int temp = atoi(RUNNING->buf);
            if (RUNNING->y + temp > temp)
                RUNNING->y += temp;
            else
                RUNNING->y = temp;
            if (RUNNING->y > RUNNING->x)
                RUNNING->x = RUNNING->y;
            printf("%d %d\n", RUNNING->id, RUNNING->x);
            if(RUNNING->i != (RUNNING->arg - 1)){
                sleep(1);
                thread_yield();
            }
        }
    }
    else {
        printf("%d %d\n", RUNNING->id, 0);
    }
    sleep(1);
    thread_exit();
}
