/**
 * 线段树基础，单点修改，查询区间极大值
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

void getString(char *p){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();

	*p++ = ch;
	while(isalpha(ch = __hv007())) *p++ = ch;
	*p++ = '\0';
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 200110;
#endif

int N;
int MOD;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[SIZE<<2];    // 最大值

inline void _pushUp(int t){
    St[t] = max(St[lson(t)], St[rson(t)]);
}

void modify(int t, int s, int e, int pos, int newValue){
    if(s == e){
		St[t] = newValue;
		return;
	}

	int mid = (s + e) >> 1;
	if(pos<=mid) modify(lson(t), s, mid, pos, newValue);
	if(mid<pos) modify(rson(t), mid+1, e, pos, newValue);
	_pushUp(t);	
}

int query(int t, int s, int e, int a, int b){
	if(a<=s && e<=b){
		return St[t];
	}

    int mid = (s + e) >> 1;
    int ans = 0;
	if(a<=mid) ans = max(query(lson(t), s, mid, a, b), ans);
	if(mid<b) ans = max(query(rson(t), mid+1, e, a, b), ans);
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); MOD = getInt();
	int ans = 0;
	char cmd[12];
	int k = 1;
	for(int q=1;q<=N;++q){
        getString(cmd);
		if('A' == *cmd){
            llt n = getInt();
			(n += ans) %= MOD;
			modify(1, 1, N, k++, n);
		}else if('Q' == *cmd){  
            int x = getInt();
			ans = query(1, 1, N, k-x, k-1);
			printf("%d\n", ans);  
		}else{
			throw runtime_error("XX");
		}
	}
	return 0;
}
