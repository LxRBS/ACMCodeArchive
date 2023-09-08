#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using Real = long double;
using llt = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#ifndef ONLINE_JUDGE
int const SZ = 101;
#else
int const SZ = 110;
#endif

template<unsigned N = 1>
struct StrHash{

size_t operator () (const string & s){
	size_t ans = 0;
    for(char ch : s) ans = ans * seeds[0] + ch;
	return ans;
}

array<size_t, N> hash(const string & s){
	array<size_t, N> ans;
    fill(ans.begin(), ans.end(), 0);
	for(char ch : s){
		for(int i=0;i<N;++i){
            ans[i] = ans[i] * seeds[i] + ch;
		}
	}
	return ans;
}

public:
StrHash():seeds({13331}){}

private:
array<size_t, N> seeds;

};


int main(){
#ifndef ONLINE_JUDGE
    freopen("z.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	StrHash<> hash;
    int n; cin >> n;
	set<size_t> ss;
	for(int i=0;i<n;++i){
		string s; cin >> s;
		ss.insert(hash(s));
	}
	cout << ss.size() << endl;
    return 0;
}