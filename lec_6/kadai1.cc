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

    vector<double> aa_prob(20, 0.0);

    for (int i = 0; i < seq.size(); i++) {
        aa_prob[aa_to_index[seq[i]]] += 1.0 / seq.size();
    }

    return aa_prob;
}

void LoadData(
    string filename,
    vector<vector<double>>& data,
    vector<int>& labels
) {
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

double Distance(
    const vector<double>& x,
    const vector<double>& y
) {
    double sum = 0.0;

    for (int i = 0; i < 20; i++) {
        sum += pow(x[i] - y[i], 2);
    }

    return sqrt(sum);
}

int Predict(
    const vector<double>& test,
    const vector<vector<double>>& train_data,
    const vector<int>& train_labels
) {
    double min_dist = numeric_limits<double>::max();
    int prediction = 0;

    for (int i = 0; i < train_data.size(); i++) {
        double dist = Distance(test, train_data[i]);

        if (dist < min_dist) {
            min_dist = dist;
            prediction = train_labels[i];
        }
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

        if (actual == 1 && pred == 1) TP++;
        if (actual == 0 && pred == 0) TN++;
        if (actual == 0 && pred == 1) FP++;
        if (actual == 1 && pred == 0) FN++;
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