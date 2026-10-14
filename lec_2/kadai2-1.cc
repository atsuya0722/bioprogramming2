#include<iostream>
using namespace std;

class Matrix {
public:
    double a,b,c,d;
    Matrix(){}
    Matrix(double x, double y, double z, double w){
        a=x; b=y;
        c=z; d=w;
    }
    Matrix operator + (const Matrix &q) const{
        Matrix m;
        m.a = a + q.a;
        m.b = b + q.b;
        m.c = c + q.c;
        m.d = d + q.d;
        return(m);
    }
    Matrix operator * (const Matrix &q) const{
        Matrix m;
        m.a = a * q.a + b * q.c;
        m.b = a * q.b + b * q.d;
        m.c = c * q.a + d * q.c;
        m.d = c * q.b + d * q.d;
        return(m);
    }
    bool operator == (const Matrix &q) const {
        if (a==q.a && b==q.b && c==q.c && d==q.d){
            return true;
        }else{
            return false;
        }
    }
};

int main (void){
    Matrix p(1,2,3,4);
    Matrix q(1,2,3,4);
    if(p==q){
        cout << "true" << endl;
    }
    return 0;

}