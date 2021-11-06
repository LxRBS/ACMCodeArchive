#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,c,b; cin >> n >> c >> b;
	vector<bool> ans(n, true);
	while(b--){
		int x; cin >> x;
		--x;
		ans[x] = false;
	}

	ans[0] = c&1;
	c -= c&1;
	for(int i = 1; i < n; ++i){
		if(ans[i] == true && c > 0) ans[i] = !ans[i-1];
		else ans[i] = false;
		if(ans[i] != ans[i-1]) --c;
	}
	for(auto b : ans) cout << b;
	cout << endl;
}
