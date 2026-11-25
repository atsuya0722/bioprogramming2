#include<iostream>
#include<string>
using namespace std;

int main(void){
    string s;
    cin >> s;
    int count=1;
    for(int i=1; i<s.size(); i++){
        if(s[i-1]==s[i]){
            count++;
        }
        if(s[i-1]!=s[i]){
            cout << s[i-1] << count;
            count=1;
        }
        if(i==s.size()-1){
            cout << s[i] << count;
        }
    }
    return 0;
}