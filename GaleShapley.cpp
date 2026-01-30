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
                                         const vector<vector<int>> &studentRanks, bool outputText) {
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

    if (outputText) {
        cout << "Matchings:\n";
        for (int i = 1; i <= n; ++i) {
            cout << i << " " << hMatch[i] << "\n";
            pairings[i] = {i, hMatch[i]};
        }
    }

    return pairings;
}

// generate input for G-S, namely a list of hospital/student preferences
pair<vector<vector<int>>, vector<vector<int>>> generateInput(int n, bool outputText) {
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

    if (outputText) {
        cout << "Hospital Rankings:\n";
    }
    vector<vector<int>> hospitalRankings(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        shuffle(all_nums.begin(), all_nums.end(), g);

        for (int j = 1; j <= n; j++) {
            hospitalRankings[i][j] = all_nums[j - 1];
        }
        if (outputText) {
            cout << "H" << i << " | ";
            for (auto num : all_nums) {
                cout << num << " ";
            }
            cout << "\n";
        }
    }

    if (outputText) {
        cout << "Student Rankings:\n";
    }
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

        if (outputText) {
            cout << "S" << i << " | ";
            for (auto num : all_nums) {
                cout << num << " ";
            }
            cout << "\n";
        }
    }

    return {hospitalRankings, studentRankings};
}

// generate random matchings for n students and hospitals; useful for testing the verifier as the
// random matchings will likely contain an unstable pair.
vector<pair<int, int>> generateMatchings(int n) {
    vector<int> all_nums(n);
    for (int i = 0; i < n; i++) {
        all_nums[i] = i + 1;
    }

    // randomization boilerplate; shuffle all nums
    random_device rd;
    mt19937 g(rd());
    shuffle(all_nums.begin(), all_nums.end(), g);

    cout << "Randomly generated matchings:\n";
    vector<pair<int, int>> matchings(n + 1);
    for (int i = 1; i <= n; i++) {
        cout << i << " " << all_nums[i - 1] << "\n";
        matchings[i] = {i, all_nums[i - 1]};
    }
    return matchings;
}

// given preference lists and a matching of hospitals to students, check whether the matching is stable
void verifyMatching(int n, const vector<vector<int>> &hospitalPrefs, const vector<vector<int>> &studentRanks,
                    vector<pair<int, int>> matchings) {
    // sets of which hospitals/students a student/hospital preferred over the one they got matched with.
    // these are stored so we can look for a pair where, say, a student in a certain hospital's hospitalBetter /also/
    // has that hospital in their studentBetter. that is to say, we store these values so we can look for a pair where
    // some hospital Y prefers student X over their match, and that same student X prefers a hospital Y over their
    // match.
    vector<set<int>> hospitalBetter(n + 1);
    vector<set<int>> studentBetter(n + 1);

    // "for each hospital"
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // we only want to add students we prefer to the current match, so once we reach the current match, we can
            // stop for this hospital

            if (hospitalPrefs[i][j] == matchings[i].second) {
                break;
            }
            hospitalBetter[i].insert(hospitalPrefs[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        int studentNr = matchings[i].second;
        int bestMatch = studentRanks[studentNr][i];

        for (int j = 1; j <= n; j++) {
            if (studentRanks[studentNr][j] < bestMatch) {
                studentBetter[studentNr].insert(j);
            }
        }
    }

    // test printing
    // cout << "Better than what I got:\n";
    // for (int i = 1; i <= n; i++) {
    //     cout << "H" << i << ": ";
    //     for (int student : hospitalBetter[i]) {
    //         cout << student << ", ";
    //     }
    //     cout << "\n";
    // }
    // cout << "Better than what I got:\n";
    // for (int i = 1; i <= n; i++) {
    //     cout << "S" << i << ": ";
    //     for (int hospital : studentBetter[i]) {
    //         cout << hospital << ", ";
    //     }
    //     cout << "\n";
    // }

    // loop through each hospital, and see which candidates they preferred to
    // the one they got. then, check to see if any of those candidates prefer this
    // hospital to the one they got. if they both prefer each other, that's an
    // unstable matching!
    for (int i = 1; i <= n; i++) {
        for (int student : hospitalBetter[i]) {
            if (studentBetter[student].find(i) != studentBetter[student].end()) {
                cout << "UNSTABLE: Hospital " << i << " and student " << student
                     << " prefer each other over their current matches!\n";
                return;
            }
        }
    }
    cout << "VALID STABLE\n";
}

void runScalabilityTests() {
    vector<int> sizes = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    // this runs each size 10 times to average the results
    const int trials = 10;

    cout << "-------------------------------------------------" << endl;
    cout << "n" << "\t" << "Average Time in microseconds (10 trials)" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int n : sizes) {
        long long totalDuration = 0;

        for (int t = 0; t < trials; t++) {
            auto data = generateInput(n, false);
            auto start = chrono::high_resolution_clock::now();

            // galeShapleyVector has couts disabled so that printing time doesn't affect timing results
            galeShapleyVector(n, data.first, data.second, false);

            auto stop = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            totalDuration += duration.count();
        }

        cout << n << "\t" << (totalDuration / trials) << endl;
    }
}

int main(int argc, char *argv[]) {

    if (argc == 2) {

        string arg = argv[1];
        if (arg == "--test") {
            // run timed tests for scalability, outputting average time taken for various input sizes
            runScalabilityTests();
        } else if (arg == "--verify") {
            // just fix n at 4 for now
            int n = 4;
            vector<vector<int>> hospitalPrefs, studentRanks;
            tie(hospitalPrefs, studentRanks) = generateInput(n, true);
            vector<pair<int, int>> matchings = generateMatchings(n);
            verifyMatching(n, hospitalPrefs, studentRanks, matchings);

        } else {
            // if passed a number (well, hopefully a number, we don't check), generate data with that many
            // hospitals/students, and run G-S on it
            int n = stoi(arg);
            vector<vector<int>> hospitalPrefs, studentRanks;
            tie(hospitalPrefs, studentRanks) = generateInput(n, true);
            vector<pair<int, int>> pairings = galeShapleyVector(n, hospitalPrefs, studentRanks, true);
            // verifyMatching(n, hospitalPrefs, studentRanks, pairings);
        }
    } else {
        galeShapleyStdin();
    }

    return 0;
}
