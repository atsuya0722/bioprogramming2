#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <limits>
using namespace std;

vector<double> SeqToVector(string seq) {
    string aa_order = "ACDEFGHIKLMNPQRSTVWY";

    map<char, int> aa_to_index;
    for (int i = 0; i < 20; i++) {
        aa_to_index[aa_order[i]] = i;
    }

    vector<double> aa_prob(400, 0.0);

    for (int i = 0; i < 29; i++) {
        int a = aa_to_index[seq[i]];
        int b = aa_to_index[seq[i + 1]];
        int index = a * 20 + b;

        aa_prob[index] += 1.0 / 29;
    }

    return aa_prob;
}

void LoadData(string filename, vector<vector<double>>& data, vector<int>& labels){
    ifstream ifs(filename);

    if (!ifs) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }

    int n;
    ifs >> n;

    for (int i = 0; i < n; i++) {
        string seq;
        int label;

        ifs >> seq >> label;

        data.push_back(SeqToVector(seq));
        labels.push_back(label);
    }
}

double Distance(const vector<double>& x, const vector<double>& y){
    double sum = 0.0;

    for (int i = 0; i < 400; i++) {
        sum += pow(x[i] - y[i], 2);
    }

    return sqrt(sum);
}

int Predict(const vector<double>& test, const vector<vector<double>>& train_data, const vector<int>& train_labels){
    int k=1;
    vector<double> min_dists(k,numeric_limits<double>::max());
    vector<int> min_labels(k,0);
    int prediction = 0;

    for (int i = 0; i < train_data.size(); i++) {
        double dist = Distance(test, train_data[i]);

        for(int j = 0; j < k; j++){
            if (dist < min_dists[j]){
                for(int l = k-1; l > j; l--){
                    min_dists[l] = min_dists[l-1];
                    min_labels[l] = min_labels[l-1];
                }
                min_dists[j]=dist;
                min_labels[j]=train_labels[i];
                break;
            }
        }
    }
    
    int count0=0, count1=0;

    for(int i = 0; i < k; i++){
        if(min_labels[i] == 0){
            count0++;
        }
        if(min_labels[i] == 1){
            count1++;
        }
    }

    if(count0 > count1){
        prediction = 0;
    }
    if(count0 < count1){
        prediction = 1;
    }

    return prediction;
}

int main() {
    vector<vector<double>> train_data;
    vector<vector<double>> test_data;
    vector<int> train_labels;
    vector<int> test_labels;

    LoadData("train_mitochondrion_cytoplasm_dataset.txt",
             train_data, train_labels);

    LoadData("test_mitochondrion_cytoplasm_dataset.txt",
             test_data, test_labels);

    int TP = 0, TN = 0, FP = 0, FN = 0;

    for (int i = 0; i < test_data.size(); i++) {
        int pred = Predict(test_data[i],
                           train_data, train_labels);

        int actual = test_labels[i];
        if (actual == 1 && pred == 1){
            TP++;
        }
        if (actual == 0 && pred == 0){
            TN++;
        } 
        if (actual == 0 && pred == 1){
            FP++;
        } 
        if (actual == 1 && pred == 0){
            FN++;
        }
    }
    double sensitivity = (double)TP / (TP + FN);
    double specificity = (double)TN / (TN + FP);

    double BA = (sensitivity + specificity) / 2.0;

    cout << "TP: " << TP << endl;
    cout << "TN: " << TN << endl;
    cout << "FP: " << FP << endl;
    cout << "FN: " << FN << endl;
    cout << "Balanced Accuracy: " << BA << endl;

    return 0;
}


/*
k=1
TP: 94
TN: 463
FP: 90
FN: 93
Balanced Accuracy: 0.669963

k=3
TP: 87
TN: 482
FP: 71
FN: 100
Balanced Accuracy: 0.668425

k=5
TP: 89
TN: 496
FP: 57
FN: 98
Balanced Accuracy: 0.686431

k=7
TP: 83
TN: 505
FP: 48
FN: 104
Balanced Accuracy: 0.678525*/