#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include <utility>
#include <string>
#include <cstring>

#define ll long long
#define UNDET INT_MAX
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
using namespace std;

struct VectorRecord {
    size_t x, y;
	int direction;
    bool operator==(const VectorRecord& other) const {
        return x == other.x && y == other.y && direction == other.direction;
    }
};

struct HashFunction {
    size_t operator()(const VectorRecord& vr) const {
        const size_t prime1 = 73856093;
        const size_t prime2 = 19349663;
        const size_t prime3 = 83492791;
        return (vr.x * prime1) ^ (vr.y * prime2) ^ (static_cast<size_t>(vr.direction) * prime3);
    }
};
unordered_set<VectorRecord, HashFunction> visitedVectors;

vector<vector<char>> grid;
vector<pair<size_t, size_t>> visited;
size_t originalX;
size_t originalY;
bool loopDetected = false;

int rotate(int dir) {
	int newDir = dir;
	switch(dir) {
		case UP:
			newDir = RIGHT;
			break;
		case DOWN:
			newDir = LEFT;
			break;
		case LEFT:
			newDir = UP;
			break;
		case RIGHT:
			newDir = DOWN;
			break;
	}
	return newDir;
}

bool obstacleAhead(size_t x, size_t y, int direction) {
	switch(direction) {
		case UP:
			if(x < 0 || x >= grid[0].size() || y-1 < 0 || y-1 >= grid.size()){
				return false;
			}			
			return (grid[y-1][x] == '#');
		case DOWN:
			if(x < 0 || x >= grid[0].size() || y+1 < 0 || y+1 >= grid.size()){
				return false;
			}
			return (grid[y+1][x] == '#');
		case LEFT:
			if(x-1 < 0 || x-1 >= grid[0].size() || y < 0 || y >= grid.size()){
				return false;
			}
			return (grid[y][x-1] == '#');
		case RIGHT:
			if(x+1 < 0 || x+1 >= grid[0].size() || y < 0 || y >= grid.size()){
				return false;
			}
			return (grid[y][x+1] == '#');
	}
	return false;
}

void helper(size_t x, size_t y, int direction) {
	if(x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()){
		return;
	}
	
	grid[y][x] = 'X';
	
	if (obstacleAhead(x, y, direction)) {
		direction = rotate(direction);
	}
	
	switch(direction) {
		case UP:
			helper(x, y-1, direction);
			break;
		case DOWN:
			helper(x, y+1, direction);
			break;
		case LEFT:
			helper(x-1, y, direction);
			break;
		case RIGHT:
			helper(x+1, y, direction);
			break;
	}
}

void helper2(size_t x, size_t y, int direction) {
	if(x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()) return;
	
	if (visitedVectors.find({x, y, direction}) != visitedVectors.end()) {
		loopDetected = true;
		return;
	}
	
	visitedVectors.insert({x, y, direction});
	
	while (obstacleAhead(x, y, direction)) {
		direction = rotate(direction);
	}
	
	switch(direction) {
		case UP:
			helper2(x, y-1, direction);
			break;
		case DOWN:
			helper2(x, y+1, direction);
			break;
		case LEFT:
			helper2(x-1, y, direction);
			break;
		case RIGHT:
			helper2(x+1, y, direction);
			break;
	}
}

int main (void) {
	ifstream fin("day6input.txt");
	string line;
	
	while(getline(fin, line)) {
		vector<char> row;
		for (char c : line) row.push_back(c);
		grid.push_back(row);
	}
	
	for(size_t y = 0; y < grid.size(); y++) {
		size_t x;
		for(x = 0; x < grid.size(); x++) {
			if(grid[y][x] == '^') {
				helper(x, y, UP);
				originalX = x;
				originalY = y;
				break;
			}
		}
		if(x != grid.size()) break;
	}
	
	int ans = 0;
	for(size_t y = 0; y < grid.size(); y++) {
		for(size_t x = 0; x < grid.size(); x++) {
			if (grid[y][x] == 'X' && !(x == originalX && y == originalY)) {
				ans++;
				visited.push_back(make_pair(x, y));
			}
		}
	}
	cout << "DAY 1: " << ans+1 << endl;
	ans = 0;
	
	for (auto loc : visited) {
		size_t y = loc.second;
		size_t x = loc.first;
		
		grid[y][x] = '#';
		
		helper2(originalX, originalY, UP);
		if(loopDetected) ans++;
		loopDetected = false;
		visitedVectors.clear();
		grid[y][x] = '.';
	}

	cout << "DAY 2: " << ans << endl;
	return 0;
}