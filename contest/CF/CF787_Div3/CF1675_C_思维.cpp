/**
 * 房间里有一幅画，每个人单独进去再出来，其中有一个人是贼，进去以后就会把画拿走。
 * 每个人出来以后会给出'01?'三者之一，
 * 其中0表示画已经消失了，1表示画还在，?表示不记得了
 * 除了贼之外，其他人都会说实话，贼可能说谎也可能说实话
 * 根据给定的数据，判断一共有多少个人有嫌疑
 * 因为最多只有一个人说谎，考虑1，前面的1不可能说谎，只有最后一个1有可能说谎
 * 同理，考虑0，后面的不可能说谎，只有第一个0可能说谎
 * 因为给定的数据肯定符合条件，所以最后一个1必然在第一个0之前，而且这之间的其他人肯定都是问号，且都有嫌疑
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

int N;
string S;

int proc(){
    N = S.length();
    int leftmost0 = N - 1;
    int rightmost1 = 0;
    for(int i=0;i<N;++i){
        if(S[i] == '0'){
			leftmost0 = i; break;
		}
	}    
	for(int i=N-1;i>=0;--i){
		if(S[i] == '1'){
			rightmost1 = i; break;
		}
	}
	return leftmost0 - rightmost1 + 1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
	while(nofkase--){
        cin >> S;
		cout << proc() << endl;
	}
    return 0;
}