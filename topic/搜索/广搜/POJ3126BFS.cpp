/*
    ����������λ����a  b��Ҫ���a�任��b
    �任�Ĺ���Ҫ��֤
    ÿ�α任������������һ����λ����
    ���ҵ�ǰ�ⲽ�ı任���õ�������ǰһ���õ�������ֻ����һ��λ��ͬ
    ����ÿ���õ��������������ظ�
*/

#include <stdio.h>
#include <queue>
using namespace std;

//����ɸ��
int const SIZE = 10000 + 2;//һ��ֻɸ��30000+����
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
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

        //ǧλ
        int ta = u / 1000, tb = u % 1000, t;
        for(int i=1;i<10;++i)if(i!=ta&&!isComp[t=i*1000+tb]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //��λ
        ta = u / 100 % 10;
        for(int i=0;i<10;++i)if(i!=ta&&!isComp[t=u+(i-ta)*100]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //ʮλ
        ta = u / 10 % 10;
        for(int i=0;i<10;++i)if(i!=ta&&!isComp[t=u+(i-ta)*10]){
            if ( t == b ) return D[u] + 1;

            if( D[t] > D[u] + 1 ){
                D[t] = D[u] + 1;
                q.push(t);
            }
        }

        //��λ
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
