#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int charDistance(char a, char b) {
    return ((a - b + 12) % 26) - 12;
}

int totalDistance(const string& firstName, const string& lastName) {
    int distance = 0;
    for (size_t i = 0; i < firstName.length(); ++i) {
        distance += charDistance(firstName[i], lastName[i]);
    }
    return distance;
}

string findCelebrity(const vector<string>& firstNames, const vector<string>& lastNames) {
    int n = firstNames.size();
    vector<int> knows(n, 0); // Keeps track of how many people each person knows

    // Calculate who knows whom
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && totalDistance(firstNames[i], lastNames[j]) > 0) {
                knows[i]++;
            }
        }
    }

    // Check for celebrity (knows nobody)
    int celebrityCount = 0;
    string celebrityName;
    for (int i = 0; i < n; ++i) {
        if (knows[i] == 0) { // A potential celebrity
            bool everyoneKnows = true;
            for (int j = 0; j < n; ++j) {
                if (i != j && totalDistance(firstNames[j], lastNames[i]) <= 0) {
                    everyoneKnows = false;
                    break;
                }
            }
            if (everyoneKnows) {
                celebrityCount++;
                celebrityName = firstNames[i] + " " + lastNames[i];
            }
        }
    }

    // Determine the result based on the number of celebrities found
    if (celebrityCount == 0) {
        return "No";
    }
    else if (celebrityCount == 1) {
        return celebrityName;
    }
    else {
        return "I should learn some logic";
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<string> firstNames(n), lastNames(n);
        for (int i = 0; i < n; ++i) {
            cin >> firstNames[i] >> lastNames[i];
        }
        cout << findCelebrity(firstNames, lastNames) << endl;
    }
    return 0;
}
