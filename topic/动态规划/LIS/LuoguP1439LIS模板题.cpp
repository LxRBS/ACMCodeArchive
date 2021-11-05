/**
    最长上升子序列，模板题
*/
#include <bits/stdc++.h>
using namespace std;


typedef int value_t;

//最长上升子序列
//src是源数组，n表示src有n个元素，从1开始
//di为表示长度为i的最长子序列的结尾元素
int lis(value_t const src[],int n,value_t d[]){
    int ret = 1;
    d[1] = src[1];
    for(int i=2;i<=n;++i){
        if ( d[ret] < src[i] ) d[++ret] = src[i];
        else *lower_bound(d+1,d+ret+1,src[i]) = src[i];
    }
    return ret;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int A[100010],B[100010],D[100010];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    for(int i=1;i<=n;++i)A[getUnsigned()]=i;
    for(int i=1;i<=n;++i)B[i]=A[getUnsigned()];
    printf("%d\n",lis(B,n,D));
    return 0;
}
