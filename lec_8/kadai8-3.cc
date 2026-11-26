#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    srandom((unsigned)time(NULL));
    const int loop = 65536, N = 65536;
    float x[N], y[N], z[N];

    for(int i = 0; i < N; i++){
        x[i] = (float)random()/RAND_MAX;
        y[i] = (float)random()/RAND_MAX;
    }

    clock_t start = clock();
    for(int i = 0; i < loop; i++){
        for(int j = 0; j < N; j++){
            z[j] = x[j] + y[j];
        }
    }
    clock_t end = clock();
    printf("time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < loop; i++){
        z[0] = x[0];
        for(int j = 1; j < N; j++){
            z[j] = z[j-1] + x[j];
        }
    }
    end = clock();
    printf("time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}