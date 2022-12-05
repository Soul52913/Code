#ifndef THREADTOOL
#define THREADTOOL
#include <setjmp.h>
#include <sys/signal.h>

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
    ready_queue[rq_current]->id = id, ready_queue[rq_current]->arg = arg;\
    ready_queue[rq_current]->i = 0, ready_queue[rq_current]->x = 0, ready_queue[rq_current]->y = 0;\
    sprintf(ready_queue[rq_current]->buf, "%d_%s", id, __FUNCTION__);\
    mkfifo(ready_queue[rq_current]->buf, 0700);\
    ready_queue[rq_current]->fd = open(ready_queue[rq_current]->buf, O_RD);
    if (setjmp(ready_queue[rq_current]->environment) == 0){\
        ++rq_size;
        ++rq_current;
        fprintf(stderr, "Initialize");\
    }
}

#define thread_exit() {\
}

#define thread_yield() {\
}

#define async_read(count) ({\
})

#endif // THREADTOOL
