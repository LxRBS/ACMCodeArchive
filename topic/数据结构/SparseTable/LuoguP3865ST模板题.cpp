/**
    Sparse Table ģ����
*/
#include <bits/stdc++.h>
using namespace std;

typedef int value_t;
int const SIZE = 100010;

//Ԥ����sparse table���飬������0��ʼ
void sparseTable(value_t const a[],int n,int mmax[][20]){
    for(int i=0;i<n;++i) mmax[i][0] = i;

    for(int j=1,tmp;(tmp=(1<<j))<=n;++j){
        for(int i=0;i+tmp<=n;++i){
            mmax[i][j] = a[mmax[i][j-1]] < a[mmax[i+(tmp>>1)][j-1]] ? mmax[i+(tmp>>1)][j-1] : mmax[i][j-1];
        }
    }
}

//��ѯa[s...e]�ļ�ֵ
int query(value_t const a[],int const mmax[][20],int s,int e){
    int k = (int)(log(double(e-s+1))/log(2.0));
    return max(a[mmax[s][k]],a[mmax[e-(1<<k)+1][k]]);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int A[SIZE];
int M[SIZE][20];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    for(int i=0;i<n;++i)A[i] = getUnsigned();

    sparseTable(A,n,M);
    while(m--){
        int a = getUnsigned()-1;
        printf("%d\n",query(A,M,a,getUnsigned()-1));
    }
    return 0;
}
