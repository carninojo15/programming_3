#ifndef _RINGBUF_H_
#define _RINGBUF_H_

#include <pthread.h>

struct ringbuf_t {
  pthread_mutex_t mutex; /* lock to protect from simutaneous access to the buffer */
  pthread_cond_t cond_full; /* producer needs to wait when the buffer is full */
  pthread_cond_t cond_empty; /* consumer needs to wait when the buffer is empty */
  int bufsiz; /* size of the buffer; you may use an empty slot to differentiate the situation the buffer is full or empty */
  int front; /* index of the first element */
  int back; /* index next to the last element (or index to the first empty slot) */
  char* buf; /* buffer itself */
};

/* return the pointer to the newl created and initialized ring buffer of the given size */
extern struct ringbuf_t* rb_init(int bufsiz); 

/* reclaim the ring buffer */
extern void rb_finalize(struct ringbuf_t* rb);

/* return the current number of elements in the buffer */
extern int rb_size(struct ringbuf_t* rb);

/* return non-zero (true) if the buffer is currently full */
extern int rb_is_full(struct ringbuf_t* rb);

/* return non-zero (true) if the buffer is currently empty */
extern int rb_is_empty(struct ringbuf_t* rb);

/* insert (i.e., append) a character into the buffer; if the buffer is full, the caller thread will be blocked */
extern void rb_insert(struct ringbuf_t* rb, int c);

/* retrieve a character at the front of the ring buffer; if the buffer is empty, the caller thread will be blocked */
extern int rb_remove(struct ringbuf_t* rb);

#endif /*_RINGBUF_H_*/
