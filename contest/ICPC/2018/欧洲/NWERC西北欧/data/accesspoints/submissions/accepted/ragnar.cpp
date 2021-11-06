#include <bits/stdc++.h>
using namespace std;

double solve(vector<int>& v){
	vector<pair<int, double>> avg = {{0,-1}};
	avg.reserve(v.size());
	for(auto x : v){
		avg.push_back({1,x});
		while(avg.back().second < avg[avg.size()-2].second){
			auto& a = avg.back();
			auto& b = avg[avg.size()-2];
			b.second = (a.first * a.second + b.first * b.second) / (a.first + b.first);
			b.first += a.first;
			avg.pop_back();
		}
	}
	int i = 0;
	double ans = 0;
	for(auto &p : avg)
		for(int j = 0; j < p.first; ++j, ++i)
			ans += (v[i] - p.second)*(v[i] - p.second);
	return ans;
}
int main(){
	int n; cin >> n;
	vector<int> x(n), y(n);
	for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
	cout << setprecision(7) << solve(x) + solve(y) << endl;
	return 0;
}
