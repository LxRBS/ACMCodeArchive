/**
 * 给定1个整点线段AB，问是否存在第3个整点使得三个点成等腰直角三角形且以线段为斜边
 * 首先将A变为原点，B变为P
 * 再将P旋转45度，得到Q，再将OQ缩短为原来的1/sqrt(2)，则Q点就是直角点
 * 考虑到旋转公式，再考虑到等比例收缩
 * | cos -sin | | 1/sqrt(2) 0 |
 * | sin cos  | | 0 1/sqrt(2) |
 * 最后的变换矩阵为
 * | 1/2 -1/2 |
 * | 1/2 1/2  |
 * 所以只要P点的x、y坐标奇偶性相同即可。
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
using pll = pair<llt, llt>;
using pr = pair<Real, Real>;

const Real PI = acos((Real)-1.0);
const Real SQRT22 = sqrt((Real)2) * (Real)0.5;

pll A, B;
pll C, D;

void proc(){
    pll p = {B.first - A.first, B.second - A.second};
	if((p.first & 1) == (p.second & 1)){
        C = {(p.first - p.second) / 2, (p.first + p.second) / 2};
		C.first += A.first;
		C.second += A.second;
		return (void)(cout<<C.first<<" "<<C.second<<endl);
	}
	return (void)(cout<<"No Answer!"<<endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
	while(cin >> A.first >> A.second >> B.first >> B.second){
		proc();
	}
    return 0;
}