//树状数组，156ms，1048k，1651B
#include <iostream>
#include <cstring>
using namespace std;

#define SIZE 100004

//树状数组
int C[SIZE] = {0};

//源数组
int A[SIZE] = {0};

//计算x的二进制位的最低位1代表的数值
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//更新，将第idx节点值加上v
//树状数组总长度为n，下标范围从1到n
void update(int idx,int v,int n){
	while( idx <= n ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

//对前x项求和
int sum(int x){
    int sum = 0;
	while( x > 0 ){
	    sum += C[x];
		x -= lowbit(x);
	}
    return sum;
}

//记录左右大小数组
int L_G[SIZE],L_L[SIZE];
int R_G[SIZE],R_L[SIZE];

int main(){
    int tofkase;
	scanf("%d",&tofkase);
	while(tofkase--){
	    int n;
		scanf("%d",&n);

		//读入源数据
		for(int i=1;i<=n;++i)
			scanf("%d",A+i);

		//清空树状数组
		memset(C,0,sizeof(C));

		//从左往右建立更新树状数组，每一次数组中的值都反映了第i个数左边的情况
		for(int i=1;i<=n;++i){
			//以A[i]为下标，该下标处+1
			//所有比A[i]小的数所指示的节点都不会发生改变
		    update(A[i],1,SIZE);

			//A[i]左边一共有多少个1，求和得到，就是比A[i]小的数的个数
			L_L[i] = sum( A[i] - 1 );
            //sum(SIZE)是所有的数的个数(i的左边),sum(A[i])是所有小于等于A[i]的数的个数
			L_G[i] = sum( SIZE ) - sum( A[i] );
		}

		//清空树状数组
		memset(C,0,sizeof(C));

		//从右往左建立更新树状数组
		for(int i=n;i>=1;--i){
		    update(A[i],1,SIZE);
            R_L[i] = sum( A[i] - 1 );
			R_G[i] = sum( SIZE ) - sum( A[i] );
		}

		long long ans = 0;
		for(int i=1;i<=n;++i)
			ans += L_L[i] * R_G[i] + L_G[i] * R_L[i];

		printf("%I64d\n",ans);
	}
	return 0;
}