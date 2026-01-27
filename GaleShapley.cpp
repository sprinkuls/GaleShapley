#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void galeShapley() {
    int n;
    if (!(cin >> n)) return;
 
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
    for (int i = 1; i <= n; ++i) freeHospitals.push(i);

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
            if (sRanks[s][h] < sRanks[s][currentH]) {
                sMatch[s] = h;
                hMatch[h] = s;
                hMatch[currentH] = 0;
                freeHospitals.push(currentH);
            } else {
                freeHospitals.push(h);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << i << " " << hMatch[i] << endl;
    }
}

int main() {
    galeShapley();
    return 0;
}