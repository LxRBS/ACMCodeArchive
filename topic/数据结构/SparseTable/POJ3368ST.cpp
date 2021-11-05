#include <stdio.h>
#include <math.h>

#define  SIZE 100000

int A[SIZE];
int M[SIZE][16];
int Left[SIZE];
int Rank[SIZE];

void init(int n){
    int i,j;
	
	//初始化，直接使用真实值
	for(i=0;i<n;i++) M[i][0] = A[i];

	//倍增
	for(j=1;1<<j<=n;j++)
		for(i=0;i+(1<<j)<=n;i++){
		    int x = M[i][j-1];
			int y = M[i+(1<<(j-1))][j-1];

			if ( x >= y ) M[i][j] = x;
			else          M[i][j] = y;
		}
			
	return ;
}

int query(int a,int b){
	int k;
	int x,y;
	
	if ( a > b ) return 0;

	if ( a == b ) return A[a];

	k = (int)( log((double)(b-a+1)) / log(2.0) );

	x = M[a][k];
	y = M[b+1-(1<<k)][k];

	return x >= y ? x : y;
}

int main(){
    int n,q;
	int i,k;
	int t1,t2;
	int left,frq;
	int a,b;
	int ans;

	while( scanf("%d",&n) && n ){
        scanf("%d",&q);
		k = 0;
		i = -1;
		scanf("%d",&t1);

		//这个循环统计输入中相等的数的频率，出现的地点
L_MAIN_1:
		i++;
		Rank[i] = k;
		Left[k] = i;
		frq = 1;
		
		//当下一个数与上一个数相等时，一直读取
		while( i + 1 < n && scanf("%d",&t2) && t1 == t2 ) frq++,i++,Rank[i]=k;
        
		A[k] = frq;
		k++;

		//保留新读取的数
		t1 = t2;
		if ( i + 1 < n ) goto L_MAIN_1;

        init(k);
		
		for(i=0;i<q;i++){
			scanf("%d%d",&t1,&t2);

			a = Rank[t1-1];
			b = Rank[t2-1];

			if ( a == b ){
				printf("%d\n",t2-t1+1);
				continue;
			}

			//区间值
			ans = query(a+1,b-1);

			//左边界值
			k = Left[a] + A[a] - t1 + 1;
            if ( ans < k ) ans = k;

			//右边界值
			k = t2 - Left[b];
			if ( ans < k ) ans = k;

            printf("%d\n",ans);
		}
	}

	return 0;
}