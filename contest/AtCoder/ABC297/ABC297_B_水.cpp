#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

using vi = vector<int>;

string S;

bool proc(){
	vi b;
	for(int i=0;i<8;++i){
        if(S[i] == 'B') b.push_back(i + 1);
	}
	int b0 = b[0] & 1, b1 = b[1] & 1;
	if(b0 == b1) return false;

	b.clear();
	for(auto ch : S){
		if('K' == ch){
			if(0 == b.size()) return false;
			return true;
		}else if('R' == ch){
			b.push_back(0);
			if(2 == b.size()) return false;
		}
	} 
	assert(0);
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> S;
	cout << (proc() ? "Yes" : "No") << endl;
    return 0; 
}
