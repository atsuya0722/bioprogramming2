#include<iostream>
#include<string>
using namespace std;

int HammingDistance(string m, string n){
    if(m.length()!= n.length()){
        return -1;
    }
    int count=0;
    for(int i=0; i<m.length();i++){
        if(m[i]!=n[i]){
            count++;
        }
    }    
    return count;
}


int main(void){
    string a = "AACCGT";
    string b = "AATCAT";
    string c = "AACCG";

    int dist1 = HammingDistance(a, b);
    if (dist1 != -1) {
        cout << "Hamming Distance: " << dist1 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }
    int dist2 = HammingDistance(a, c);
    if (dist2 != -1) {
        cout << "Hamming Distance: " << dist2 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }

    return 0;
}
