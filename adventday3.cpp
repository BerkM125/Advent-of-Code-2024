#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#define ll long long

using namespace std;

int main (void) {
	ifstream fin("day3input.txt");
	bool enabled = true;
	int sum = 0;

	string match = "mul(";
	string dostr = "do()";
	string dontstr = "don't()";

	string str;
	stringstream buf;

	buf << fin.rdbuf();
	str = buf.str();
	
	for (int n = 0; n < str.length(); n++) {
		if (str[n] == 'd') {
			int x = n;
			for (x = n; x < n+dostr.length(); x++) {
				if (str[x] != dostr[x-n]) {
					break;
				}
			}
			if(x==n+dostr.length()) enabled = true;
			for (x = n; x < n+dontstr.length(); x++) {
				if (str[x] != dontstr[x-n]) {
					break;
				}
			}
			if(x==n+dontstr.length()) enabled = false;

		}
		else if (enabled && str[n] == 'm') {
			int first = 0;
			int second = 0;
			bool matching = true;
			for (int x = n; (x < n+match.length()) && (x<str.length()); x++) {
				if(str[x] != match[x-n]) {
					matching = false;
					break;
				}
			}
			if (!matching) continue; 

			int x = n+match.length();
			
			string fstr = "";
			string sstr = "";
			while(isdigit(str[x]) && x < str.length()) {
				fstr = fstr + str[x];
				x++;
			}
			if (str[x] != ',') continue;
	
			x++;
			while(isdigit(str[x]) && x < str.length()) {
				sstr = sstr + str[x];
				x++;
			}
			if (str[x] != ')') continue;
			sum += (stoi(fstr) * stoi(sstr));
		}
	}
	cout << "ANSWER: " << sum << endl;
	return 0;
}