/*
    N���к���N��Ů��
    ÿ��Ů����һ����ѡ���к��б�
    ÿ��Ů�������ѵı�ѡҲ���Ǹ�Ů���ı�ѡ
    ��ƥ�䣬���N��Ů������ƥ�䣬�ͳ������һ��
    �������������
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 110;

bool Graph[SIZE][SIZE];//����ͼ����
int L[SIZE];//LiΪA����Biƥ��ĵ�
bool Flag[SIZE];//Fi��ʾBi�Ƿ���������·�У���һ��������

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//nodeΪA�еĽڵ��ţ���1��ʼ
int dfs(int node,int nb){
    for(int i=1;i<=nb;++i){
        //���û�бߣ������Ѿ�������·��
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        //���߽���죬����Bi�Ѿ�ʹ�ù�
        if ( 0 == L[i] || dfs(L[i],nb) ){
            L[i] = node;
            return 1;
        }
    }
    return 0;
}
//naΪA��������nbΪB������
int Hungary(int na,int nb){
    fill(L,L+nb+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}

struct ufs_t{
    enum{UF_SIZE=110};
    int father[UF_SIZE+1];

    void init(int n){for(int i=0;i<=n;++i)father[i]=i;}
    int find(int x){return father[x]==x?x:father[x]=find(father[x]);}
    void unite(int x,int y){father[find(y)]=find(x);}
}UF;

int N,M,F;
bool read(){
    if ( 3 != scanf("%d%d%d",&N,&M,&F) ) return false;

    initGraph(N,N);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = true;
    }

    UF.init(N);
    for(int i=0;i<F;++i){
        scanf("%d%d",&a,&b);
        UF.unite(a,b);
    }

    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j)if(UF.find(i)==UF.find(j)){
        for(int k=1;k<=N;++k){
            if ( Graph[j][k] ) Graph[i][k] = true;
            if ( Graph[i][k] ) Graph[j][k] = true;
        }
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();

        int cnt = 0;
        while( Hungary(N,N) == N ){
            ++cnt;
            //ɾ���Ѿ�ʹ�ù���ƥ���
            for(int i=1;i<=N;++i) Graph[L[i]][i] = false;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
