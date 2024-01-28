#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

// Define constants
const double R = 8.3144621;  // Universal gas constant (J/(mol K))
const double F = 96485.3415;  // Faraday constant (C/mol)
const double T = 298.15;  // Temperature (K)
const double n = 1;  // Number of electrons transferred

// Structure for impedance parameters
struct ImpedanceParameters {
    double omega;
    double Rct;
    double alpha;
    double omegac;
};

// Function to calculate impedance spectrum
complex<double> impedance(double omega, double Rct, double alpha, double omegac) {
    // Calculate impedance using Randles circuit model
    double Zreal = Rct / (1 + pow(omega * Rct, 2) + pow(omega * omegac, 2));
    double Zimag = sqrt(1 - pow(Zreal / Rct, 2));

    // Convert real and imaginary parts to complex impedance
    complex<double> Z(Zreal, Zimag);

    return Z;
}

// Function to read data from a CSV file
vector<ImpedanceParameters> read_csv(const string& filename) {
    ifstream data_file(filename);
    vector<ImpedanceParameters> data;
    string line, word;

    if (!data_file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    while (getline(data_file, line)) {
        stringstream s(line);
        ImpedanceParameters params;
        getline(s, word, ','); params.omega = stod(word);
        getline(s, word, ','); params.Rct = stod(word);
        getline(s, word, ','); params.alpha = stod(word);
        getline(s, word, ','); params.omegac = stod(word);
        data.push_back(params);
    }

    return data;
}

// Main function
int main() {
    string filename = "data.csv";  // Replace with your CSV file name
    vector<ImpedanceParameters> csv_data = read_csv(filename);

    for (const auto& params : csv_data) {
        complex<double> Z = impedance(params.omega, params.Rct, params.alpha, params.omegac);
        cout << "Omega: " << params.omega << ", Impedance: " << Z.real() << " + " << Z.imag() << "i" << endl;
    }

    return 0;
}
