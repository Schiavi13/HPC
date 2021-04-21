#include <stdio.h>
#include <omp.h>

void simple(int n, float *a, float *b){
    int i;
    printf("%d\n",i);
    #pragma omp parallel for 
    for (i=1; i<n; i++) /* i is private by default */{
        b[i] = (a[i] + a[i-1]) / 2.0;
        printf("Thread#: %d b[%d] = %f\n", omp_get_thread_num(),i,b[i]);
    }
    printf("%d\n",i);
}

int main(){
    int n=3;
    float a[]={1.0, 2.0, 3.0};
    float b[3];
    simple(n,a,b);
    return 0;
}