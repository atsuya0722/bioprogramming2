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

    
    void CalMean(vector<vector<double>>& expression_matrix,vector<double>& mean){
        for(int i=0; i<NUM_GENES; i++){
            double sum=0;
            for(int j=0; j<NUM_TISSUES; j++){
                sum+=expression_matrix[i][j];
            }
            mean[i]=sum/NUM_TISSUES;
        }
    }

    void CalScore(vector<vector<double>>& expression_matrix,vector<double>& mean,vector<double>& score){
        double disp=0;
        for(int i=0; i<NUM_GENES; i++){
            double sum=0;
            for(int j=0; j<NUM_TISSUES; j++){
                sum+=pow(mean[i]-expression_matrix[i][j],2);
            }
            disp=sum/NUM_TISSUES;
            score[i]=mean[i]/(sqrt(disp)+0.01);
        }
    }

    int main(void){
        vector<string> tissue_name(NUM_TISSUES, "");
        vector<string> gene_name(NUM_GENES, "");
        vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
        LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);
        vector<double> mean(NUM_GENES, 0);
        vector<double> score(NUM_GENES, 0);
        CalMean(expression_matrix, mean);
        CalScore(expression_matrix, mean, score);
        vector<int> order(NUM_GENES);

        for(int i=0; i<NUM_GENES; i++){
            order[i] = i;
        }
        sort(order.begin(), order.end(),
            [&](int a, int b){
                return mean[a] > mean[b];
            });

        cout << "平均TPM上位5遺伝子" << endl;

        for(int i=0; i<5; i++){
            cout << gene_name[order[i]] << " "<< mean[order[i]] << endl;
        }
        sort(order.begin(), order.end(),
            [&](int a, int b){
                return score[a] > score[b];
            });

        cout << endl << "スコア上位5遺伝子" << endl;

        for(int i=0; i<5; i++){
            cout << gene_name[order[i]] << " " << score[order[i]] << endl;
        }

        return 0;
    }