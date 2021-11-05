/**
 * 模仿投篮，问抛物线轨迹是否入框
 * 两种方式入框，直接进或者打板
 * 当场不知道哪里有问题（极有可能是精度）
 * 下来改用整型，直接AC
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

typedef long long llt;

llt A, B, C;
llt X0, X1, Y0, Y1, Y2;

inline llt f(llt x){
    return (A * x + B) * x + C;
}

bool proc(){
    llt fx0 = f(X0);
    llt fx1 = f(X1);
    if(fx0 <= Y0) return false;

    /// 到此处说明(X0, Y0)在抛物线的下方
    if(fx1 < Y0) return true; // 说明(X1, Y0)在抛物线的上方
    if(fx1 == Y0) return false; // 说明刚好撞到(X1, Y0)
    if(fx1 > Y2) return false; // 说明撞不到篮板

    /// 检查对称位置即可知道反弹是否入框
    llt fx2 = f(X1 + X1 - X0);
    return fx2 < Y0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        A = getInt(); B = getInt(); C = getInt();
        X0 = getInt(); X1 = getInt();
        Y0 = getInt(); Y1 = getInt(); Y2 = getInt();
        puts(proc() ? "Yes" : "No");
	}
	return 0;
}
