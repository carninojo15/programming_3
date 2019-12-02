#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
float balance = 100;

struct mystruct { float amt; };

void* access(void* arg)
{
  struct mystruct* x = (struct mystruct*)arg;

  printf("trying to add %f to account (with balance=%f)\n", x->amt, balance);
  pthread_mutex_lock(&mutex);
  balance += x->amt;
  pthread_mutex_unlock(&mutex);
  printf("final balance=%f\n", balance);

  return 0;
}

int main()
{
  pthread_t t0, t1;

  struct mystruct* x = (struct mystruct*)malloc(sizeof(struct mystruct));
  struct mystruct* y = (struct mystruct*)malloc(sizeof(struct mystruct));
  x->amt = -10;
  y->amt = 30;

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&t0, NULL, access, (void*)x);
  pthread_create(&t1, NULL, access, (void*)y);
  
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);

  free(x); free(y);
  printf("final final balance=%f\n", balance);

  pthread_mutex_destroy(&mutex);

  return 0;
}
