#include <cstdio>
#include <algorithm>
using namespace std;

double FAC[11] = {
	1.0,1.0,2.0,6.0,24.0,120.0,720.0,
	5040.0,40320.0,362880.0,3628800.0
};

int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
		int a[11];
		for(int i=0;i<n;++i)scanf("%d",a+i);

		//初始化
		double c1[11]={0.0},c2[11]={0.0};
		for(int i=0;i<=a[0];++i) c1[i] = 1.0 / FAC[i];

		//乘
		for(int i=1;i<n;++i){
			//j+k次的系数依次加上j次的系数，因为k这边的系数始终为1
			//超过m次的不必关心
			for(int j=0;j<=m;++j)
				for(int k=0;k<=a[i]&&k+j<=m;++k)
				    c2[j+k] += c1[j] / FAC[k];
            
			//保存结果，清除临时变量
			copy(c2,c2+m+1,c1);
			fill(c2,c2+m+1,0.0);
			
		}

		//确定结果
		double ans = c1[m] * FAC[m];
        printf("%.0lf\n",ans);

	}
	return 0;
}