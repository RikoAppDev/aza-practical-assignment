#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a job
struct Job {
    int id;
    int deadline;
    float profit;
};

// Comparison function for sorting jobs by profit in descending order
bool compareJobs(const Job &a, const Job &b) {
    return a.profit > b.profit;
}

// Function to schedule jobs to maximize total profit within their deadlines
void scheduleJobs(int n, vector<Job> &jobs) {
    // Sort jobs in descending order of profit
    sort(jobs.begin(), jobs.end(), compareJobs);

    vector<int> result(n, -1);         // To store the optimal sequence of jobs
    vector<bool> scheduleJob(n, false); // To track if a job is scheduled or not

    // Loop through each job
    for (int i = 0; i < n; i++) {
        // Loop through possible time slots in reverse order
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!scheduleJob[j]) {
                scheduleJob[j] = true;
                result[j] = i; // Schedule the job and update the result
                break;
            }
        }
    }

    // Display results
    cout << "Optimal sequence of jobs with maximum profit is: ";
    float totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (scheduleJob[i]) {
            totalProfit += jobs[result[i]].profit;
            cout << jobs[result[i]].id << " ";
        }
    }
    cout << "\nTotal profit from jobs is: " << totalProfit << "$" << endl;
}

int main() {
    // Initialisation of a vector of jobs
    vector<Job> jobs = {
            {1, 2, 40},
            {2, 4, 15},
            {3, 3, 60},
            {4, 2, 20},
            {5, 3, 10},
            {6, 1, 45},
            {7, 1, 55}
    };

    int n = (int) jobs.size();
    scheduleJobs(n, jobs);

    return 0;
}