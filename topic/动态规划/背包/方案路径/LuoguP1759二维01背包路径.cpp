/**
   01二维背包，输出具体方案
   要求多种方案时输出尽量靠前的物品
*/
#include <bits/stdc++.h>
using namespace std;
typedef int gains_t;//type of gains
int Path[110][210][210];

void zeroOneKnapsack(int index,gains_t d[][210],int maxv1,int maxv2,int cost1,int cost2,gains_t gains){
    int tmp;
    for(int v1=maxv1;v1>=cost1;--v1)for(int v2=maxv2;v2>=cost2;--v2){
        if(d[v1][v2]<(tmp=d[v1-cost1][v2-cost2]+gains)){
            d[v1][v2] = tmp;
            Path[index][v1][v2] = 1;
        }
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
int N,Sum;
int Cost[2][110];
int Gain[110];
int D[210][210];
void output(int index,int cost1,int cost2){
    if(index-1>0){
        if(Path[index][cost1][cost2]){
            output(index-1,cost1-Cost[0][index],cost2-Cost[1][index]);
        }else{
            output(index-1,cost1,cost2);
        }
    }
    if(Path[index][cost1][cost2]) printf("%d ",index);
}
int main(){
    //freopen("1.txt","r",stdin);
    int m = getUnsigned();
    int v = getUnsigned();
    int n = getUnsigned();
    for(int i=1;i<=n;++i){
        Cost[0][i] = getUnsigned();
        Cost[1][i] = getUnsigned();
        Gain[i] = getUnsigned();
    }
    for(int i=1;i<=n;++i){
        zeroOneKnapsack(i,D,m,v,Cost[0][i],Cost[1][i],Gain[i]);
    }
    printf("%d\n",D[m][v]);
    output(n,m,v);puts("");
    return 0;
}
