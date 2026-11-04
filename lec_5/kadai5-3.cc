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

    void CalCorrelation(vector<vector<double>>& expression_matrix,
    vector<string>& gene_name){

    vector<double> mean(NUM_GENES,0);
    vector<double> disp_sum(NUM_GENES,0);

    for(int i=0; i<NUM_GENES; i++){
        for(int j=0; j<NUM_TISSUES; j++){
            mean[i]+=expression_matrix[i][j];
        }
        mean[i] /= NUM_TISSUES;

        for(int j=0; j<NUM_TISSUES; j++){
            disp_sum[i]+=pow(expression_matrix[i][j]-mean[i],2);
        }
    }

    for(int i=0; i<NUM_GENES; i++){
        for(int k=i+1; k<NUM_GENES; k++){
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

void Pretreatment(vector<vector<double>>& expression_matrix){
    vector<int> count(NUM_GENES,0);
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
    
    vector<vector<double>> filtered;
    for(int i=0; i<NUM_GENES; i++){
        if(count[i]<NUM_TISSUES*0.8 && disp[i]>100){
            
        }
    }
}