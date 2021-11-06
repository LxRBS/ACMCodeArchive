#include <bits/stdc++.h>

#define FORD(i,a,b) for(short i=(b-1); i>=(a); i--)

using namespace std;

int main(){
	short n, m;
	string key, cypher;
	cin >> n >> m >> key >> cypher;
	string decrypt = string(m-n, '0') + key;

	FORD(i, n, m){
		FORD(k, 0, 26){
			if(((decrypt[i]-'a') + k) % 26 == cypher[i] - 'a'){
				decrypt[i-n] = char(k+'a');
			}
		}
	}

	cout << decrypt << endl;
	return 0;
}
