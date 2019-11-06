#include<stdio.h>

int rand(void);
void srand(unsigned int seed);
void shellsort(int v[], int n);

int main(){
    int arr[10];
    for(int i=0;i<9;i++)
        arr[i] = 0;
    srand(12345);
    printf("Before shellsort:\n");
    for(int i=0;i<9;i++){
        arr[i] = rand();
        printf("%d\n", arr[i]);
    }

    int n = sizeof(arr)/sizeof(arr[0]);

    printf("After decreasing shellsort:\n");
    shellsort(arr, n);
    for(int i=0;i<9;i++)
        printf("%d\n", arr[i]);

    return 0;
}

unsigned long int next = 1;
int rand(void){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

/* srand: set seed for rand() */
void srand(unsigned int seed){
    next = seed;
}

void shellsort(int v[], int n){
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j>=0 && v[j]<v[j+gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
 }
