/**
 * 给定n/a/b，构造一个长度为n的字符串，满足：
 * 每个长度为a的子串恰好有b个不同的字母
 * 就用b作为循环节即可
*/
#include <bits/stdc++.h>
using namespace std;
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char A[2100];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        int n = getInt();
        int a = getInt();
        int b = getInt();
        for(int i=0;i<n;i+=b){
            for(int j=0;j<b;++j){
                A[i+j] = 'a' + j;
            }
        }
        A[n] = '\0';
        puts(A);
    }
    return 0;
}

