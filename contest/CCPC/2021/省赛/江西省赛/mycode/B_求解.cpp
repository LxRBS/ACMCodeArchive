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

typedef long long llt;
typedef pair<int, int> pii;
#define fi first
#define se second

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else 
int const SIZE = 200010;
#endif

llt X, Y;
vector<int> Ans;

void proc(){
    Ans.clear();
    while(1){
        int t = X / Y;
        X = X % Y;
        Ans.push_back(t);
        if(!X) break;
        swap(X, Y);
    }    
    printf("%d", Ans.size()-1);
    for(auto i: Ans){
        printf(" %d", i);
    }
    puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        X = getInt();
        Y = getInt();
        proc();
    }
    return 0;
}