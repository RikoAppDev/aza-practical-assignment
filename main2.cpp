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

// Disjoint Set Data Structure functions
int findSet(int i, vector<int> &parent) {
    // Find the representative of the set to which i belongs
    if (i != parent[i]) {
        parent[i] = findSet(parent[i], parent);
    }
    return parent[i];
}

void unionSets(int i, int j, vector<int> &parent, vector<int> &depth, vector<int> &smallest) {
    // Union by rank with path compression
    int rooti = findSet(i, parent);
    int rootj = findSet(j, parent);

    if (depth[rooti] > depth[rootj]) {
        parent[rootj] = rooti;
        smallest[rooti] = min(smallest[rooti], smallest[rootj]);
    } else {
        parent[rooti] = rootj;
        smallest[rootj] = min(smallest[rooti], smallest[rootj]);

        if (depth[rooti] == depth[rootj]) {
            depth[rootj]++;
        }
    }
}

void scheduleJobs(int n, vector<Job> &jobs) {
    // Sort jobs in descending order of profit
    sort(jobs.begin(), jobs.end(), compareJobs);

    // Find the maximum deadline among all jobs
    int d = 0;
    for (int i = 0; i < n; i++) {
        d = max(d, jobs[i].deadline);
    }

    // Initialize data structures for disjoint set operations
    vector<int> result(d + 1, -1);
    vector<int> parent(d + 1);
    vector<int> depth(d + 1, 0);
    vector<int> smallest(d + 1);

    for (int i = 0; i <= d; i++) {
        parent[i] = i;
        smallest[i] = i;
    }

    // Iterate through jobs and schedule them
    for (int i = 0; i < n; i++) {
        int j = min(d, jobs[i].deadline);

        // Find the latest available time slot for the job
        while (j > 0 && smallest[findSet(j, parent)] == 0) {
            j--;
        }

        // Schedule the job and update data structures
        if (smallest[findSet(j, parent)] != 0) {
            result[j] = i;
            unionSets(j, j - 1, parent, depth, smallest);
        }
    }

    // Display results
    cout << "Optimal sequence of jobs with maximum profit is: ";
    float totalProfit = 0;
    for (int i = 1; i <= d; i++) {
        if (result[i] != -1) {
            totalProfit += jobs[result[i]].profit;
            cout << jobs[result[i]].id << " ";
        }
    }
    cout << "\nTotal profit from jobs is: " << totalProfit << "$" << endl;
}

int main() {
    // Initialize jobs
    vector<Job> jobs;
    jobs.push_back((Job) {1, 2, 40});
    jobs.push_back((Job) {2, 4, 15});
    jobs.push_back((Job) {3, 3, 60});
    jobs.push_back((Job) {4, 2, 20});
    jobs.push_back((Job) {5, 3, 10});
    jobs.push_back((Job) {6, 1, 45});
    jobs.push_back((Job) {7, 1, 55});

    int n = (int) jobs.size();
    scheduleJobs(n, jobs);

    return 0;
}
