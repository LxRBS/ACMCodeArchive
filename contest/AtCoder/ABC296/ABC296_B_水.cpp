#include <bits/stdc++.h>
using namespace std;

vector<string> Vec;

string proc(){
	for(int k=1,i=7;i>=0;--i,++k){
        const auto & s = Vec[i];
		for(int j=0,c='a';j<8;++j,++c){
			if(s[j] == '*'){
				return string(1, c) + string(1, char(k + '0'));
			}
		}
	}
	assert(0);
	return "";
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Vec.assign(8, string());
	for(auto & s : Vec) cin >> s;
	cout << proc() << endl;
    return 0; 
}
