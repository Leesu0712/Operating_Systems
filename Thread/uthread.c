/* uthread.c */

/*************************************************
 * EEE3535-02 Fall 2018                          *
 * School of Electrical & Electronic Engineering *
 * Yonsei University, Seoul, South Korea         *
 *************************************************/

#include "syscall.h"
#include "types.h"
#include "user.h"
#include "x86.h"
#include "thread.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"


// Thread create
int thread_create(thread_t *thread, void(*func)(void*), void *arg) {
   int tid = *(int*)arg;
   thread->tid = tid;

   return tcreate(tid, func, arg);   
}

// Thread join
int thread_join(thread_t thread) {
   int tid = thread.tid;
   
   return tjoin(tid);
}

// Mutex init
void mutex_init(mutex_t *lock) {
   lock->flag = 0;
}

// Mutex lock
void mutex_lock(mutex_t *lock) {
   while(xchg(&lock->flag, 1) == 1)
	yield();
}

// Mutex unlock
void mutex_unlock(mutex_t *lock) {
   lock->flag = 0;
}

