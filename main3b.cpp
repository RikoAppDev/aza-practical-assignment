#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Assignment {
    int person;
    int job;
    int cost;
};

// Helper functions for sort algorithm
bool compareJobs(const Assignment &a, const Assignment &b) {
    return a.cost < b.cost;
}

bool compareAssignmentsCost(const vector<Assignment> &a, const vector<Assignment> &b) {
    return a[0].cost < b[0].cost;
}

bool comparePersons(const Assignment &a, const Assignment &b) {
    return a.person < b.person;
}

// Check if job wal already assigned
bool alreadyAssigned(vector<Assignment> &assignments, Assignment a) {
    for (auto &i: assignments) {
        if (i.job == a.job)
            return true;
    }
    return false;
}

// Assign persons and jobs correspondingly using
vector<Assignment> minAssignmentCost(const vector<vector<int>> &costMatrix) {
    int n = (int) (costMatrix.size());

    // Create a matrix with all assignment representations
    vector<vector<Assignment>> dp(n);

    for (int i = 0; i < costMatrix.size(); i++) {
        for (int j = 0; j < costMatrix[i].size(); j++) {
            Assignment job = *new Assignment;
            job.job = j;
            job.person = i;
            job.cost = costMatrix[i][j];
            dp[i].push_back(job);
        }
    }

    // Sort jobs for each person
    for (auto &i: dp) {
        sort(i.begin(), i.end(), compareJobs);
    }

    // Sort persons using their most efficient job cost
    sort(dp.begin(), dp.end(), compareAssignmentsCost);

    // Find correct assignments
    vector<Assignment> assignments;
    int jobId = 0;
    for (int i = 0; i < dp.size(); i++) {
        Assignment a = dp[i][jobId];
        if (!alreadyAssigned(assignments, a)) {
            Assignment newAssignment = dp[i][jobId];
            assignments.push_back(newAssignment);
            jobId = 0;
        } else {
            jobId++;
            i--;
        }
    }

    sort(assignments.begin(), assignments.end(), comparePersons);
    return assignments;
}

int main() {
    // Example input
    vector<vector<int>> costMatrix = {
            {10, 5, 5},
            {2,  4, 10},
            {5,  1, 7}
    };

    // Find the optimal assignments
    vector<Assignment> assignments = minAssignmentCost(costMatrix);
    int minimalCost = 0;

    // Print assignments
    cout << "Job assignment:" << endl;
    for (auto &assignment: assignments) {
        cout << "Person P" << assignment.person + 1 << " -> Job J" << assignment.job + 1
             << " with cost " << assignment.cost << " time units" << endl;
        minimalCost += assignment.cost;
    }

    cout << "\nMinimal assignment job cost: " << minimalCost << " time units" << endl;

    return 0;
}
