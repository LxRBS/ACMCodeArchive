/**
 * 给定参数，计算
 * X = X + A[p]
 * p = (Kp + B) % N
 * 计算 1E12 次。很显然p一定会有周期，计算出周期即可，最多计算2N次。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
int const SIZE = 133;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

llt N;
llt P, K, B, T;
vector<llt> A;

int proc0(){
    if(0 == T) return cout << 0 << endl, 0;
    llt x = 0;
    for(int i=0;i<T;++i){
        x += A[P];
        P = (K * P + B) % N;        
    }
    cout << x << endl;
    return 0;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> P >> K >> B >> T;
    A.assign(N, 0);
    for(int i=0;i<N;++i) cin >> A[i]; 

    if(1 == N) return cout << A[0] * T << endl, 0;
    if(T <= 2000000) return proc0();

    map<llt, int> pos;
    vector<llt> vec;

    pos[P] = vec.size();
    vec.push_back(P);

    int start = -1;
    while(1){
        auto nt = (vec.back() * K + B) % N;
        auto it = pos.find(nt);
        if(it != pos.end()){
            start = it->second;
            break;
        }
        it = pos.insert(it, {nt, vec.size()});
        vec.emplace_back(nt);
    }

    llt pre = start;
    llt zhouqi = vec.size() - start;
    llt huihe = (T - start) / zhouqi;
    llt suf = (T - start) % zhouqi;
    
    assert(pre + huihe * zhouqi + suf == T);

    llt pre_ans = 0;
    for(int i=0;i<start;++i){
        pre_ans += A[P];
        P = (K * P + B) % N;
    }

    llt zhouqi_ans = 0;
    for(int i=start;i<vec.size();++i){
        zhouqi_ans += A[P];
        P = (K * P + B) % N;
    }
    assert(P == vec[start]);

    auto ans = pre_ans + zhouqi_ans * huihe;
    for(int i=0;i<suf;++i){
        ans += A[P];
        P = (K * P + B) % N;
    }

    cout << ans << endl;
    return 0;
}