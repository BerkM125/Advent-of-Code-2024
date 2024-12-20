#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <utility>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

map<char, vector<pair<int, int>>> antennas;
unordered_set<pair<int, int>, pair_hash> locationset;

int mainDay1() {
    ifstream fin("day8input.txt");
    string line;
    vector<vector<char>> grid;
    
    while(getline(fin, line)) {
        vector<char> buf;
        for (char c : line) buf.push_back(c);
        grid.push_back(buf);
    }
    
    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[y].size(); x++) {
            char target = grid[y][x];
            if(target == '.' || target == '\n' || target == ' ') continue;
            antennas[target].push_back(make_pair(x, y));
        }   
    }
    
    for(auto k : antennas) {
        for (auto loc : k.second) {
            for (int n = 0; n < k.second.size(); n++) {
                pair<int, int> coord = k.second[n];
                if(coord.first == loc.first && coord.second == loc.second) continue;
                
                int xDist = loc.first - coord.first;
                int yDist = loc.second - coord.second;
                int x = loc.first;
                int y = loc.second;

				if(!(y+yDist < 0 || y+yDist >= grid.size() || x+xDist < 0 || x+xDist >= grid[0].size())) {
					locationset.insert(make_pair(x+xDist, y+yDist));
				}
            }
        }
    }
	cout << "ANSWER: " << locationset.size() << endl;
    return 0;
}

int main(void) {
    ifstream fin("day8input.txt");
    string line;
    vector<vector<char>> grid;
    
    while(getline(fin, line)) {
        vector<char> buf;
        for (char c : line) buf.push_back(c);
        
        grid.push_back(buf);
    }
    
    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[y].size(); x++) {
            char target = grid[y][x];
            if(target == '.' || target == '\n' || target == ' ') continue;
            antennas[target].push_back(make_pair(x, y));
        }   
    }
    
    for(auto k : antennas) {
        for (auto loc : k.second) {
            for (int n = 0; n < k.second.size(); n++) {
                pair<int, int> coord = k.second[n];
                if(coord.first == loc.first && coord.second == loc.second) continue;
                
                int xDist = loc.first - coord.first;
                int yDist = loc.second - coord.second;
                int x = loc.first;
                int y = loc.second;
				
				while(!(y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size())) {
					if((y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size())) {
						break;
					}
					locationset.insert(make_pair(x, y));
					x+=xDist;
					y+=yDist;
				}
            }
        }
    }
	cout << "ANSWER: " << locationset.size() << endl;
    return 0;
}

