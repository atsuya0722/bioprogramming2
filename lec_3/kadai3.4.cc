#include<iostream>
#include<cmath>
using namespace std;

double f1(double x){
    return exp(x)+x-5;
}

double df1(double x){
    return exp(x)+1;
}

double f2(double x){
    return cbrt(x);
}

double df2(double x){
    return 1/(3*pow(cbrt(x),2));
}


int main(void){
    double error=1e-12;
    double count1=0;
    double x1_n=0;
    double x1_n1=x1_n-f1(x1_n)/df1(x1_n);
    count1++;
    while(fabs(x1_n1-x1_n)>error){
        x1_n=x1_n1;
        x1_n1=x1_n-f1(x1_n)/df1(x1_n);
        count1++;
    }
    cout << x1_n1 << endl << count1 << endl;

    double count2=0;
    double x2_n=-0.1;
    double x2_n1=x2_n-f2(x2_n)/df2(x2_n);
    count2++;
    while(fabs(x2_n1-x2_n)>error){
        x2_n=x2_n1;
        x2_n1=x2_n-f2(x2_n)/df2(x2_n);
        count2++;
    }
    cout << x2_n1 << endl << count2 << endl;

    return 0;
    
}

//f1(x)の解は1.30656　繰返し回数は7回で二分法に比べて少なかった。
//f2(x)の解は-nanとなり求まらなかった。繰り返し回数は1028回。
//f2(x)のグラフの形から考えるとニュートン法を用いると解であるx=0からxn+1がどんどん離れてしまうためだと考えられる。