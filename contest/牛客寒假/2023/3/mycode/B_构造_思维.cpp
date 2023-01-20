/**
 * 给定N，要求只能用1×W的矩形条，其中 1 <= W <= ceil(N/2.0)， 注意矩形条的W可以不同
 * 只能用N个矩形条，问能够拼出来的最大正方形的边长。
 * 一开始想打表找一个简单的公式，wa了几次。
 * 最后给出了构造方法，才确定。
 * 假设N是偶数，最大能用的条是1×N/2。假设正方形的边长是K，
 * 则先使用K个最大条，得到K*N/2，然后再用(K-N/2)个最大条竖着放，然后还有一个小方块，显然也需要K-N/2个条
 * 所以一共用了 K + 2 * (K-N/2)，需要小于等于N
 * 如果是奇数，则最大条为1×(N+1)/2，推导与刚才类似。
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
int const SIZE = 130;
#else
int const SIZE = 1e7+5;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 

llt N;
vi A;

llt proc(){
	if(1 == N) return 1;
	if(2 == N) return -1;
	if(3 == N || 4 == N) return 2;
	if(N & 1) return (N + N + 1) / 3;
	return (N + N) / 3;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
	while(nofkase--){
		cin >> N;
		cout << proc() << endl;
	}
    return 0;
}