/*
    首先判断图是否连通
    不能跨点成边
    然后求生成树的数量
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

struct ufs_t{
    enum{UF_SIZE=330};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;


int const SIZE_OF_COLUMNS = 330;

//a is the determinant to be calculated which will be changed during calculation
//n is n, the valid index is from 0 to n-1
llt determinant(llt (*a)[SIZE_OF_COLUMNS],int const n,llt const mod){
    llt ret = 1;

    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		while( a[j][i] ){
    			llt t = a[i][i] / a[j][i];
    			for(int k=i;k<n;++k){
    				a[i][k] = ( a[i][k] - t * a[j][k] ) % mod;
				}
				for(int k=i;k<n;++k) swap(a[i][k],a[j][k]);
				ret = -ret;
			}
		}

		if ( 0 == a[i][i] ) return 0;

		ret = ret * a[i][i] % mod;
	}

	if ( ret < 0 ) ret += mod;
    return ret;
}

llt const MOD = 10007LL;
int N,R;
llt X[330],Y[330];
llt G[330][330];

inline llt dist2(int idx,int jdx){
    llt x = X[idx] - X[jdx];
    llt y = Y[idx] - Y[jdx];
    return x * x + y * y;
}

inline llt cross(int pdx,int idx,int jdx){
    llt x1 = X[idx] - X[pdx];
    llt y1 = Y[idx] - Y[pdx];
    llt x2 = X[jdx] - X[pdx];
    llt y2 = Y[jdx] - Y[pdx];
    return x1 * y2 - x2 * y1;
}

inline bool isInter(int pdx,int idx,int jdx){
    return 0 == cross(pdx,idx,jdx)
       && X[pdx] <= max(X[idx],X[jdx])
       && min(X[idx],X[jdx]) <= X[pdx]
       && Y[pdx] <= max(Y[idx],Y[jdx])
       && min(Y[idx],Y[jdx]) <= Y[pdx];
}

bool isOK(int idx,int jdx){
     for(int k=0;k<N;++k)if(idx!=k&&jdx!=k&&isInter(k,idx,jdx))return false;
     return true;
}

void read(){
    scanf("%d%d",&N,&R);

    llt r2 = (llt)R * (llt)R;
    memset(G,0,sizeof(G));
    UF.init(N);

    for(int i=0;i<N;++i) scanf("%lld%lld",X+i,Y+i);

    for(int i=0;i<N;++i){
        for(int j=0;j<i;++j){
            if ( dist2(i,j) <= r2 && isOK(i,j) ){//i,j之间有条边
                ++G[i][i];
                ++G[j][j];
                --G[i][j];
                --G[j][i];
                UF.unite(i,j);
            }
        }
    }
}

void proc(){
    //判断是否连通
    bool flag = false;
    for(int i=1;i<N;++i){
        if ( UF.find(i) != UF.find(0) ){
            flag = true;
            break;
        }
    }

    if (flag) {
        printf("-1\n");
        return;
    }

    llt ans = determinant(G,N-1,MOD);
    printf("%lld\n",ans);
}

int main(){
    //freopen("1.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--){
        read();
        proc();
    }
    return 0;
}
