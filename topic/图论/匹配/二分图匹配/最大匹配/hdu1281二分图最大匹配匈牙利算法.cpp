/*
    ����һ�����̣�������ܷŶ��ٸ���
    �����ʹؼ����ж��ٸ�
    �����Ŀ��hdu1045һ����Ӧ������
    ��ʵ����ֱ�Ӱ����н��߼���
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 505;

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

int N,M,K;
bool read(){
    if ( EOF == scanf("%d%d%d",&N,&M,&K) ) return false;

    initGraph(N,M);
    int a,b;
    for(int i=0;i<K;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        int ans = Hungary(N,M);

        int ret = 0;
        //��ÿһ���ߣ�ɾ��֮���������ƥ��
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j)if(Graph[i][j]){
            Graph[i][j] = false;
            if ( ans != Hungary(N,M) ) ++ret;
            Graph[i][j] = true;
        }

        printf("Board %d have %d important blanks for %d chessmen.\n",kase,ret,ans);
    }
    return 0;
}
