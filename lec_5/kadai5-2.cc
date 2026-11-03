#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>

#define NUM_TISSUES 68
#define NUM_GENES 19594

using namespace std;

void LoadExpressionFile(string file_name, vector<string>& tissue_name, vector<string>& gene_name, vector<vector<double>>& expression_matrix){
    
    ifstream ifs(file_name);
    if(!ifs){
        cerr<<"Cannot open expression file:" << file_name << endl;
        exit(1);
    }
    string temp;
    ifs >> temp;

    for(int i=0; i<NUM_TISSUES; i++){
        ifs >> tissue_name[i];
    }

    for(int i=0; i<NUM_GENES; i++){
        ifs >> gene_name[i];
        for(int j=0; j<NUM_TISSUES; j++){
            ifs >> expression_matrix[i][j];
        }
    }
    ifs.close();
    }

     int main(void){
        vector<string> tissue_name(NUM_TISSUES, "");
        vector<string> gene_name(NUM_GENES, "");
        vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
        LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);
        vector<double> max_tpm(NUM_GENES,0);

        for(int i=0; i<NUM_GENES; i++){
            for(int j=0; NUM_TISSUES; j++){
                if(max_tpm[i]<expression_matrix[i][j]){
                    max_tpm[i]=expression_matrix[i][j];                }
            }
        }

        vector<double> unique_index(NUM_GENES,0);
        for(int i=0; i<NUM_GENES; i++){
            int sum=0;
            for(int j=0; j<NUM_TISSUES; j++){
                sum=1-expression_matrix[i][j]/max_tpm[i];
            }
            unique_index[i]=sum/(NUM_TISSUES-1);
        }

        
        for(int i=0, i<NUM_GENES; i++){
            if(unique_index[i]>0.85){
                
            }
        }