/**
 * 给定N，求x和y，使得 x + y = N 且x和y的各位数字之和相差不超过1
 * 可以考虑暴力搜索，因为最多不超过九位数。
 * 这里使用构造，如果N是偶数，则直接对半分即可
 * 如果N是奇数，也直接对半分，只有一种情况不行，即 xx0, xx9 的情况
 * 此时不满足第二个条件。观察一下可知，如果改成 xx4, xx5 就能满足情况了
 * 还需要考虑末尾连续9的情况，即 x000 x999， 此时要改成 x545 和 x454
 * 因此只需要对末尾连续9进行处理即可。 
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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;

llt N;


void proc(){
    if(0 == N % 2){
        return (void)printf("%lld %lld\n", N/2, N/2);
    }
    auto x = N / 2 + 1;
    auto y = N / 2;
    if(y % 10 != 9) return (void)printf("%lld %lld\n", x, y);
    // assert(0 == x % 10);



    vll vy;
    while(y){
        vy.push_back(y % 10);
        y /= 10;
    }
    vi vx;
    while(x){
        vx.push_back(x % 10);
        x /= 10;
    }

    for(int i=0;i<vy.size();++i){
        if(vy[i] == 9){
            assert(vx[i] == 0);
            if(i & 1){
                vy[i] -= 5;
                vx[i] += 5;
            }else{
                vy[i] -= 4;
                vx[i] += 4;
            }
        }else{
            break;
        }
    }
    y = 0;
    for(int i=vy.size()-1;i>=0;--i) y = y * 10 + vy[i];
    x = 0;
    for(int i=vx.size()-1;i>=0;--i) x = x * 10 + vx[i];
    // assert(x + y == N);
    printf("%lld %lld\n", x, y);
} 

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        proc();
    }
    return 0;
}