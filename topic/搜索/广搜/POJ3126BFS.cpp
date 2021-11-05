/*
    给定两个四位素数a  b，要求把a变换到b
    变换的过程要保证
    每次变换出来的数都是一个四位素数
    而且当前这步的变换所得的素数与前一步得到的素数只能有一个位不同
    而且每步得到的素数都不能重复
*/

#include <stdio.h>
#include <queue>
using namespace std;

//线性筛法
int const SIZE = 10000 + 2;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

int const INF = 1000000;
int D[10000];
int bfs(int a,int b){
    if ( a == b ) return 0;

    fill(D+1000,D+10000,INF);

    queue<int> q;
    q.push(a);
    D[a] = 0;

    while( !q.empty() ){
        int u = q.front();
        q.pop();

        //千位
        int ta = u / 1000, tb = u % 1000, t;
        for(int i=1;i<10;++i)if(i!=ta&&!isComp[t=i*1000+tb]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //百位
        ta = u / 100 % 10;
        for(int i=0;i<10;++i)if(i!=ta&&!isComp[t=u+(i-ta)*100]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //十位
        ta = u / 10 % 10;
        for(int i=0;i<10;++i)if(i!=ta&&!isComp[t=u+(i-ta)*10]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //个位
        ta = u % 10;
        for(int i=0;i<10;++i)if(i!=ta&&!isComp[t=u+(i-ta)]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }
    }

    return -1;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();

    int a,b,nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&a,&b);
        int ret = bfs(a,b);
        if ( -1 != ret ) printf("%d\n",ret);
        else puts("Impossible");
    }
    return 0;
}
