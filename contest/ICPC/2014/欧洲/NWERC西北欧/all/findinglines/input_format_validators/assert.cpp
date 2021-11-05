#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)


void isInteger(string in){
	assert(in.size() > 0);
	if(in[0] == '-')in = in.substr(1);
	assert(in.size() <= 10);
	assert(in.size() > 0);
	FOR(i,0,(int)in.size()){
		assert(in[i] >= '0');
		assert(in[i] <= '9');
	}
}

vector<ll> getNums(){
	string in;
	assert(getline(cin,in));
	vector<string> pnums;
	int last = 0;
	FOR(i,0,(int) in.size()){
		if(in[i] == ' '){
			assert(i > 0);
			assert(i < in.size() - 1);
			assert(in[i-1] != ' ');
			assert(in[i+1] != ' ');
			pnums.push_back(in.substr(last, i - last));
			last = i + 1;
		}
	}
	pnums.push_back(in.substr(last));
	vector<ll> nums;
	FOR(i,0,(int)pnums.size()){
		isInteger(pnums[i]);
		istringstream is(pnums[i].c_str());
		ll tmp;
		is >> tmp;
		nums.push_back(tmp);
	}
	return nums;
}

int main() {
	vector<ll> tmp = getNums();
	assert(tmp.size() == 1);
	ll N = tmp[0];
	tmp = getNums();
	assert(tmp.size() == 1);
	ll p = tmp[0];
	assert(1 <= N && N <= 100000);
	assert(20 <= p && p <= 100);
	FOR(i,0,N){
		tmp = getNums();
		assert(tmp.size() == 2);
		FOR(j,0,2){
			assert(0 <= tmp[j] && tmp[j] <= 1000000000);
		}
	}
	return 42;
}
