#include <bits/stdc++.h>
using namespace std;

int N;
string S;

bool proc(){
	for(int i=1;i<N;++i){
		if(S[i] == S[i - 1]) return false;
	}
	return true;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> S;
	puts(proc()?"Yes":"No");
    return 0; 
}
