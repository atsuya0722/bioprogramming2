#include<iostream>
#include<fstream>
#include<vector>
#include<string>
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
            for(int j=0; j<NUM_TISSUES; j++){
                if(max_tpm[i]<expression_matrix[i][j]){
                    max_tpm[i]=expression_matrix[i][j];               
                }
            }
        }

        vector<double> unique_index(NUM_GENES,0);
        for(int i=0; i<NUM_GENES; i++){
            double sum=0;
            for(int j=0; j<NUM_TISSUES; j++){
                sum+=1-expression_matrix[i][j]/max_tpm[i];
            }
            unique_index[i]=sum/(NUM_TISSUES-1);
        }

        vector<int> unique_count(NUM_TISSUES,0);
        for(int i=0; i<NUM_GENES; i++){
            if(unique_index[i]>=0.85){
                int max_tissue_num=0;
                double max_tissue_value=0;
                for(int j=0; j<NUM_TISSUES; j++){
                    if(max_tissue_value < expression_matrix[i][j]){
                        max_tissue_value=expression_matrix[i][j];
                        max_tissue_num=j;
                    }
                }
                unique_count[max_tissue_num]++;
            }
        }
        
        int unique_max_tissue=max_element(unique_count.begin(), unique_count.end())-unique_count.begin();
        cout << "もっとも組織特異的発現遺伝子数が多い組織は" << tissue_name[unique_max_tissue] << endl;

        for(int i=0; i<NUM_GENES; i++){
            if(unique_index[i]>=0.95 && expression_matrix[i][unique_max_tissue]>=1000){
                cout << gene_name[i] << endl;
            }
        }
    }

//もっとも組織特異的発現遺伝子数が多い組織はTestis
//Testisにおいて特異性が高く、TPM1000以上の遺伝子
//SMCP
//LELP1
//TNP1
//PHF7
//CRISP2
//PRM2
//PRM1
//CMTM2
//YBX2
