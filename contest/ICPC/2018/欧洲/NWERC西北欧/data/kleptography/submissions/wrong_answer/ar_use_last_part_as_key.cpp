// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,M;
    string key, encrypted;
    cin >> N >> M >> key>> encrypted;
    for(int i = 0; i < M ; i++){
        char next_l = (char) (((encrypted[i] - 'a') - (key[i] - 'a') + 26) % 26) + 'a';
        key += string(1,next_l);
        cout << next_l;
    }
    cout << endl;
	return 0;
}
