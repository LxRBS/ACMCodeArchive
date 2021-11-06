/**
    给定若干type，每个type若干个物品，每个物品有a、b、c、d
    要求每个type选一个物品，
    使得(100+SIGMA(a))(100+SIGMA(b))(100+SIGMA(c))(100+SIGMA(d))乘积最大
    深搜。注意若某个type本来就没有物品，则不要搜索，否则超时
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,K;
int A[55][55];
int B[55][55];
int C[55][55];
int D[55][55];
int Cnt[55];
int Type[55];
int TCnt;

llt Ans;
llt CurA,CurB,CurC,CurD;

//当前搜索第depth类物品
void dfs(int depth){
    if(depth==TCnt){
        llt tmp = CurA*CurB*CurC*CurD;
        if(Ans<tmp) Ans = tmp;
        return;
    }

    int real_type = Type[depth];

    int& cnt = Cnt[real_type];
    for(int i=0;i<cnt;++i){
        //做变化
        CurA += A[real_type][i];
        CurB += B[real_type][i];
        CurC += C[real_type][i];
        CurD += D[real_type][i];
        dfs(depth+1);
        //还原
        CurA -= A[real_type][i];
        CurB -= B[real_type][i];
        CurC -= C[real_type][i];
        CurD -= D[real_type][i];
    }
}

int main() {
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        K = getUnsigned();
        fill(Cnt,Cnt+K+1,0);
        for(int i=1;i<=N;++i){
            int type = getUnsigned();
            int& idx = Cnt[type];
            A[type][idx] = getUnsigned();
            B[type][idx] = getUnsigned();
            C[type][idx] = getUnsigned();
            D[type][idx++] = getUnsigned();
        }

        TCnt = 0;
        for(int i=1;i<=K;++i){
            if(Cnt[i]){
                Type[TCnt++] = i;
            }
        }

        Ans = 0LL;
        CurA = CurB = CurC = CurD = 100LL;
        dfs(0);
        printf("%lld\n",Ans);
    }
    return 0;
}
