/**
 * 类似于归并操作。假设有A和B两个非常长的数组，数组内容以段的形式给出。
 * 即(V, L)表示有L个V。每个数组均有若干个(Vi, Li)。
 * 问两个数组有多少个位置，其上的数是相等的。
 * 对每个数组维护当前段，交替推进判断即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}


#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}

using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;

llt L; 
int N1, N2;
vector<pair<int, llt>> A, B;

inline pair<llt, llt> get(pair<llt, llt> p, llt len){
    return {p.second + 1, p.second + len};
}

inline llt proc(pair<llt, llt> u, pair<llt, llt> v){
	llt s = max(u.first, v.first);
	llt e = min(u.second, v.second);
	if(s > e) return 0;
	return e - s + 1;
}

llt proc(){
    llt ans = 0;
    int a = 0, b = 0;
	pair<llt, llt> u{-1, 0}, v{-1, 0};
	int va = -1, vb = -1;
	while(1){
		if(u.second == v.second){
			auto pa = A[a++];
			auto pb = B[b++];
			if(pa.first == pb.first){
				ans += min(pa.second, pb.second);
			}
			u = get(u, pa.second);
			v = get(v, pb.second);
			va = pa.first;
			vb = pb.first;
		}

		while(a < N1 and u.second < v.second){
			auto p = A[a++];
			u = get(u, p.second);
            va = p.first;
			if(va == vb) ans += proc(u, v); 
		}

		while(b < N2 and v.second < u.second){
            auto p = B[b++];
			v = get(v, p.second);
			vb = p.first;
			if(va == vb) ans += proc(u, v);
		}

		if(a == N1 or b == N2) break;
	}
    
	if(a == N1){
		assert(u.second = L);
		while(b < N2){
            auto p = B[b++];
			v = get(v, p.second);
			vb = p.first;
			if(va == vb) ans += proc(u, v);			
		}
	}

	if(b == N2){
		assert(v.second == L);
		while(a < N1){
			auto p = A[a++];
			u = get(u, p.second);
            va = p.first;
			if(va == vb) ans += proc(u, v); 
		}		
	}

    assert(u.second == L and v.second == L);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    // L = getLL(); N1 = getInt(); N2 = getInt();
	cin >> L >> N1 >> N2;
    A.assign(N1, {});
	B.assign(N2, {});
	// for(auto & p : A) p.first = getInt(), p.second = getLL();
	// for(auto & p : B) p.first = getInt(), p.second = getLL();
	for(auto & p : A) cin >> p.first >> p.second;
	for(auto & p : B) cin >> p.first >> p.second;
	cout << proc() << endl;
    return 0; 
}


