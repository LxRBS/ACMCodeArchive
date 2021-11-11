/**
 * 给定N个人，每个人都有一个权值，范围在[Li, Ri]之间。
 * 初始每个人的权值都取各自的最大，每个人的得分为N-Ki，其中Ki是其余权值中比wi大的数量
 * 现在要求调整每个人的权值，使得权值和最小，同时满足：
 * 每个人的得分不能少于原得分
 * 得分不能少，实际上就是说权值的大小顺序不能改变，因此新权值顺序等同于Ri的顺序
 * 按Ri进行排序，然后依次决定当前权值即可。
 * 注意得分不能少，但是可以多，例如
 * 4
 * 1 2
 * 2 2
 * 2 4
 * 2 4
 * 答案是8
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
int const SIZE = 22;
#else
int const SIZE = 120000;
#endif

typedef long long llt;

struct _t{
	int s, e;
	bool operator < (const _t&b)const{
		if(e != b.e) return e < b.e;
		return s < b.s;
	}
}A[SIZE];

int N, Level;

llt proc(){
    sort(A+1, A+N+1);
	llt ans = 0LL;
	int cur = 1, k = 0;
	while(1){
        k = 0;
		int level = 0;
		while(cur+k<=N&&A[cur].e==A[cur+k].e) level=max(level, A[cur+k].s), ++k;

        if(level > Level) Level = level;
		ans += k * (llt)Level;
		if((cur+=k) > N) break;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getInt();
	Level = 2000000000;
	for(int i=1;i<=N;++i){
        Level = min(Level, A[i].s = getInt());
		A[i].e = getInt();
	}
	cout<<proc()<<endl;
    return 0;
}

