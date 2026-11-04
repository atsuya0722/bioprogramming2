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

void CalCorrelation(vector<vector<double>>& expression_matrix, vector<string>& gene_name, int& filtered_num_genes){
    vector<double> mean(filtered_num_genes,0);
    vector<double> disp_sum(filtered_num_genes,0);

    for(int i=0; i<filtered_num_genes; i++){
        for(int j=0; j<NUM_TISSUES; j++){
            mean[i]+=expression_matrix[i][j];
        }
        mean[i] /= NUM_TISSUES;

        for(int j=0; j<NUM_TISSUES; j++){
            disp_sum[i]+=pow(expression_matrix[i][j]-mean[i],2);
        }
    }

    for(int i=0; i<filtered_num_genes; i++){
        for(int k=i+1; k<filtered_num_genes; k++){
            double numerator=0;
            for(int j=0; j<NUM_TISSUES; j++){
                numerator+=(expression_matrix[i][j]-mean[i])*(expression_matrix[k][j]-mean[k]);
            }
            double denominator=sqrt(disp_sum[i]*disp_sum[k]);
            if(denominator==0){
                continue;
            }
            double correlation=numerator/denominator;
            if(correlation>0.999){

                cout << gene_name[i] << " と " << gene_name[k] << " : "  << correlation << endl;
            }
        }
    }
}

void Pretreatment(vector<vector<double>>& expression_matrix, vector<string>& gene_name, vector<vector<double>>& filtered_matrix, vector<string>& filtered_gene_name, int& filtered_num_genes){
    vector<int> count(NUM_GENES,0);
    vector<double> mean(NUM_GENES,0);
    vector<double> disp(NUM_GENES,0);
    for(int i=0; i<NUM_GENES; i++){
        for(int j=0; j<NUM_TISSUES; j++){
            if(expression_matrix[i][j]<1){
                count[i]++;
            }
            mean[i]+=expression_matrix[i][j];
        }
        mean[i] /= NUM_TISSUES;

        for(int j=0; j<NUM_TISSUES; j++){
            disp[i]+=pow(expression_matrix[i][j]-mean[i],2)/NUM_TISSUES;
        }
    }
    
    for(int i=0; i<NUM_GENES; i++){
        if(disp[i]>100 && count[i]<NUM_TISSUES*0.8){
            vector<double> temp;
            for(int j=0; j<NUM_TISSUES; j++){
                if(expression_matrix[i][j]>100){
                    expression_matrix[i][j]=100;
                }
                temp.push_back(expression_matrix[i][j]);
            }
            filtered_matrix.push_back(temp);
            filtered_gene_name.push_back(gene_name[i]);
        }
    }
    filtered_num_genes=filtered_gene_name.size();
}

int main(void){
    vector<string> tissue_name(NUM_TISSUES, "");
    vector<string> gene_name(NUM_GENES, "");
    vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
    LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);

    vector<vector<double>> filtered_matrix;
    vector<string> filtered_gene_name;
    int filtered_num_genes;
    Pretreatment(expression_matrix, gene_name, filtered_matrix, filtered_gene_name,filtered_num_genes);
    cout << filtered_matrix.size() << endl;
    CalCorrelation(filtered_matrix, filtered_gene_name, filtered_num_genes);
    return 0;
}

//MTND2P28 と NDUFS5 : 1
//MTND2P28 と EEF1B2 : 1
//MTND2P28 と EIF4A2 : 1
//MTND2P28 と RPL9 : 1
//MTND2P28 と RPL34 : 1
//MTND2P28 と TOMM6 : 1
//MTND2P28 と RPL7 : 1