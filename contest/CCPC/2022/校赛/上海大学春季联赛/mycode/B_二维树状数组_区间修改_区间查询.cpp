/**
 * 二维数组，元素值只有0和1，两种操作：区间取反，区间异或
 * 维护区间修改和区间查询操作，需要用到4个二维树状数组
 * 由于查询异或和，区间取反直接变成区间加1操作即可
 * 模板题
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 3;
#else
int const SIZE = 1E3+8;
#endif

/// 区间修改，区间查询
/// 需要维护4个二维树状数组
struct _t{

using value_t = long long int;
enum{SZ = SIZE};
value_t c[4][SZ][SZ];
int n, m; // 第一维和第二维

void init(int nn, int mm){this->n = nn, this->m = mm;}
static int lowbit(int x){return x & -x;}

void _modify(int x, int y, value_t d){
	for(int i=x;i<=this->n;i+=lowbit(i))for(int j=y;j<=this->m;j+=lowbit(j)){
        c[0][i][j] += d;
		c[1][i][j] += d * x;
		c[2][i][j] += d * y;
		c[3][i][j] += d * x * y;
	}
}

value_t _query(int x, int y){
	value_t ans = 0;
	for(int i=x;i;i-=lowbit(i))for(int j=y;j;j-=lowbit(j)){
		ans += (x+1) * (y+1) * c[0][i][j] - (y+1) * c[1][i][j] - (x+1) * c[2][i][j] + c[3][i][j];
	}
	return ans;
}

/// 区间修改
void modify(int x1, int y1, int x2, int y2, value_t d){
    this->_modify(x1, y1, d);
	this->_modify(x1, y2+1, -d);
    this->_modify(x2+1, y1, -d);
	this->_modify(x2+1, y2+1, d);
}

/// 区间查询
value_t query(int x1, int y1, int x2, int y2){
    value_t ans = 0;
	ans += this->_query(x2, y2);
	ans -= this->_query(x2, y1 - 1);
	ans -= this->_query(x1 - 1, y2);
	ans += this->_query(x1 - 1, y1 - 1);
	return ans;
}

};

int N, M, Q;
_t Bit;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    Q = getInt();
	Bit.init(N, M);
	for(int op,x1,y1,x2,y2,q=1;q<=Q;++q){
        op = getInt();
		x1 = getInt(); y1 = getInt();
		x2 = getInt(); y2 = getInt();
		if(1 == op){
			Bit.modify(x1, y1, x2, y2, 1);
		}else{
			long long ans = Bit.query(x1, y1, x2, y2);
			if(ans < 0) ans = -ans;
            printf("%lld\n", 1LL & ans);
		}
	}
    return 0;
}