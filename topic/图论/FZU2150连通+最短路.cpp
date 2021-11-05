/*
    �������ڵ�ͼ���ջ�
    ��0���ȼ2��(������ͬһ��)�ݵأ����ƿ�ʼ��4��������
    ���ܷ����вݵض��չ⣬��������ʱ��
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const INF = 1000000000;

int N,M;
char A[12][12];
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=0;i<N;++i)scanf("%s",A[i]);
    return true;
}

struct ufs_t{
    int father[110];
    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};
int Index[12][12];
int G[110][110];
bool Flag[110];

int proc(){
    int cnt = 0;

    //�����ж��Ƿ����2����ͨ��
    UF.init(N*M);
    memset(Index,0,sizeof(Index));
    memset(G,0,sizeof(G));

    int a,b;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j)if('#'==A[i][j]){
        if ( 0 == Index[i][j] ) Index[i][j] = ++cnt;

        for(int d=0;d<4;++d){
            int dr = i + DR[d];
            int dc = j + DC[d];
            if ( 0 <= dr && dr < N && 0 <= dc && dc < M && '#' == A[dr][dc] ){
                if ( 0 == Index[dr][dc] ) Index[dr][dc] = ++cnt;
                UF.unite(a=Index[i][j],b=Index[dr][dc]);
                G[a][b] = G[b][a] = 1;
            }
        }
    }

    if ( 0 == cnt ) return -1;
    if ( 1 == cnt ) return 0;

    memset(Flag,0,sizeof(Flag));
    int ans = 0;
    for(int i=1;i<=cnt;++i){
        if ( !Flag[a = UF.find(i)] ){
            Flag[a] = true;
            ++ans;
            if ( ans > 2 ) return -1;
        }
    }

    //Floyd
    for(int i=1;i<=cnt;++i)for(int j=1;j<=cnt;++j)if(0==G[i][j]&&i!=j)G[i][j]=INF;
    for(int k=1;k<=cnt;++k)for(int i=1;i<=cnt;++i)for(int j=1;j<=cnt;++j)G[i][j]=min(G[i][j],G[i][k]+G[k][j]);

    if ( 2 == ans ){
        //�����·�е��·
        ans = INF;
        for(int i=1;i<=cnt;++i)for(int j=1;j<=cnt;++j)if( INF != G[i][j] && (INF == ans || ans < G[i][j]) ){
            ans = G[i][j];
        }
        return ( ans + 1 ) >> 1;
    }

    //���ֻ��һ����ͨ��
    ans = INF;
    for(int i=1;i<cnt;++i)for(int j=i+1;j<=cnt;++j){
        //��i��j�գ������Ҫ�೤ʱ��
        int tmp = 0;
        for(int k=1;k<=cnt;++k){
            tmp = max(tmp,min(G[i][k],G[j][k]));
        }
        if ( tmp < ans ) ans = tmp;
    }

    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,proc());
    }
    return 0;
}
