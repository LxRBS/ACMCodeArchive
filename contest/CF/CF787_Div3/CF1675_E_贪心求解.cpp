/**
 * 给一个字符串，每次操作，可以选择一个字母x，将该字符串中所有为x的字母均变成x-1
 * 最多执行K次操作，问能够得到的字典序最小的字符串是多少
 * 首先注意到操作的特性，假设有字符串bc，K为2，
 * 则可以先将c变为b，再把b变为a，这样整个字符串都变为了a，是最小
 * 但如果是bdc，K为2，则ada并非最小，acc才是最小
 * 所以首先应该找到这样一个位置，其字母到a的操作次数小于等于K，且最靠右，且之前没有比它更大的字母，记作pos
 * 要么所有字符串都变为a，要么所有小于等于该字母的位置都变为a，此时假设还剩L次操作
 * 剩下的L次操作确定不足以让剩下的任何字母变为a，因此把pos+1位置的字母减L即可，
 * 当然剩下其他小于等于A[pos+1]的字母都能变为A[pos+1]-L
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
int const SIZE = 2e5+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;

int N, K;
char A[SIZE];

char * proc(){
	vi vec;
	vec.push_back(A[0]);
	for(int i=1;i<N;++i){
		if(vec.back() < A[i]) vec.push_back(A[i]);
	}

	vi cnt(vec.size());
	int tmp = -1;
	for(int i=0,n=vec.size();i<n;++i){
		cnt[i] = vec[i] - 'a';
		if(cnt[i] > K){
            tmp = i;
			break;
		}
	}
	if(-1 == tmp){
		fill(A, A+N, 'a');
		return A;
	}

    int mmm = -1;
    int used = 0;
	if(tmp) used += vec[tmp-1] - 'a', mmm = vec[tmp-1];
	K -= used;
	char ch = vec[tmp] - K;

	for(int i=0;i<N;++i){		
		if(A[i] <= mmm) A[i] = 'a';
		else if(A[i] <= vec[tmp] && A[i] >= ch) A[i] = ch;
	}
	return A;
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%d%s", &N, &K, A);
		puts(proc());
    }
    return 0;
}