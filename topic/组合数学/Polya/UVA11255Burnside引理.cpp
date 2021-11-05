#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
int const SIZE = 41;
llt C[SIZE][SIZE] = {1};
void initC(int n){
    for(int i=1;i<=n;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j){
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
}

bool isComp[SIZE] = {false};
int P[SIZE] = {0};
int PCnt = 0;
int Euler[SIZE] = {0,1};
void sieveEuler(){
    llt tmp;
	for(int i=2;i<SIZE;++i){
		if ( !isComp[i] ) P[PCnt++] = i, Euler[i] = i - 1;

		for(int j=0;j<PCnt&&(tmp=i*P[j])<SIZE;++j){
			isComp[tmp] = true;

			if ( 0 == i % P[j] ){
				Euler[tmp] = Euler[i] * P[j];
				break;
			}else{
				Euler[tmp] = Euler[i] * ( P[j] - 1 );
			}
		}
	}
}

llt f(int n, int L, int a, int b, int c){
    int k = n / L;
    if(a%k||b%k||c%k) return 0;
    a /= k, b /= k, c /= k;
    assert(L==a+b+c);
    return C[L][a] * C[L-a][b];
}

llt fji(int n, int a, int b, int c){
    int m = n >> 1;
    a = (a-1) >> 1; b >>= 1; c >>= 1;
    return C[m][a] * C[m-a][b] * n;
}

llt fou(int n, int a, int b, int c){
    n >>= 1, a >>= 1, b = (b-1)>>1, c = (c-1)>>1;
    return C[n-1][a] * C[n-a-1][b] * n << 1;
}
llt f(int n, int a, int b, int c){
    int na = a & 1;
    int nb = b & 1;
    int nc = c & 1;

    if(n&1){
        if(na+nb+nc>1) return 0;
        if(1==na) return fji(n, a, b, c);
        if(1==nb) return fji(n, b, a, c);
        return fji(n, c, a, b);
    }

    if(0==na+nb+nc){
        llt ans = 0;
        n >>= 1, a >>= 1, b >>= 1, c >>= 1;
        assert(n==a+b+c);
        ans += C[n][a] * C[n-a][b] * n;
        ans += C[n][b] * C[n-b][c] * n;
        ans += C[n][c] * C[n-c][a] * n;
        /// 过缝隙的
        ans += C[n][a] * C[n-a][b] * n;
        return ans >> 1;
    }

    if(2==na+nb+nc){
        if(0==na) return fou(n, a, b, c);
        if(0==nb) return fou(n, b, a, c);
        return fou(n, c, a, b);
    }

    return 0;
}

llt proc(int a, int b, int c){
    int i = 1,n = a + b + c;
    llt ans = 0;
    /// 计算旋转变换不变元的数量
    for(;i*i<n;++i){
        if(n%i) continue;
        ans += f(n, i, a, b, c) * Euler[n/i];
        ans += f(n, n/i, a, b, c) * Euler[i];
    }
    if(i*i==n) ans += f(n, i, a, b, c) * Euler[i];
    /// 计算翻转不变
    ans += f(n, a, b, c);
    return ans / (n+n);
}

int main(){
    //freopen("1.txt","r",stdin);
    /// 首先求组合数，再求欧拉函数
    initC(SIZE-1);
    sieveEuler();

    int nofkase, a, b, c;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d%d",&a,&b,&c);
        printf("%lld\n", proc(a, b, c));
    }
    return 0;
}
