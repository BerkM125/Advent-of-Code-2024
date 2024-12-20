#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#define ll long long
#define UNDET INT_MAX
using namespace std;
const string code = "XMAS";

void scan(vector<vector<char>>& arr, int x, int y, int n, int prev, int *hits) {
	if(n == 4) {
		*hits += 1;
		return;
	}
	if(x > arr[0].size()-1 || x < 0 || y > arr.size()-1 || y < 0) return;

	if(arr[y][x] == code[n]) {
		if (prev == UNDET || prev == 1)
			scan(arr, x+1, y, n+1, ( (prev == UNDET) ? 1 : prev ), hits);
		if (prev == UNDET || prev == 2)
			scan(arr, x-1, y, n+1, ( (prev == UNDET) ? 2 : prev ), hits);
		if (prev == UNDET || prev == 3)
			scan(arr, x, y+1, n+1, ( (prev == UNDET) ? 3 : prev ), hits);
		if (prev == UNDET || prev == 4)
			scan(arr, x, y-1, n+1, ( (prev == UNDET) ? 4 : prev ), hits);
		if (prev == UNDET || prev == 5)
			scan(arr, x+1, y+1, n+1, ( (prev == UNDET) ? 5 : prev ), hits);
		if (prev == UNDET || prev == 6)
			scan(arr, x+1, y-1, n+1, ( (prev == UNDET) ? 6 : prev ), hits);
		if (prev == UNDET || prev == 7)
			scan(arr, x-1, y+1, n+1, ( (prev == UNDET) ? 7 : prev ), hits);
		if (prev == UNDET || prev == 8)
			scan(arr, x-1, y-1, n+1, ( (prev == UNDET) ? 8 : prev ), hits);
	}
	else {
		return;
	}
}

bool assertmas (vector<vector<char>>& arr, int x, int y) {
	if(x-1 > arr[0].size()-1 || x-1 < 0 || y-1 > arr.size()-1 || y-1 < 0) return false;
	if(x+1 > arr[0].size()-1 || x+1 < 0 || y+1 > arr.size()-1 || y+1 < 0) return false;

	if ( !(
		(arr[y-1][x-1] == 'M' && arr[y+1][x+1] == 'S') ||
		(arr[y-1][x-1] == 'S' && arr[y+1][x+1] == 'M')) )
		return false;
	if ( !(
		(arr[y-1][x+1] == 'M' && arr[y+1][x-1] == 'S') ||
		(arr[y-1][x+1] == 'S' && arr[y+1][x-1] == 'M')) )	
		return false;
	
	return true;
}

int main (void) {
	int total = 0;
	ifstream fin("day4input.txt");
	vector<vector<char>> fileData;
	string line;

	while (getline(fin, line)) {
		fileData.push_back(vector<char>(line.begin(), line.end()));
	}

	fin.close();
	
	for (int y = 0; y < fileData.size(); y++) {
		for (int x = 0; x < fileData[y].size(); x++) {
			if (fileData[y][x] == 'A') {
				if(assertmas(fileData, x, y)) {
					total += 1;
				}
			}
		}
	}
	cout << "ANSWER: " << total << endl;
	return 0;
}