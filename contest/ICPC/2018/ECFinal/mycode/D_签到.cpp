/**
    Ç©µ½
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

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        int n = getInt();
        int m = getInt();
        printf(n<=m?"Yes\n":"No\n");
        while(n--)getInt();
        while(m--)getInt();
    }
    return 0;
}
