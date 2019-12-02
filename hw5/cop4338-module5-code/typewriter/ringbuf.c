#include <assert.h>
#include <stdlib.h>
#include "ringbuf.h"

static int rb_next_slot(struct ringbuf_t* rb, int idx)
{
  assert(rb);
  assert(0 <= idx && idx < rb->bufsiz);
  idx++;
  if(idx >= rb->bufsiz) return 0;
  return idx;
}

struct ringbuf_t* rb_init(int bufsiz)
{
  struct ringbuf_t* rb;

  if(bufsiz <= 1) return 0; /* bufsiz must be greater than 1 */

  rb = (struct ringbuf_t*)malloc(sizeof(struct ringbuf_t));
  if(!rb) return 0; /* problem with memory allocation */
  
  rb->buf = (char*)malloc(bufsiz);
  if(!rb->buf) return 0; /* problem with memory allocation */

  pthread_mutex_init(&rb->mutex, NULL);
  pthread_cond_init(&rb->cond_full, NULL);
  pthread_cond_init(&rb->cond_empty, NULL);
  rb->bufsiz = bufsiz;
  rb->front = rb->back = 0;

  return rb;
}

void rb_finalize(struct ringbuf_t* rb)
{
  assert(rb && rb->buf);
  free(rb->buf);
  free(rb);
}

int rb_size(struct ringbuf_t* rb)
{
  assert(rb);
  if(rb->back < rb->front) return rb->back+rb->bufsiz-rb->front;
  else return rb->back-rb->front;
}

int rb_is_full(struct ringbuf_t* rb)
{
  assert(rb);
  return rb_size(rb) == rb->bufsiz-1; /*(rb->front == rb_next_slot(rb, rb->back));*/
}

int rb_is_empty(struct ringbuf_t* rb)
{
  assert(rb);
  return !rb_size(rb); /*(rb->front == rb->back);*/
}

void rb_insert(struct ringbuf_t* rb, int c)
{
  int was_empty;

  assert(rb);
  pthread_mutex_lock(&rb->mutex);
  while(rb_is_full(rb))
    pthread_cond_wait(&rb->cond_full, &rb->mutex);
  was_empty = rb_is_empty(rb);
  rb->buf[rb->back] = (char)c;
  rb->back = rb_next_slot(rb, rb->back);
  if(was_empty) pthread_cond_broadcast(&rb->cond_empty);
  pthread_mutex_unlock(&rb->mutex);
}

int rb_remove(struct ringbuf_t* rb)
{
  int was_full;
  int c;

  assert(rb);
  pthread_mutex_lock(&rb->mutex);
  while(rb_is_empty(rb))
    pthread_cond_wait(&rb->cond_empty, &rb->mutex);
  was_full = rb_is_full(rb);
  c = (int)rb->buf[rb->front];
  rb->front = rb_next_slot(rb, rb->front);
  if(was_full) pthread_cond_broadcast(&rb->cond_full);
  pthread_mutex_unlock(&rb->mutex);

  return c;
}
