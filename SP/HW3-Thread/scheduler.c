#include "threadtools.h"

/*
 * Print out the signal you received.
 * If SIGALRM is received, reset the alarm here.
 * This function should not return. Instead, call longjmp(sched_buf, 1).
 */
void sighandler(int signo) {
    // TODO
    if (signo == SIGTSTP){
        printf("caught SIGTSTP\n");
    }
    else if (signo == SIGALRM){
        printf("caught SIGALRM\n");
        alarm(timeslice);
    }
    siglongjmp(sched_buf, 1);
}

/*
 * Prior to calling this function, both SIGTSTP and SIGALRM should be blocked.
 */
void scheduler() {
    // TODO
    int jumpReturn = setjmp(sched_buf);
    struct pollfd pfds[wq_size];
    for (int i = 0; i < wq_size; ++i) {
        pfds[i].fd = waiting_queue[i]->fd;
        pfds[i].events = POLLIN;
    }
    int rret = poll(pfds, wq_size, 60);
    int sizeToMinus = rret;
    if (rret == -1) {
        perror("poll");
        exit(-1);
    }
    if (rret > 0) {
        int waitingReady[rret];
        for (int i = 0; i < wq_size && rret > 0; ++i) { 
            if (pfds[i].revents & POLLIN) {
                waitingReady[rret - 1] = i;
                --rret;
            }
        }
        for (int i = 0; i < sizeToMinus; ++i) { 
            int index = waitingReady[i];
            ready_queue[rq_size] = waiting_queue[index];
            if (index != (wq_size - 1)){
                waiting_queue[index] = waiting_queue[wq_size - 1];
            }
            waiting_queue[wq_size - 1] = NULL;
            ++rq_size;
            --wq_size;
        }
    }
    if (jumpReturn == 1){
        if (rq_current == (rq_size - 1))
            rq_current = 0;
        else
            ++rq_current;
    }
    else if (jumpReturn == 2){
        waiting_queue[wq_size] = ready_queue[rq_current];
        if (rq_current != (rq_size - 1)){
            ready_queue[rq_current] = ready_queue[rq_size - 1];
        }
        ready_queue[rq_size - 1] = NULL;
        if (rq_current == (rq_size - 1))
            rq_current = 0;
        ++wq_size;
        --rq_size;
    }
    else if (jumpReturn == 3){
        free(ready_queue[rq_current]);
        if (rq_current != (rq_size - 1)){
            ready_queue[rq_current] = ready_queue[rq_size - 1];
        }
        ready_queue[rq_size - 1] = NULL;
        if (rq_current == (rq_size - 1))
            rq_current = 0;
        ++wq_size;
        --rq_size;
    }
    if (rq_size == 0 && wq_size != 0){
        struct pollfd pfds[wq_size];
        for (int i = 0; i < wq_size; ++i) {
            pfds[i].fd = waiting_queue[i]->fd;
            pfds[i].events = POLLIN;
        }
        int rret = poll(pfds, wq_size, 60);
        int sizeToMinus = rret;
        if (rret == -1) {
            perror("poll");
            exit(-1);
        }
        if (rret > 0) {
            int waitingReady[rret];
            for (int i = 0; i < wq_size && rret > 0; ++i) { 
                if (pfds[i].revents & POLLIN) {
                    waitingReady[rret - 1] = i;
                    --rret;
                }
            }
            for (int i = 0; i < sizeToMinus; ++i) { 
                int index = waitingReady[i];
                ready_queue[rq_size] = waiting_queue[index];
                if (index != (wq_size - 1)){
                    waiting_queue[index] = waiting_queue[wq_size - 1];
                }
                waiting_queue[wq_size - 1] = NULL;
                ++rq_size;
                --wq_size;
            }
        }
    }
    else if (rq_size == 0 && wq_size == 0)
        return;
    else {
        siglongjmp(RUNNING->environment, 1);
    }
}
