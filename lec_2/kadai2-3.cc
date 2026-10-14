#include <iostream>
#include <vector>
#include <string>
using namespace std;

double CalcGCContent(string seq){
    double count=0;
    for(int i=0; i<seq.length(); i++){
        if(seq[i]=='G' || seq[i]=='C'){
            count++;
        }
    }
    return count/seq.length()*100;
}

int main(void){
    vector<string> sequences = {
        "ATGCGAT",
        "GCGCGCGC",
        "ATATATAC",
        "CCCGGGTT",
        "TTAACCGA"
    };


    vector<string> high_gc_sequences; 
    for(int i=0; i<sequences.size(); i++){
        if(CalcGCContent(sequences[i])>=50){
            high_gc_sequences.push_back(sequences[i]);
        }
    }
    
    cout << "GC含量が50%以上の配列：" << endl;
    for(int i = 0; i < high_gc_sequences.size();i++){
        cout << high_gc_sequences[i] << endl;
    }
    return 0;
} 