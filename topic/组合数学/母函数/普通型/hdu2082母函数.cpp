//典型的母函数，求幂为50(包括)以下的系数和
#include <cstdio>
#include <algorithm>
#include <numeric>
using namespace std;

int A[26];
int G[51];//多项式系数
int T[51];//临时变量
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		for(int i=0;i<26;++i)scanf("%d",A+i);

        //首先将G设置为第一个式子，也就是字母A的
		fill(G,G+A[0]+1,1);
		fill(G+A[0]+1,G+51,0);
		fill(T,T+51,0);

		//连乘，考虑到后面的式子系数要么为1要么为0，因此不必写出正规的多项式乘法
		for(int i=1;i<26;++i){
			for(int j=0;j<51;++j)for(int k=0;k<=A[i]*(i+1)&&k<51;k+=i+1){
				if ( j + k < 51 )//只计算50次及以下的
				    T[j+k] += G[j];
			}
			//将临时变量的值拷贝到G
			copy(T,T+51,G);
            //清零
			fill(T,T+51,0);
		}

		//输出，因为0次代表没有字母，也就不算一个单词
		printf("%d\n",accumulate(G+1,G+51,0));
	}
	return 0;
}