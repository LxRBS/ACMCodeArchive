/*
    计算行列式
*/
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMNS = 210;

typedef long long int int_t;

//a is the determinant to be calculated which will be changed during calculation
//n is n, the valid index is from 0 to n-1
int_t determinant(int_t (*a)[SIZE_OF_COLUMNS],int const n,int_t const mod){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i][j]%=mod;
        }
    }

    int_t ret = 1;

    for(int i=0;i<n;++i){
    	for(int j=i+1;j<n;++j){
    		while( a[j][i] ){
    			int_t t = a[i][i] / a[j][i];
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

int_t A[SIZE_OF_COLUMNS][SIZE_OF_COLUMNS];
int N,Mod;

bool read(){
    if ( 2 != scanf("%d%d",&N,&Mod) ) return false;

    for(int i=0;i<N;++i)for(int j=0;j<N;++j)scanf("%lld",A[i]+j);
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) {
        printf("%lld\n",determinant(A,N,Mod));
    }
    return 0;
}

