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

using namespace std;

int main (void) {
	ifstream fin("day1input.txt");
	
	vector<int> right;
	vector<int> left;
	map<int, int> freq;
	
	int r, l;
	ll sum = 0;
	string t_str;

	while (true) {
		fin >> l;
		fin >> r;

		if(r == -1) break;
		right.push_back(r);
		left.push_back(l);	

		freq[r] += 1;
	}
	
	for (int l : left) {
		sum += ( (ll)l * (ll)freq[l] );
	}

	cout << "ANSWER: " << sum << endl;
	return 0;
}