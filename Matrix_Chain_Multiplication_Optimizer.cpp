/*
 * Matrix Chain Multiplication Optimizer
 *
 * Author:       Parsa Zamani
 * Degree:       Bachelor's in Computer Engineering
 * University:   University of Kurdistan
 * GitHub:       @parsazamani1383
 * Date:         2025-06-11
 *
 * Description:
 *  This program computes the optimal parenthesization of a sequence of matrices
 *  using dynamic programming to minimize the total number of scalar multiplications.
 *  It supports both manual and random input, displays DP tables, computes the Catalan number,
 *  and saves the results to a text file.
 */

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

/*
 * MatrixChainOptimizer:
 * A class to perform matrix chain multiplication optimization using dynamic programming.
 */
class MatrixChainOptimizer {
private:
    vector<int> P;               // Array of matrix dimensions
    vector<vector<int>> m;       // Table to store minimum multiplication costs
    vector<vector<int>> s;       // Table to store split points
    int n;                       // Number of matrices

public:
    // Constructor: initializes with the dimensions array
    MatrixChainOptimizer(const vector<int>& dims) {
        P = dims;
        n = dims.size() - 1;
        m.resize(n + 1, vector<int>(n + 1, 0));
        s.resize(n + 1, vector<int>(n + 1, 0));
    }

    // Performs dynamic programming to compute the optimal multiplication order
    void computeOptimalOrder() {
        for (int i = 1; i <= n; ++i)
            m[i][i] = 0;

        for (int L = 2; L <= n; ++L) {
            for (int i = 1; i <= n - L + 1; ++i) {
                int j = i + L - 1;
                m[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    int q = m[i][k] + m[k + 1][j] + P[i - 1] * P[k] * P[j];
                    if (q < m[i][j]) {
                        m[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
    }

    // Recursively prints the optimal parenthesization
    void printOptimalParenthesis(int i, int j, ostream& out) {
        if (i == j)
            out << "A" << i;
        else {
            out << "(";
            printOptimalParenthesis(i, s[i][j], out);
            out << " x ";
            printOptimalParenthesis(s[i][j] + 1, j, out);
            out << ")";
        }
    }

    // Optionally displays the DP tables m and s
    void displayTables(bool show = true) {
        if (!show) return;
        cout << "\nTable m (costs):\n";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i > j) cout << "   -   ";
                else cout << m[i][j] << "\t";
            }
            cout << endl;
        }

        cout << "\nTable s (splits):\n";
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i >= j) cout << "  -  ";
                else cout << s[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Saves results to a specified text file
    void saveToFile(const string& filename) {
        ofstream fout(filename);
        fout << "Matrix dimensions (P): ";
        for (int p : P) fout << p << " ";
        fout << "\n\nMinimum multiplication cost: " << m[1][n] << "\n";
        fout << "Optimal parenthesization: ";
        printOptimalParenthesis(1, n, fout);
        fout << "\nCatalan number (n = " << n << "): " << catalanNumber(n) << "\n";
        fout.close();
        cout << "\nResults saved to file: " << filename << endl;
    }

    // Returns the minimum cost of multiplication
    int getMinCost() {
        return m[1][n];
    }

    // Prints the optimal parenthesization to console
    void printOptimalParenthesisToConsole() {
        printOptimalParenthesis(1, n, cout);
        cout << endl;
    }

    // Static method to calculate the nth Catalan number
    static long long catalanNumber(int n) {
        if (n <= 1) return 1;
        vector<long long> cat(n + 1, 0);
        cat[0] = cat[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                cat[i] += cat[j] * cat[i - j - 1];
        return cat[n];
    }
};

// Utility function to generate a random dimension array
vector<int> generateRandomDimensions(int n, int minDim = 1, int maxDim = 1000) {
    vector<int> P(n + 1);
    for (int i = 0; i <= n; ++i)
        P[i] = minDim + rand() % (maxDim - minDim + 1);
    return P;
}

// Main program: handles user input and coordinates the process
int main() {
    srand(time(0));  // Seed random number generator

    int mode;
    cout << "Matrix Chain Multiplication\n";
    cout << "1. Manual input\n";
    cout << "2. Random input\n";
    cout << "Choose input mode (1 or 2): ";
    cin >> mode;

    vector<int> P;
    int numMatrices;

    if (mode == 1) {
        cout << "Enter number of matrices: ";
        cin >> numMatrices;
        cout << "Enter dimensions array P (size = " << numMatrices + 1 << "):\n";
        P.resize(numMatrices + 1);
        for (int i = 0; i <= numMatrices; ++i) {
            cin >> P[i];
        }
    } else {
        numMatrices = 5 + rand() % 11;  // [5, 15]
        P = generateRandomDimensions(numMatrices);
        cout << "Randomly generated " << numMatrices << " matrices.\nDimensions P: ";
        for (int val : P) cout << val << " ";
        cout << endl;
    }

    MatrixChainOptimizer optimizer(P);
    optimizer.computeOptimalOrder();

    cout << "\nMinimum number of multiplications: " << optimizer.getMinCost() << endl;
    cout << "Optimal parenthesization: ";
    optimizer.printOptimalParenthesisToConsole();
    cout << "Catalan number: " << MatrixChainOptimizer::catalanNumber(numMatrices) << endl;

    // Ask if user wants to see the DP tables
    char showTables;
    cout << "\nShow DP tables? (y/n): ";
    cin >> showTables;
    if (showTables == 'y' || showTables == 'Y') {
        optimizer.displayTables(true);
    }

    // Save results to file
    optimizer.saveToFile("matrix_chain_output.txt");

    return 0;
}
