/**
 * 给定N、M、X和Y，求N场比赛至少M分且进X球丢Y球的不同方案总数。
 * NMXY均不大，可以支持O(N^4)。
 * 初步很容易想到令Dijxy为i轮比赛j分进x丢y的方案总数，很容易确定转移方程。
 * 但是暴力方法至少需要O(N^5)，超时。
 * 标程用了前缀和优化，最终使得复杂度达到O(N^4)
 * 这里用推公式。考虑恰好N场比赛胜A平B负C进X丢Y的方案总数。
 * 首先拿出A个进球和C个丢球，这是固定的。然后k从[0, min(X-A,Y-C)]取值。
 * 对每一个k，将k个进球和k个丢球分配到N场比赛中，作为垫底。这个分配是完备的。
 * 然后再将X-A-k个进球分配到A个胜场中，将Y-C-k个丢球分配到C个负场中，这个分配是满足恰好满足约束的，且完备的。
 * 最后只需要从N场确定A、B即可。因此对一个固定的ABC需要O(X)的循环
 * 然后再遍历A、B即可。O(N^3)。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;

llt const MOD = 998244353LL;

llt powerMod(llt a, llt n){
    llt ret = 1LL;
    a %= MOD;

    while(n){
        if(n & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        n >>= 1;
    }
    return ret;
}

inline llt inv(llt a){return powerMod(a, MOD-2LL);}

struct mint{

llt value;
mint(llt c=0):value((c%MOD+MOD)%MOD){}

const mint operator + (const mint & r) const {return mint(value + r.value);}
const mint operator - (const mint & r) const {return mint(value - r.value);}
const mint operator * (const mint & r) const {return mint(value * r.value);}
const mint operator / (const mint & r) const {return *this * mint(inv(r.value));}

mint & operator += (const mint & r){
    (value += r.value) %= MOD;
    return *this;
}

mint & operator *= (const mint & r){
    (value *= r.value) %= MOD;
    return *this;
}

};

int N, M, X, Y;

vvll A; // Aij表示平i场进j球的方案数
v3ll B; // Bijk 表示胜i场进j球丢k球的情况

void procA(){
    A.assign(N+1, vll(min(X, Y)+1, 0LL));
    A[0][0] = 1;
    for(int i=1;i<=N;++i){
        const auto & pre = A[i - 1];
        auto & d = A[i];
        for(int j=0,n=d.size();j<n;++j){
            auto & dj = d[j];
            dj = 0;
            for(int k=0;k<=j;++k){
                (dj += pre[j - k]) %= MOD;
            }
        }
    }

    printf("A\n");
    for(int i=1;i<=N;++i){
        printf("%d轮:\n", i);
        for(int j=0;j<A[i].size();++j){
            printf("(%d球, %lld)", j, A[i][j]);
        }
        printf("\n");
    }
}

void procB(){
    B.assign(N+1, vvll(X+1, vll(Y+1, 0LL)));
    for(int j=1;j<=X;++j)for(int k=0;k<min(Y+1, j);++k)B[1][j][k] = 1;

    for(int i=1;i<N;++i){ // 胜i场
        const auto & cur = B[i];
        auto & nxt = B[i+1];
        for(int j=i;j<=X;++j){ // 胜i场至少要进i球
            for(int k=0;k<=min(Y, j-i);++k){ // 净胜球至少是i, 所以丢球数<=j-i
                const auto tmp = cur[j][k];
                assert(tmp > 0);

                /// 考虑tmp对下一轮的贡献
                for(int u=1;u<=X-j;++u){
                    for(int v=0;v<min(Y-k+1, u);++v){
                        nxt[j+u][v+k] += tmp;
                    }
                }
            }
        }
    }

    printf("B\n");
    for(int i=1;i<=N;++i){
        printf("%d轮\n", i);
        for(int j=i;j<=X;++j){                        
            for(int k=0;k<min(Y+1, j);++k){                
                printf("(进%d, 丢%d, %lld)", j, k, B[i][j][k]);
            }
        }
        printf("\n");
    }
}

vector<vector<llt>> C;
//初始化从1到n的组合数，包括n
void initC(int n){
    C.assign(n+1, vector<llt>(n+1, 0LL));
    C[0][0] = 1;
	for(int i=1;i<=n;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
	}
}

inline mint f(llt n, llt k){
    if(0 == n && 0 == k) return mint(1);
    if(0 == n) return mint(0);
    return C[n+k-1][n-1];
}

llt proc(){
    // procA();
    // procB();   

    mint ans;
    for(int sheng=0;sheng<=min(X, N);++sheng){
        for(int ping=max(N-sheng-Y,max(0, M-3*sheng));ping<=N-sheng;++ping){
            int fu = N - sheng - ping;

            assert(0 <= fu && 0 <= sheng  && 0 <= ping && sheng + ping + fu == N);
            assert(sheng * 3 + ping >= M);
            assert(sheng <= X);
            assert(fu <= Y);

            int jinqiu = X - sheng;
            int diuqiu = Y - fu;

            mint tmp;
            for(int k=0,lim=min(X-sheng ,Y-fu);k<=lim;++k){
                tmp += f(N, k) * f(sheng, X-sheng-k) * f(fu, Y-fu-k);   
            }
            ans += tmp * C[N][sheng] * C[N-sheng][ping];
        }
    }

    return ans.value;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    initC(200);    
    N = getInt();
    M = getInt();
    X = getInt();
    Y = getInt();
    cout << proc() << endl;
    return 0;
}
