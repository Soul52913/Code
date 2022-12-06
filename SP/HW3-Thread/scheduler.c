#include "threadtools.h"

/*
 * Print out the signal you received.
 * If SIGALRM is received, reset the alarm here.
 * This function should not return. Instead, call longjmp(sched_buf, 1).
 */
void sighandler(int signo) {
    // TODO
    if (setjmp(sched_buf) == 0){
        
    }
    if( sigismember( &set , SIGQUIT ) )
}

/*
 * Prior to calling this function, both SIGTSTP and SIGALRM should be blocked.
 */
void scheduler() {
    // TODO
}
