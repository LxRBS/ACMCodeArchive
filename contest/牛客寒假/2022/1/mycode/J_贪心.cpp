/**
 * 给定两个数组，一组是闹的，一组是静的，从中一共选出N个围成一圈
 * 但是要求闹的不能相邻
 * 问能获得的满足条件的最大权和是多少。无法满足则输出-1
 * 令B是静的数量，显然要求B+B>=N
 * 然后贪心取数即可
 * 如果a小于等于b，直接取b即可
 * 如果a大于b，则取出a后，还需要根据已有的数量决定是否附带一个b
 * 最后如果没有取满，再在剩下的队列里取即可
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
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int A, B, N;
vi VA, VB;

int proc(){
	// if(A + B < N) return -1;
	if(B + B < N) return -1;

    priority_queue<int> qa, qb;
	for(int i : VA) qa.push(i);
	for(int i : VB) qb.push(i);
    
	int cnt = N;
	int ans = 0;
	int ca = 0, cb = 0;
	while(!qa.empty() && !qb.empty()){
        int a = qa.top();
		int b = qb.top();
        if(a > b){
			if(ca < cb){
				ans += a;
				++ca; 
				qa.pop();
				if(--cnt == 0) break;
			}else{
				ans += b;
				++cb;
				qb.pop();
				if(--cnt == 0) break;
			}
		}else{
			ans += b;
			++cb;
			qb.pop();
			if(--cnt == 0) break;
		}
	}
	if(qa.empty()){
		while(cnt--){
			ans += qb.top(); qb.pop();
		}
	}else if(qb.empty()){
		while(cnt--){
			ans += qa.top(); qa.pop();
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		VB.assign(B=getInt(), 0);
        VA.assign(A=getInt(), 0);		
		N = getInt();
		for(int & i : VB) i = getInt();
		for(int & i : VA) i = getInt();		
		printf("%d\n", proc()); 
	}

    return 0;
}