/**
 * 模拟球在矩形框内来回碰撞。首先要处理球在四壁或者角上的变向情况，直接写成嵌套if。
 * 其次要判断球无法到达终点的情况，如果某个位置及方向重复出现，还没有路过过终点，则说明永远无法到达指定终点。
 * 同时还需判断是否能够路过终点的情况，使用了叉积和点积作为判断。
 * 另外初始情况的特判要注意。
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
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

int N, M;
pii S, T;
string D;
set<pair<pii, string>> Flag;

bool f(const pii & pos){
	if(pos.first == 1 and pos.second == 1) return true;
	if(pos.first == 1 and pos.second == M) return true;
	if(pos.first == N and pos.second == 1) return true;
	if(pos.first == N and pos.second == M) return true;
	return false;
}

pii move(pii pos, string & d){
    if("DR" == d){
        // int t = min(N - pos.first, M - pos.second);
		int tx = N - pos.first;
		int ty = M - pos.second;
		if(tx < ty){
            pos.first += tx, pos.second += tx;
			d = "UR";
		}else if(ty < tx){
			pos.first += ty, pos.second += ty;
			d = "DL";
		}else{
			pos.first += ty, pos.second += ty;
			d = "UL";
		}
	}else if("DL" == d){
        // int t = min(N - pos.first, pos.second - 1);
		int tx = N - pos.first;
		int ty = pos.second - 1;
		if(tx < ty){
            pos.first += tx, pos.second -= tx;
			d = "UL";
		}else if(ty < tx){
			pos.first += ty, pos.second -= ty;
			d = "DR";
		}else{
			pos.first += ty, pos.second -= ty;
			d = "UR";
		}
	}else if("UR" == d){
        // int t = min(pos.first - 1, M - pos.second);
		int tx = pos.first - 1;
		int ty = M - pos.second;
		if(tx < ty){
            pos.first -= tx, pos.second += tx;
			d = "DR";
		}else if(ty < tx){
			pos.first -= ty, pos.second += ty;
			d = "UL";
		}else{
			pos.first -= ty, pos.second += ty;
			d = "DL";
		}
	}else if("UL" == d){
        // int t = min(pos.first - 1, pos.second - 1);
		int tx = pos.first - 1;
        int ty = pos.second - 1;
		if(tx < ty){
            pos.first -= tx, pos.second -= tx;
			d = "DL";
		}else if(ty < tx){
			pos.first -= ty, pos.second -= ty;
			d = "UR";
		}else{
			pos.first -= ty, pos.second -= ty;
			d = "DR";
		}
	}else{
		throw runtime_error("XX");
	}
	return pos;
}

bool isOK(pii a, pii b, pii c){
    // if(a == b or b == c) return true;
	llt xob = b.first - a.first;
	llt yob = b.second - a.second;
	llt xoc = c.first - a.first;
	llt yoc = c.second - a.second;
	return 0 == xob * yoc - yob * xoc and xob * xoc + yob * yoc > 0;
}

int proc(){
	if(S == T) return 0;

    Flag.clear();
	pii cur = S;
	string d = D;
	Flag.insert({cur, d});
	int ans = 0;
	while(1){
        auto pos = move(cur, d);
		if(isOK(cur, T, pos)) break;
		ans += 1;
		cur = pos;
		
		auto it = Flag.find({cur, d});
		if(it != Flag.end()) return -1;
		Flag.insert(it, {cur, d});
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
	int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> M >> S.first >> S.second >> T.first >> T.second >> D;
		printf("%d\n", proc()); 
	}
    return 0; 
}


