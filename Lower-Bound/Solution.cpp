#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

void readInstance(string filename, int& P, int& numNodes, vector<vector<int>>& matrix01, vector<vector<int>>& matrix02){
    string line;
    istringstream word;
    ifstream instance01(filename, ios::in);
    if (!instance01.good()) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    } else {
        if (!instance01.eof()) {
            getline(instance01, line); // Number of vertices - P
            getline(instance01, line);
            word.str(line);
            word >> numNodes;
            word >> P;
            word.clear();
            matrix01.resize(numNodes, vector<int>(numNodes, 0));
            for (int i = 0; i < numNodes; i++) {
                getline(instance01, line); // 1st matrix
                word.str(line);
                for (int j = 0; word.good(); j++) {
                    word >> matrix01[i][j];
                }
                word.clear();
            }
            // Initialize the cost matrix with zeros
            matrix02.resize(numNodes, vector<int>(numNodes, 0));
            getline(instance01, line);
            // Read costs for each arc
            for (int i = 0; i < numNodes; i++) {
                getline(instance01, line); // 2nd matrix
                word.str(line);
                for (int j = 0; word.good(); j++) {
                    word >> matrix02[i][j];
                }
                word.clear();
            }
        }
    }
}

int calculateTotalCost(vector<vector<int>>& matrix01, vector<vector<int>>& matrix02, int P, int numNodes) {
    
    int min = 0;
    bool test = true;
    int total_cost = 0;
    // Sorting the location array
    while (test){
        test = false;
        for (int i = 0; i < numNodes - 1; i++){
            if (matrix01[i + 1][1] < matrix01[i][1]){
                min = matrix01[i][1];
                matrix01[i][1] = matrix01[i + 1][1];
                matrix01[i + 1][1] = min;
                test = true;
            }
        }
    }
    
    for (int i = 0; i < P; i++){
        total_cost = total_cost + matrix01[i][1];
    }
    // Calculating the total assignment cost for each non-selected vertex
    vector<int> sorted_assignment;
    sorted_assignment.resize(numNodes, 0);
    for (int i = 0; i < numNodes; i++) {
        int min_cost = numeric_limits<int>::max();
        for (int j = 0; j < numNodes ; j++) {
            if (i != j) {
                if (matrix02[i][j] < min_cost){
                    min_cost = matrix02[i][j];
                }
            }
        }
        sorted_assignment[i] = min_cost;
    }
    bool test2 = true;
    int min2 = 0;
    while (test2){
        test2 = false;
        for (int i = 0; i < numNodes - 1; i++){
            if (sorted_assignment[i + 1] < sorted_assignment[i]){
                min2 = sorted_assignment[i];
                sorted_assignment[i] = sorted_assignment[i + 1];
                sorted_assignment[i + 1] = min2;
                test2 = true;
            }
        }
    }
    int assignment_cost = 0;
    for (int i = 0; i < (numNodes - P); i++){
        assignment_cost = assignment_cost + sorted_assignment[i];
    }
    cout << "Lower bound: " << assignment_cost + total_cost;
    return 0;
}

int main (){
    int P, numNodes;
    vector<vector<int>> matrix01;
    vector<vector<int>> matrix02;
    readInstance("../Instance/PMCS-200.txt", P, numNodes, matrix01, matrix02);
    int cost = calculateTotalCost(matrix01, matrix02, P, numNodes);
    return 0;
}

