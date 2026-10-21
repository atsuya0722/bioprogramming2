#include<iostream>
#include<cmath>
using namespace std;

double f1(double x){
    return exp(x)+x-5;
}

double f2(double x){
    return cbrt(x);
}

int main(void){
    double error=1e-12;
    double left1=0;
    double right1=2;
    double mid1;
    double fmid1;
    int count1=0;
    while(right1-left1>error){
        mid1=(left1+right1)/2;
        count1++;
        fmid1=f1(mid1);
        if(fmid1<0){
            left1=mid1;
        }else if(fmid1>0){
            right1=mid1;
        }else{
            break;
        }
    }
    cout << mid1 << endl << count1 << endl;

    double left2=-0.1;
    double right2=0.2;
    double mid2;
    double fmid2;
    int count2=0;
    while(right2-left2>error){
        mid2=(left2+right2)/2;
        count2++;
        fmid2=f2(mid2);
        if(fmid2<0){
            left2=mid2;
        }else if(fmid2>0){
            right2=mid2;
        }else{
            break; 
        }
    }
    cout << mid2 << endl << count2 << endl;
    return 0;

}

//f1(x)の解は1.3066　繰返し回数は41回
//f2(x)の解は1.81899e-13　繰返し回数は39回