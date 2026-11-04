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

    //平均TPM上位5遺伝子
//FTL 4656.03
//INS 3873.45
//MTATP6P1 3823.68
//PRSS1 3701.7
//REG1A 3628.86

//スコア上位5遺伝子
//AP3S2 4.87987
//POLR2J 4.79708
//C1orf43 4.54716
//NDUFA2 4.39417
//LAMTOR2 4.33042

//AP3S2はAP3複合体の一部を構成するタンパク質であり、ゴルジ体の膜から小胞が出芽する過程を促進し、リソソームへの物質輸送にも直接関与している可能性がある。
//また、BLOC-1複合体と協調して働き、細胞体で形成される小胞の中に輸送対象となる物質を取り込むために必要である。これらの小胞は、神経突起や神経終末へと物質を運搬する。