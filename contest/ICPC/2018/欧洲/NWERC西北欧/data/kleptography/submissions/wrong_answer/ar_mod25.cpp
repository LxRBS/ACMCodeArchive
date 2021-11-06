// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,M;
    string last_part, plain, encrypted;
    cin >> N >> M >> last_part >> encrypted;
    plain = encrypted;
    for(int i = 0; i < N; i++)
        plain[M-N+i] = last_part[i];
    for(int i = M-N-1; i >= 0; i--)plain[i] = (((encrypted[i+N] - 'a') - (plain[i+N] - 'a') + 25) % 25) + 'a';
    cout << plain << endl;
	return 0;
}
