#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <sstream>
#include <cmath>
using namespace std;
// ������� ��� ������ �������
void printMatrix(const  vector< vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// ������� ��� ������ �������� ������� � ������� ������ ������
vector<vector<double>> findInverseMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    vector<vector<double>> augmentedMatrix(n, vector<double>(2 * n, 0.0));

    // ������� ����������� �������, ��� ������ �� ������������ ������� ����� ��������� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = matrix[i][j];
        }
        augmentedMatrix[i][i + n] = 1.0;
    }

    // �������� ����������� ������� � ������������ ����
    for (int i = 0; i < n; i++) {
        // �������� ������� �������
        int pivotRow = i;
        for (int j = i + 1; j < n; j++) {
            if (augmentedMatrix[j][i] > augmentedMatrix[pivotRow][i]) {
                pivotRow = j;
            }
        }

        // ������ ������ �������, ���� ������� ������� �� �� ������� ���������
        if (pivotRow != i) {
            swap(augmentedMatrix[i], augmentedMatrix[pivotRow]);
        }

        // ����������� ������
        double pivotElement = augmentedMatrix[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[i][j] /= pivotElement;
        }

        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = augmentedMatrix[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
                }
            }
        }
    }

    // ��������� �������� ������� �� ����������� �������
    vector<vector<double>> inverseMatrix(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverseMatrix[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return inverseMatrix;
}


// ������� ��� ������ ������� �� ���������� �����
vector< vector<double>> readMatrixFromFile(const  string& filename) {
    ifstream file(filename);
    vector< vector<double>> matrix;
    string line;

    while (getline(file, line)) {
        vector<double> row;
        istringstream iss(line);
        double value;

        while (iss >> value) {
            row.push_back(value);
        }

        matrix.push_back(row);
    }

    return matrix;
}


// ������� ��� ��������� ������� �� ������
vector<double> matrixVectorMultiply(const vector<vector<double>>& matrix, const vector<vector<double>>& freec) {
    int rows = matrix.size();
    int cols = matrix[0].size();


    vector<double> result(rows, 0.0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * freec[0][j];
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // ������ �������������
    vector< vector<double>> matrix = readMatrixFromFile("matrix.txt");
    vector< vector<double>> freec = readMatrixFromFile("free.txt");

    cout << "�������� �������:" << endl;
    printMatrix(matrix);
    cout << '\n';
    vector< vector<double>> inverseMatrix = findInverseMatrix(matrix);

    cout << "�������� �������:" << endl;
    printMatrix(inverseMatrix);
    cout << "��������� ������������:" << endl;
    printMatrix(freec);
    vector<double> roots = matrixVectorMultiply(inverseMatrix, freec);
    cout << "��������� �����:" << endl;
    for (const auto& root : roots) {
        cout << root << endl;
    }

    return 0;
}
