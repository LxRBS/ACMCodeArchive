/**
    给定数A和B，定义加法为：从低位到高位相加，每一位相加的结果依次写下来，得到和。
    例如：19+16 = 215 66+99 = 1515
    现在给定A与和，求B， 不存在的话输出-1
    写成了深搜递归的形式，但其实每一位是没有选择的。循环即可搞定。
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 22;
#endif

char A[SIZE], S[SIZE];
char B[SIZE];

int NA, NS;
int NB;

bool dfs(int da, int ds){
    if(-1 == da){
		if(-1 == ds) return true;

		while(ds!=-1) B[NB++] = S[ds--];
		return true;
	}

    if(da > ds) return false;

	int cha = S[ds] - A[da];
	if(cha >= 0){
        B[NB++] = cha + '0';
		bool t = dfs(da-1, ds-1);
		if(t) return true;
		--NB;
	}else{
		if(0==ds||'1'!=S[ds-1]) return false;
		cha += 10;
		B[NB++] = cha + '0';
		bool t = dfs(da-1, ds-2);
		if(t) return true;
		--NB;
	}
    return false;
}

char* proc(){
	NA = strlen(A);
	NS = strlen(S);
	NB = 0;
    bool t = dfs(NA-1, NS-1);
	if(t){
		B[NB] = '\0';
		reverse(B, B+NB);
		int k = 0;
		while(B[k]=='0') ++k;
		return B+k;
	}else{
		B[0] = '-';
		B[1] = '1';
		B[2] = '\0';
		return B;
	}
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s%s", A, S);
		printf("%s\n", proc());
	}
    return 0;
}
