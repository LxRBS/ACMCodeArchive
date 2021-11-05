//给定有向图，问所有点对的最短距离的平均值
//保证所有点对均联通

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

int Dist[101][101];
int I2V[101];
int Vn;
bool read(){
    int a,b;
    scanf("%d%d",&a,&b);

    if ( 0 == a && 0 == b ) return false;

    Vn = 0;
    fill(I2V,I2V+101,0);
    for(int i=1;i<=100;++i)fill(Dist[i],Dist[i]+101,1000000000);

    I2V[a] = ++Vn;
    I2V[b] = ++Vn;
    Dist[1][2]  = 1;

    while(1){
        scanf("%d%d",&a,&b);
        if ( 0 == a && 0 == b ) return true;

        if ( 0 == I2V[a] ) I2V[a] = ++Vn;
        if ( 0 == I2V[b] ) I2V[b] = ++Vn;

        Dist[I2V[a]][I2V[b]] = 1;
    }
}


//Floyd算法
void Floyd(int n){
	//三重循环
	for(int k=1;k<=n;++k)for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)
		Dist[i][j] = min(Dist[i][j],Dist[i][k]+Dist[k][j]);
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        Floyd(Vn);
        int sum = 0;
        for(int i=1;i<=Vn;++i)for(int j=1;j<=Vn;++j)if(i!=j) sum += Dist[i][j];
        printf("Case %d: average length between pages = %.3f clicks\n",kase,(double)sum/(double)(Vn*Vn-Vn));
    }
    return 0;
}
