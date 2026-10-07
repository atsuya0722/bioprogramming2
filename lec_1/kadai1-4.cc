#include <iostream>
using namespace std;

class Matrix{
public:
    double a,b,c,d;
    void set(double x, double y, double z, double w){
        a=x;
        b=y;
        c=z;
        d=w;
    }
    Matrix add(Matrix &q){
        Matrix m;
        m.a=a+q.a;
        m.b=b+q.b;
        m.c=c+q.c;
        m.d=d+q.d;
        return(m);
    }
    Matrix mult(Matrix &q){
        Matrix m;
        m.a=a*q.a+b*q.c;
        m.b=a*q.b+b*q.d;
        m.c=c*q.a+d*q.c;
        m.d=c*q.b+d*q.d;
        return(m);
    }
    double trace(void){
        return a+d;
    }
    Matrix inverse_matrix(void){
        Matrix m;
        double coefficient=1/(a*d-b*c);
        m.a=coefficient*d;
        m.b=coefficient*(-b);
        m.c=coefficient*(-c);
        m.d=coefficient*a;
        return(m);
    }
};
 
int main(void){
    Matrix p,q;
    p.set(1, 2, 3, 4);
    q.set(5, 6, 7, 8);
    Matrix r,s;
    r=p.add(q);
    s=p.mult(q);
    double a,b;
    a=p.trace();
    b=q.trace();
    Matrix c,d;
    c=p.inverse_matrix();
    d=q.inverse_matrix();
    cout << r.a <<" "<< r.b << endl << r.c << " " << r.d << endl; 
    cout << s.a <<" "<< s.b << endl << s.c << " " << s.d << endl; 
    cout << a << endl;
    cout << b << endl;
    cout << c.a <<" "<< c.b << endl << c.c << " " << c.d << endl; 
    cout << d.a <<" "<< d.b << endl << d.c << " " << d.d << endl;
    return 0;
}