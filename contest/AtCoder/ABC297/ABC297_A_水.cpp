#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

using vi = vector<int>;

int N, D;
vi A;

int proc(){
	for(int i=1;i<N;++i){
		if(A[i] - A[i - 1] <= D) return A[i];
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> D;
	A.assign(N, 0);
	for(auto & i : A) cin >> i;
	cout << proc() << endl;
    return 0; 
}


