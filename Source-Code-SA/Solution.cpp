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
            getline(instance01, line); // The number of vertices - P
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

void initialize_solution(int numNodes, int P, vector<bool>& solution, int avg, vector<vector<int>>& matrix01){
    // Initialize the random number generator
    srand(time(NULL)); 
    solution.resize(numNodes, false);
    // Randomly select P vertices
    int i = 0;
    while(i < P){
        int vertex;
        // Generate a random vertex not already chosen
        vertex = rand() % numNodes;
        if(!solution[vertex] && matrix01[vertex][1] < avg){
            solution[vertex] = true;
            i++;
        }   
    }
}

int calculateTotalCost(vector<bool>& solution, vector<vector<int>>& matrix01, vector<vector<int>>& matrix02, int P) {
    int numNodes = solution.size();
    int selection_cost = 0;
    int assignment_cost = 0;
    int selected_vertices[P];
    int count = 0;
    // Count the number of selected vertices and store their indices in the selected_vertices array
    for (int i = 0; i < numNodes; i++) {
        if (solution[i]) {
            selected_vertices[count] = i;
            count++;
            selection_cost += matrix01[i][1];  
        }
    }
    // Calculate the total assignment cost for each non-selected vertex
    for (int i = 0; i < numNodes; i++) {
        if (!solution[i]) {
            int min_cost = numeric_limits<int>::max();
            for (int j = 0; j < P; j++) {
                int k = selected_vertices[j];
                int cost = matrix02[i][k];
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
            assignment_cost += min_cost;
        }
    }
    // Calculate the total cost as the sum of selection and assignment costs
    int total_cost = selection_cost + assignment_cost;
    return total_cost;
}

void perform_transition(vector<bool>& solution, int numNodes, int avg, vector<vector<int>>& matrix01, vector<vector<int>>& matrix02, int P) {
    srand(time(NULL));
    int oldCost = calculateTotalCost(solution, matrix01, matrix02, P);
    vector<bool> newSolution;
    newSolution.resize(numNodes, false);
    for(int i = 0; i < numNodes; i++){
        newSolution[i] = solution[i];
    }
    for (int i = 0; i < (numNodes * P); i++) {
        int node1 = rand() % numNodes; // Select two random nodes to swap
        int node2 = rand() % numNodes;
        while (node1 == node2 || newSolution[node1] == newSolution[node2]) {
            node2 = rand() % numNodes;
        }
        if ((newSolution[node1] && matrix01[node1][1] < avg * 2.2) || (newSolution[node2] && matrix01[node2][1] < avg * 2.2)) {
            bool tmp = newSolution[node1];
            newSolution[node1] = newSolution[node2];
            newSolution[node2] = tmp;
            int newCost = calculateTotalCost(newSolution, matrix01, matrix02, P);
            if (newCost < oldCost) {
                oldCost = newCost;
                for (int i = 0; i < numNodes; i++) {
                    solution[i] = newSolution[i];
                }
            } else {
                // Undo the swap
                bool tmp = newSolution[node1];
                newSolution[node1] = newSolution[node2];
                newSolution[node2] = tmp;
            }
        }
    }
}

void simulated_annealing_algorithm(int avg, vector<bool>& solution, double T_max, double T_min, double alpha, int max_iterations, int P, vector<vector<int>>& matrix01, vector<vector<int>>& matrix02) {
    srand(time(NULL));
    int numNodes = solution.size();
    double current_cost = calculateTotalCost(solution, matrix01, matrix02, P);
    double best_cost = current_cost;
    vector<bool> best_solution;
    best_solution.resize(numNodes, false);
    for (int i = 0; i < numNodes; i++) {
        best_solution[i] = solution[i];
    }
    double T = T_max;
    int iterations = 0;
    // Main loop
    while (iterations < max_iterations) {
    	cout << "iterations  " <<" < --------------------------- "<< iterations <<" --------------------------- >"<< endl;
        perform_transition(solution, numNodes, avg, matrix01, matrix02, P);
        double new_cost = calculateTotalCost(solution, matrix01, matrix02, P);
        double delta_cost = new_cost - current_cost;
        if (delta_cost < 0) {
            current_cost = new_cost;
            cout<<"new_cost : "<<new_cost<<endl;
            if (new_cost < best_cost) {
                best_cost = new_cost;
                cout<<"best_cost : "<<best_cost<<endl;
                for (int j = 0; j < numNodes; j++) {
                    best_solution[j] = solution[j];
                }
            }
        } else {
            // Generate a random number between 0 and 1
            double r = rand() % 100;
            r = r / 100;
            if (r < exp(-delta_cost / T)) {
                current_cost = new_cost;
                cout << "current_cost : " << current_cost << endl;
            } else {
                for (int j = 0; j < numNodes; j++) {
                    solution[j] = best_solution[j];
                }
            }
        }
        T *= alpha;
        iterations++;
    }
    for (int j = 0; j < numNodes; j++) {
        solution[j] = best_solution[j];
    }
}

void Result(string filename, vector<bool>& solution, int& numNodes, int P, vector<vector<int>>& matrix01, vector<vector<int>>& matrix02){
    ofstream file(filename);
    if(file.good()){
        int numCenters = 0;
        file << "The Centers: " << endl;
        file << "[";
        for (int i = 1; i < numNodes ; i++) {
            if(solution[i]){
                file << i << ",";
                numCenters++;
            }
        }
        file << "]" << endl;
        file << "Total Cost: " << calculateTotalCost(solution, matrix01, matrix02, P) << endl;
    } else {
        cerr << "ERROR!";
        exit(1);
    }
    file.close();
}

int main (){
    int P, numNodes, avg = 0, k = 0;
    vector<vector<int>> matrix01;
    vector<vector<int>> matrix02;
    vector<bool> solution;
    readInstance("../Instance/PMCS-200.txt", P, numNodes, matrix01, matrix02);
    for (int i = 0; i < numNodes; i++) {
        avg = avg + matrix01[i][1];
    }
    avg = avg / numNodes;
    initialize_solution(numNodes, P, solution, avg, matrix01);
    cout << "Initial Cost: " << calculateTotalCost(solution, matrix01, matrix02, P) << endl;
    double T_max = 1000;
    double T_min = 1e-2;
    double alpha = 0.9;
    int max_iterations = 100 ; 
    simulated_annealing_algorithm(avg, solution, T_max, T_min, alpha, max_iterations, P, matrix01, matrix02);
    cout << "Final Cost: " << calculateTotalCost(solution, matrix01, matrix02, P) << endl;
    Result("../Result/Result-200.txt", solution, numNodes, P, matrix01, matrix02);
    return 0;
}

