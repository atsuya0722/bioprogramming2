#include<iostream>
#include <fstream>
using namespace std;

int main(void){
    int a,b;
    cin >> a >> b;
    int sum;
    sum=a+b;
    cout << sum << endl;
    
    ifstream ist ("input.txt");
    if(!ist){
        cout << "Cannot ope input.txt" << endl;
        exit(1);
    }

    string s;
    getline(ist, s);
    ist.close();

    ofstream ost("output.txt");
    if(!ost){
        cerr << "Cannot open output.txt" << endl;
        exit(1);
    }
    ost << s << endl;
    ost.close();
    return 0;
}