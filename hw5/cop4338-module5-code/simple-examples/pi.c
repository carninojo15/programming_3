#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct mythread {
  pthread_t id; /* thread id */
  int n; /* number of darts I need to throw */
  int idx; /* thread index (0 .. p-1) */
};

pthread_mutex_t mutex;
int sum = 0;

int calc_darts(int n)
{
  int i, s = 0;
  for(i=0; i<n; i++) {
    double x = (double)rand()/RAND_MAX;
    double y = (double)rand()/RAND_MAX;
    if(sqrt(x*x+y*y) <= 1) s++;
  }
  return s;
}

void* work(void* arg)
{
  struct mythread* myt = (struct mythread*)arg;
  int s = calc_darts(myt->n);
  pthread_mutex_lock(&mutex);
  sum += s;
  pthread_mutex_unlock(&mutex);
  return 0;
}

int main(int argc, char* argv[])
{
  int n, p, i;
  struct mythread* t;

  if(argc != 3) { printf("USAGE: %s n p\n", argv[0]); return -1; }
  n = atoi(argv[1]);
  p = atoi(argv[2]);

  srand(time(0));
  pthread_mutex_init(&mutex, NULL);

  t = (struct mythread*)malloc(p*sizeof(struct mythread));
  for(i=0; i<p; i++) {
    t[i].n = n/p; t[i].idx = i;
    pthread_create(&t[i].id, 0, work, &t[i]);
  }

  for(i=0; i<p; i++) {
    pthread_join(t[i].id, 0);
  }

  printf("pi =~ %lf\n", 4.0*sum/n);

  pthread_mutex_destroy(&mutex);
  free(t);
  return 0;
}
