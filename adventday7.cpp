#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <cstring>
#define ll long long
using namespace std;

bool helper(vector<ll> nums, ll step, ll curr) {
	if(step >= nums.size()) return false;
	
	ll p = curr * nums[step];
	ll s = curr + nums[step];
	ll c = stoll(to_string(curr) + to_string(nums[step]));
	
	if(p == nums[0] || s == nums[0] || c == nums[0]) {
		return true;
	}
	
	return helper(nums, step+1, p) || helper(nums, step+1, s) || helper(nums, step+1, c);
}

int main(void) {
	ifstream fin("day7input.txt");
	string line;
	ll ans = 0;
	
	while(getline(fin, line)) {
		ll n;
		vector<ll> inp;
		replace(line.begin(), line.end(), ':', ' ');
		istringstream ss(line);
		
		while(ss >> n) {
			inp.push_back(n);
		}
		
		if(helper(inp, 2, inp[1])) {
			ans += inp[0];
		}
	}
	cout << "ANSWER: " << ans << endl;
	return 0;
}