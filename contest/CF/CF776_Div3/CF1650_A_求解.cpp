/**
 * 给定字符串S，长度为奇数，每次删去任意相邻的两个字母，问最后是否能够得到字母C
 * 观察以后发现不能单独留下奇数位置的字母(0-index)
 * 因此只需判断02468...位置上是否存在字母C即可
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
int const SIZE = 2E5+5;
#endif

string S;
char T;
bool proc(){
    int n = S.length();
    for(int i=0;i<n;i+=2){
        // if(i == 1 || i == n-2) continue;
        if(S[i]==T) return true;
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; cin>>nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        cin>>S>>T;
        cout<<(proc()?"YES":"NO")<<endl;
    }
    return 0;
}
