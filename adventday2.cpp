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
#define SHOULD_DECREASE 1
#define SHOULD_INCREASE 0
#define UNDET INT_MAX

using namespace std;

int main (void) {
	int ans = 0;
	string line;
	ifstream fin("day2input.txt");

	while (getline(fin, line)) {
		int num = UNDET;
		int trend = UNDET;
		istringstream stream(line);
		vector<int> list; 
		
		while (stream >> num) {
			list.push_back(num);
		}

		bool strike = false;
		size_t n = 1;
		vector<int> copy(list);

		for (size_t o = 0; o < copy.size(); o++) {

			if(strike) list.erase(list.begin() + o);

			for (n = 1; n < list.size(); n++) {

				if (trend == UNDET) {
					if (list[n] > list[n-1]) trend = SHOULD_INCREASE;
					else if (list[n] < list[n-1]) trend = SHOULD_DECREASE;
				}

				else {
					if ( (list[n] > list[n-1] && trend == SHOULD_DECREASE) ||
						(list[n] < list[n-1] && trend == SHOULD_INCREASE) ||
						(list[n] == list[n-1] && trend != UNDET))
							break;
				}
				
				int gap = abs(list[n] - list[n-1]);

				if (!(gap >= 1 && gap <= 3)) break;
			}

			if (n == list.size()) {
				ans++;
				break;
			}

			strike = true;
			list = copy;
		}
	}

	cout << "ANSWER: " << ans << endl;
	return 0;
}