#include <stdio.h>
#include "ringbuf.h"

void* producer(void* arg)
{
  struct ringbuf_t* rb = (struct ringbuf_t*)arg;

  int c = getchar();
  do {
    rb_insert(rb, c);
    c = getchar();
  } while(c != EOF);
  rb_insert(rb, -1);
  
  return 0;
}

void* consumer(void* arg)
{
  struct ringbuf_t* rb = (struct ringbuf_t*)arg;

  int c = rb_remove(rb);
  while(c != -1) {
    printf("%c", c);
    c = rb_remove(rb);
  }

  return 0;
}

int main()
{
  pthread_t t0, t1;
  struct ringbuf_t* rb;

  rb = rb_init(10);
  if(!rb) return 0;

  pthread_create(&t0, NULL, producer, (void*)rb);
  pthread_create(&t1, NULL, consumer, (void*)rb);
  
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  
  rb_finalize(rb);
  return 0;
}
