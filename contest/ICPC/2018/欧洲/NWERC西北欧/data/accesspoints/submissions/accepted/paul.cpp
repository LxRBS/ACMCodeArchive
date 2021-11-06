#include <bits/stdc++.h>
using namespace std;

double min_cost(vector<int> x) {
	int n = x.size();
	vector<long long> sum(n+1);
	for (int i = 0; i < n; i++) sum[i+1] = sum[i]+x[i];
	
	auto avg = [&](int i, int j) { return double(sum[j]-sum[i])/(j-i); };

	stack<int> st;
	for (int i = 0; i < n; i++) {
		int j = i;
		while (!st.empty() && avg(st.top(),j) > avg(j,i+1)) j = st.top(), st.pop();
		st.push(j);
	}
	double res = 0;
	int i = n;
	while (!st.empty()) {
		int j = st.top();
		st.pop();
		for (int k = j; k < i; k++) res += pow(x[k]-avg(j,i),2);
		i = j;
	}
	return res;
}

int main() {
	int n; cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	cout << fixed << setprecision(10) << min_cost(x) + min_cost(y) << endl;
}
