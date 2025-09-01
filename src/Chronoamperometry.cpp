#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Define constants
const double R = 8.3144621;  // Universal gas constant (J/(mol K))
const double F = 96485.3415;  // Faraday constant (C/mol)
const double T = 298.15;  // Temperature (K)
const double n = 1;  // Number of electrons transferred

// Structure for electrochemical parameters
struct ElectrochemicalParameters {
    double potential;
    double E0;
    double k0;
    double d;
    double c;
};

// Function to calculate current
double current(double potential, double E0, double k0, double d, double c) {
    double io = k0 * exp(-(E0 - potential) / (n * R * T / F));
    double i = io * (1 + pow((d * potential / (n * R * T)), 0.5));

    return i;
}

// Function to read data from a CSV file
vector<ElectrochemicalParameters> read_csv(const string& filename) {
    ifstream data_file(filename);
    vector<ElectrochemicalParameters> data;
    string line, word;

    if (!data_file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    while (getline(data_file, line)) {
        stringstream s(line);
        ElectrochemicalParameters params;
        getline(s, word, ','); params.potential = stod(word);
        getline(s, word, ','); params.E0 = stod(word);
        getline(s, word, ','); params.k0 = stod(word);
        getline(s, word, ','); params.d = stod(word);
        getline(s, word, ','); params.c = stod(word);
        data.push_back(params);
    }

    return data;
}

// Simulate chronoamperometry
void chronoamperometry(const vector<ElectrochemicalParameters>& params) {
    // Iterate over each set of parameters
    for (const auto& p : params) {
        ofstream data_file("chronoamperometry_data_" + to_string(p.potential) + ".txt");
        for (int t = 0; t < 1000; t++) { // Assuming a fixed time duration
            double current_value = current(p.potential, p.E0, p.k0, p.d, p.c);
            data_file << t << " " << current_value << endl;
        }
        data_file.close();
    }
}

// Main function
int main() {
    string filename = "electrochemical_data.csv";  // Replace with your CSV file name
    vector<ElectrochemicalParameters> csv_data = read_csv(filename);

    // Simulate chronoamperometry with the read parameters
    chronoamperometry(csv_data);

    return 0;
}
