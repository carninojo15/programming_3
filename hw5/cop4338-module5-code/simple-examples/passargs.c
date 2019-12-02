#include <stdio.h>
#include <pthread.h>

struct mystruct {
  int id;
  char* msg;
};

void* printhello(void* arg)
{
  struct mystruct* s = (struct mystruct*)arg;

  if(!s->id) {
    int i; float x = 1;
    for(i=0; i<1000000; i++) x = x*x;
  }
  printf("\"%s\" from thread %d\n", s->msg, s->id);
  return 0;
}

struct mystruct s0 = { 0, "this is my string!" };
struct mystruct s1 = { 1, "whatever I want to put here" };

int main()
{
  pthread_t t0, t1;

  pthread_create(&t0, NULL, printhello, (void*)&s0);
  pthread_create(&t1, NULL, printhello, (void*)&s1);
  
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);

  return 0;
}
