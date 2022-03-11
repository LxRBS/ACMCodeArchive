/**
 * 给定一个数组A，初始Ai==i，从1到N做N次操作，每次操作如下：
 * 对当前区间[1, cur]内的元素做循环右移操作，移动距离任意
 * 给定N次操作以后的数组A，求方案，如无输出-1
 * 反过来考虑，拿到最后的数组A以后，看N在哪里，
 * 最后一次操作必然是将N从N位置移动到现有位置，
 * 所以只需做一个逆操作就能得到N-1次操作的数组
 * 如此继续，就能得到最初的数组。
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
int const SIZE = 15;
#else
int const SIZE = 2E3+5;
#endif

int N, A[SIZE];
vector<int> Ans;

bool proc(int idx){
    int pos = 0;
    while(pos<idx && A[pos]!=idx) ++pos;
    if(pos == idx) return false;
    int k = (pos + 1) % idx;
    Ans.push_back(k);
    if(0==k) return true;
    rotate(A, A+pos+1, A+idx);
    return true;
}

void proc(){
    Ans.clear();
    for(int k=N;k>=1;--k){
        if(!proc(k)){
            return (void)puts("-1");
        }
    }
    for(auto it=Ans.rbegin();it!=Ans.rend();++it) printf("%d ", *it);puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); 
        for(int i=0;i<N;++i) A[i] = getInt();
        proc();
    }
    return 0;
}
