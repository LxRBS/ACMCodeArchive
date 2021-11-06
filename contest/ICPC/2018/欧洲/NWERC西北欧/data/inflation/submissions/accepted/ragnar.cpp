#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(auto &x : v) cin >> x;
	sort(v.begin(), v.end());
	double d = 1;
	for(int i = 1; i <= n; ++i){
		if(v[i-1] > i){
			cout << "impossible\n";
			return 0;
		}
		d = min(d, v[i-1]/double(i));
	}
	cout << setprecision(7) << d << endl;
	return 0;
}
