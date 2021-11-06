#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

const int MAXN = 1.1e6;
ll v[MAXN];

int main(){
    int N;
    cin >> N;
    FOR(i,0,N)cin >> v[i];
    sort(v, v + N);
    reverse(v, v + N);
    ll dif = v[0] - v[1] + 1;
    ll active = 1;
    ll slowadd = v[1] - v[2];
    ll res = v[1] - v[2];
    while(true){
        while(active+1 < N && v[active + 1] + slowadd >= v[1])++active;
        ll S = 0;
        while((1ll<<(S+1)) <= active)++S;
        ll T = (dif - 1) / S;
        if(active+1 < N)T = min(T, v[1] - (v[active + 1] + slowadd));
        if(T == 0){
            cout << (res + dif - 1) << endl;
            return 0;
        }
        res += (S + 1) * T;
        slowadd += T;
        dif -= S * T;
    }
	return 0;
}
