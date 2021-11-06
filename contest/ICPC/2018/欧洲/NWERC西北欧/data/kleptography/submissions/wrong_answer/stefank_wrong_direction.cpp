#include <bits/stdc++.h>

#define FOR(i,a,b) for(short i=(a); i < (b); i++)

using namespace std;

int main(){
	short n, m;
	string key, cypher;
	cin >> n >> m >> key >> cypher;
	string decrypt = string(m-n, '0') + key;

	FOR(i, n, m){
		FOR(k, 0, 26){
			if(((decrypt[i]-'a') + k) % 26 == cypher[i] - 'a'){
				decrypt[i-n] = char(k+'a');
			}
		}
	}

	cout << decrypt << endl;
	return 0;
}
