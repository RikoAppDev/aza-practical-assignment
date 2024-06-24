#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Assignment representation
struct Assignment {
    int person;
    int job;
    int cost;
};

// Check if job was already assigned
bool wasJobAssigned(int job, const vector<Assignment> &assignments) {
    return any_of(assignments.begin(), assignments.end(), [job](const Assignment &a) { return a.job == job; });
}

// Loops through persons and jobs and assign them correspondingly with greedy approach
vector<Assignment> greedyAssignment(const vector<vector<int>> &costMatrix) {
    vector<Assignment> assignments;

    int n = (int) costMatrix.size();

    for (int person = 0; person < n; person++) {
        int minCost = INT_MAX;
        int minJob = -1;

        for (int job = 0; job < n; job++) {
            if (!wasJobAssigned(job, assignments)) {
                if (costMatrix[person][job] < minCost) {
                    minCost = costMatrix[person][job];
                    minJob = job;
                }
            }
        }

        assignments.push_back({person, minJob, minCost});
    }

    return assignments;
}

int main() {
    // Example cost matrix P x J
    vector<vector<int>> costMatrix = {
            {10, 5, 5},
            {2,  4, 10},
            {5,  1, 7}
    };

    // Find the greedy assignment
    vector<Assignment> assignments = greedyAssignment(costMatrix);
    int minimalCost = 0;

    // Display the results
    cout << "Job assignment:" << endl;
    for (auto &assignment: assignments) {
        cout << "Person P" << assignment.person + 1 << " -> Job J" << assignment.job + 1 << " with cost "
             << assignment.cost << " time units" << endl;
        minimalCost += assignment.cost;
    }
    cout << "\nMinimal assignment job cost: " << minimalCost << " time units" << endl;
}