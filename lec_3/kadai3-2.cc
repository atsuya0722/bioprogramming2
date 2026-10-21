#include<iostream>
#include<cmath>
using namespace std;

int main(void){
    float a=1,b=10000,c=1;
    float x1,x2;
    
    if(b>=0){
        x1=(-b-sqrt((b+2*sqrt(a*c))*(b-2*sqrt(a*c))))/(2*a);
        x2=c/a/x1;
    }
    else{
        x1=(-b+sqrt((b+2*sqrt(a*c))*(b-2*sqrt(a*c))))/(2*a);
        x2=c/a/x1;
    }
    cout << x1 << endl << x2 << endl;

    float y1=(-b-sqrt((b*b-4*a*c)))/(2*a);
    float y2=(-b+sqrt((b*b-4*a*c)))/(2*a);
    cout << y1 << endl << y2 << endl;

    return 0;
}

//桁落ちに配慮した場合　解は10000と0.1
//桁落ちに配慮しない場合　解は10000と0