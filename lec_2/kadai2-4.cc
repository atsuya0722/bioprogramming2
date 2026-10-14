#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

int main(void){
    map<string, int> interaction_num;
    ifstream ist ("human_protein_interaction.txt");
    if(!ist){
        cout << "Cannot open human_protein_interaction.txt" << endl;
        exit(1);
    }
    string line;
    while(getline(ist,line)){
        int space=line.find(" ");
        string protein1=line.substr(0,space);
        string protein2=line.substr(space+1);
        interaction_num[protein1]++;
        interaction_num[protein2]++;
    }
    ist.close();
    string max_protein;
    int max_interaction=0;
    for(map<string,int>::const_iterator it = interaction_num.begin(); it != interaction_num.end(); it++){
        if(it->second > max_interaction){
            max_protein=it->first;
            max_interaction=it->second;
        }
    }
    cout << max_protein << ' ' << endl << max_interaction << endl;
    return 0;
}

