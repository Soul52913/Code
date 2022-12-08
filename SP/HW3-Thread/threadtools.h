#ifndef THREADTOOL
#define THREADTOOL
#include <setjmp.h>
#include <sys/signal.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define THREAD_MAX 16  // maximum number of threads created
#define BUF_SIZE 512
struct tcb {
    int id;  // the thread id
    jmp_buf environment;  // where the scheduler should jump to
    int arg;  // argument to the function
    int fd;  // file descriptor for the thread
    char buf[BUF_SIZE];  // buffer for the thread
    int i, x, y;  // declare the variables you wish to keep between switches
};

extern int timeslice;
extern jmp_buf sched_buf;
extern struct tcb *ready_queue[THREAD_MAX], *waiting_queue[THREAD_MAX];
/*
 * rq_size: size of the ready queue
 * rq_current: current thread in the ready queue
 * wq_size: size of the waiting queue
 */
extern int rq_size, rq_current, wq_size;
/*
* base_mask: blocks both SIGTSTP and SIGALRM
* tstp_mask: blocks only SIGTSTP
* alrm_mask: blocks only SIGALRM
*/
extern sigset_t base_mask, tstp_mask, alrm_mask;
/*
 * Use this to access the running thread.
 */
#define RUNNING (ready_queue[rq_current])

void sighandler(int signo);
void scheduler();

#define thread_create(func, id, arg) {\
    func(id, arg);\
}

#define thread_setup(id, arg) {\
    ready_queue[rq_size] = malloc(sizeof(struct tcb));\
    ready_queue[rq_size]->id = id, ready_queue[rq_size]->arg = arg;\
    ready_queue[rq_size]->i = 0, ready_queue[rq_size]->x = 0, ready_queue[rq_size]->y = 0;\
    sprintf(RUNNING->buf, "%d_%s", id, __FUNCTION__);\
    mkfifo(RUNNING->buf, 0700);\
    RUNNING->fd = open(RUNNING->buf, O_RDWR | O_NONBLOCK);\
    if (sigsetjmp(RUNNING->environment, 1) == 0){\
        return;\
    }\
}

#define thread_exit() {\
    sprintf(RUNNING->buf, "%d_%s", id, __FUNCTION__);\
    unlink(RUNNING->buf);\
    longjmp(sched_buf, 3);\
}

#define thread_yield() {\
    if (sigsetjmp(RUNNING->environment, 1) == 0){\
        sigprocmask(SIG_SETMASK, &alrm_mask, NULL);\
        sigprocmask(SIG_SETMASK, &tstp_mask, NULL);\
        sigprocmask(SIG_SETMASK, &base_mask, NULL);\
    }\
}

#define async_read(count) ({\
    if (sigsetjmp(RUNNING->environment, 1) == 0){\
        siglongjmp(sched_buf, 2);\
    }\
    else\
        read(RUNNING->fd, RUNNING->buf, count);\
})

#endif // THREADTOOL
