#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

// put here what I want thread to share
int count = 0;

pthread_mutex_t mutex;

typedef struct mom{
  int mx;
  int mn;
} mom;

struct mythread {
  pthread_t id;
  // int n;
  int idx; 
};

int check_circuit (int z) {
  int v[16];        /* Each element is a bit of z */
  int i;


  for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);
  if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) {
    printf ("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
	    v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
	    v[10],v[11],v[12],v[13],v[14],v[15]);
    return 1;
  } else return 0;
}

void* thread_func(void* arg){
  mom *d;
  d = (mom*)arg;
  int i;
  // printf("min:%d, max:%d\n", d->mn, d->mx);
  pthread_mutex_lock(&mutex);
  for (i = d->mn; i <= d->mx; i++) 
    // note: count needs to be shared between threads
    // but only one should change at once so use mutex
    count += check_circuit(i);
  pthread_mutex_unlock(&mutex);
  // printf("hello from a child thread.\n");
}

int main (int argc, char *argv[]) 
{
  int thr, i, r, z, start, end;
  struct timeval t1, t2;
  void *results;
  mom d;
  // struct mythread* threads;

  // initialize some vars
  z = start = end = 0;

  // sanity checks
  if(argc < 2){
    printf("More arguments expected");
    exit(-1);
  }

  gettimeofday(&t1, 0);
  thr = atoi(argv[1]);
  pthread_t threads[thr];
  z = 65536/thr;
  start = 0;
  end = z;

  pthread_mutex_init(&mutex, NULL);
  // threads = (struct mythread*)malloc(sizeof(struct mythread));
  //change so we only loop for thread count amountend
  for (i = 0; i < thr; i++){
    // set max and min
    d.mx = end;
    d.mn = start;
    // threads[i].idx = i;
    // threads[i].id = threads[i];
    // threads[i].n = thr;
    r = pthread_create(&threads[i], NULL, 
                thread_func, (void*)&d);
    // move this line to thread_func: 
    // count += check_circuit (i);
    start = end + 1;
    end = end + z;
    // printf("start:%d, end:%d\n", start, end);
  }

  // join the threads
  for(int i = 0; i < thr; i++)
    r = pthread_join(threads[i], &results);

  gettimeofday(&t2, 0);

  printf ("Execution time %fs\n", (t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6);
  printf ("There are %d solutions\n", count);
  return 0;
}
