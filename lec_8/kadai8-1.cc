#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    const int loop=65536, n=8192;
    float a[n], b[n], c[n], d[n];
    float invb[n], invd[n];
    
    for(int i=0; i<n; i++){
        a[i]=(float)random()/RAND_MAX;
        b[i]=(float)random()/RAND_MAX+0.1f;
        c[i]=(float)random()/RAND_MAX;
        d[i]=(float)random()/RAND_MAX+0.1f;

        invb[i]=1.0f/b[i];
        invd[i]=1.0f/d[i];
    }

    clock_t start, end;
    double sum;
    start=clock();
    sum=0.0;
    for(int i=0; i<loop; i++){
        for(int j=0; j<n; j++){
            sum+=(a[j]+b[j])*(c[j]+d[j]);
        }
    }
    end=clock();
    printf("sum1=%f\n", (float)sum);
    printf("time1:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}