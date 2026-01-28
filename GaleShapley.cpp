#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void galeShapleyStdin() {
    int n;
    if (!(cin >> n))
        return;

    vector<vector<int>> hospitalPrefs(n + 1, vector<int>(n + 1));
    vector<vector<int>> studentRanks(n + 1, vector<int>(n + 1));

    // hospital prefs
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> hospitalPrefs[i][j];
        }
    }

    // student prefs
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int h_id;
            cin >> h_id;
            studentRanks[i][h_id] = j;
        }
    }

    vector<int> sMatch(n + 1, 0);
    vector<int> hMatch(n + 1, 0);
    vector<int> nextChoice(n + 1, 1);

    queue<int> freeHospitals;
    for (int i = 1; i <= n; ++i)
        freeHospitals.push(i);

    while (!freeHospitals.empty()) {
        int h = freeHospitals.front();
        freeHospitals.pop();

        int s = hospitalPrefs[h][nextChoice[h]];
        nextChoice[h]++;

        if (sMatch[s] == 0) {
            sMatch[s] = h;
            hMatch[h] = s;
        } else {
            int currentH = sMatch[s];
            // trade up
            if (studentRanks[s][h] < studentRanks[s][currentH]) {
                sMatch[s] = h;
                hMatch[h] = s;
                hMatch[currentH] = 0;
                freeHospitals.push(currentH);
            } else {
                freeHospitals.push(h);
            }
        }
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        cout << i << " " << hMatch[i] << endl;
    }
}

// runs G-S on the lists of input given, and returns a vector of pairs
// (literally, the (Hospital, Student) pairs that G-S outputs)
vector<pair<int, int>> galeShapleyVector(int n, const vector<vector<int>> &hospitalPrefs,
                                         const vector<vector<int>> &studentRanks) {
    vector<int> sMatch(n + 1, 0);
    vector<int> hMatch(n + 1, 0);
    vector<int> nextChoice(n + 1, 1);

    queue<int> freeHospitals;
    for (int i = 1; i <= n; ++i)
        freeHospitals.push(i);

    while (!freeHospitals.empty()) {
        int h = freeHospitals.front();
        freeHospitals.pop();

        int s = hospitalPrefs[h][nextChoice[h]];
        nextChoice[h]++;

        if (sMatch[s] == 0) {
            sMatch[s] = h;
            hMatch[h] = s;
        } else {
            int currentH = sMatch[s];
            // trade up
            if (studentRanks[s][h] < studentRanks[s][currentH]) {
                sMatch[s] = h;
                hMatch[h] = s;
                hMatch[currentH] = 0;
                freeHospitals.push(currentH);
            } else {
                freeHospitals.push(h);
            }
        }
    }

    vector<pair<int, int>> pairings(n + 1);

    cout << "Matchings:\n";

    for (int i = 1; i <= n; ++i) {
        cout << i << " " << hMatch[i] << "\n";
    }

    return pairings;
}

// generate input for G-S, namely a list of hospital/student preferences
pair<vector<vector<int>>, vector<vector<int>>> generateInput(int n) {
    // store the numbers 1-n (inclusive) in a vector, so for n=3 it'll store {1, 2, 3}, n=5 it'll store {1, 2, 3, 4, 5}.
    // since every preference list, for both hospitals and students, is just /some/ permutation of this list, we just
    // keep shuffling this list and saying the result of that shuffle is the preference list for the
    // hospital/student in question. that's also why the loop below runs 2n times, rather than n.
    vector<int> all_nums(n);
    for (int i = 0; i < n; i++) {
        all_nums[i] = i + 1;
    }

    // randomization boilerplate
    random_device rd;
    mt19937 g(rd());

    cout << "Hospital Rankings:\n";
    vector<vector<int>> hospitalRankings(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        shuffle(all_nums.begin(), all_nums.end(), g);

        for (int j = 1; j <= n; j++) {
            hospitalRankings[i][j] = all_nums[j - 1];
        }

        cout << "H" << i << " | ";
        for (auto num : all_nums) {
            cout << num << " ";
        }
        cout << "\n";
    }

    cout << "Student Rankings:\n";
    vector<vector<int>> studentRankings(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        shuffle(all_nums.begin(), all_nums.end(), g);

        // may note: this is basically storing the student rankings as a way of looking
        // up which hospital has a higher preference.
        // so for example, studentRankings[2][3] = 1 means:
        // "student 2 has ranked hospital 3 as their #1 choice"
        // NOT that their third-favorite is hospital 1. very important distinction!!
        for (int j = 1; j <= n; j++) {
            // studentRankings[i][j] = all_nums[j - 1];
            studentRankings[i][all_nums[j - 1]] = j;
        }

        cout << "S" << i << " | ";
        for (auto num : all_nums) {
            cout << num << " ";
        }
        cout << "\n";
    }

    return {hospitalRankings, studentRankings};
}

int main(int argc, char *argv[]) {

    if (argc == 2) {
        // if passed a number (well, hopefully a number, we don't check), generate data with that many
        // hospitals/students, and run G-S on it
        int n = stoi(argv[1]);

        vector<vector<int>> hospitalPrefs, studentRanks;
        tie(hospitalPrefs, studentRanks) = generateInput(n);
        vector<pair<int, int>> pairings = galeShapleyVector(n, hospitalPrefs, studentRanks);

    } else {
        galeShapleyStdin();
    }

    return 0;
}
