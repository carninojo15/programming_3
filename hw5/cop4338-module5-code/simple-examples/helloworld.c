#include <stdio.h>
#include <pthread.h>

void* helloworld(void* p)
{
  printf("hello world (from child thread)!\n");
  return (void*)1;
}

int main()
{
  pthread_t t1;
  void* x;

  pthread_create(&t1, NULL, &helloworld, NULL);
  printf("hello world (from main thread)!\n");


  pthread_join(t1, &x);
  printf("x=%p\n", x);
  return 0;
}
