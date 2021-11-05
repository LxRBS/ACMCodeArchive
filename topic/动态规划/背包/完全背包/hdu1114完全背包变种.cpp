//��ȫ�����ı���
//Ҫ�����ȡ��ָ�����ʱ�ܹ��õ�����С����
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef int gains_t;
typedef int cost_t;

//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void completeKnapsack(gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=cost;v<=maxv;++v){
        if ( d[v-cost] != INT_MAX )//�ڱ�׼��ȫ�����н���һ�±仯
        d[v] = min(d[v],d[v-cost]+gains);
    }
}

gains_t G[505];
cost_t C[505];
gains_t D[10010];
int E,F,N;
void read(){
    E = getUnsigned();
    F = getUnsigned();
    N = getUnsigned();
    for(int i=0;i<N;++i) G[i] = getUnsigned(), C[i] = getUnsigned();
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while( nofkase-- ){
        read();

        int x = F - E;
        fill(D,D+x+1,INT_MAX);
        D[0] = 0;
        for(int i=0;i<N;++i) completeKnapsack(D,x,C[i],G[i]);
        if ( INT_MAX == D[x] ) printf("This is impossible.\n");
        else printf("The minimum amount of money in the piggy-bank is %d.\n",D[x]);
    }
    return 0;
}
