#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <set>
using namespace std;

bool isValidUpdate(const vector<int>& update, const map<int, set<int>>& precedence) {
    for (size_t i = 0; i < update.size(); ++i) {
        for (size_t j = i + 1; j < update.size(); ++j) {
            int earlier = update[i];
            int later = update[j];
            if (precedence.count(later) && precedence.at(later).count(earlier)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ifstream fin("day5input.txt");
    if (!fin.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }

    map<int, set<int>> precedence;
    string line;

    while (getline(fin, line)) {
        if (line.empty()) break;
        int a, b;
        sscanf(line.c_str(), "%d|%d", &a, &b);
        precedence[a].insert(b);
    }

    int sumOfMiddles = 0;
    while (getline(fin, line)) {
        vector<int> update;
        stringstream ss(line);
        string token;

        while (getline(ss, token, ',')) {
            update.push_back(stoi(token));
        }

        if (isValidUpdate(update, precedence)) {
            sumOfMiddles += update[update.size() / 2];
        }
    }

    fin.close();

    cout << "ANSWER: " << sumOfMiddles << endl;
    return 0;
}
