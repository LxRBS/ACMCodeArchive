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
	assert(tmp.size() == 3);
	ll N = tmp[0];
	ll P = tmp[1]; // == MOD
	ll R = tmp[2]; // == RELOAD
	assert(1 <= N && N <= 2000);
	assert(1 <= P && P <= 10000000);
	assert(1 <= R && R <= 10000000);
	tmp = getNums();
	assert(tmp.size() == N);
	FOR(i,0,N){
		assert(0 <= tmp[i] && tmp[i] < P);
	}
	return 42;
}
