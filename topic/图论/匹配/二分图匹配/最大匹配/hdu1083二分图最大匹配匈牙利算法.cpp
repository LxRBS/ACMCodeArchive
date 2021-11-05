/*
    N��ѧ����P���γ�
    ���Ƿ���Դ�N��ѧ��������P����ʹ��ǡ�ø�����һ�ſγ�
    ���������ƥ�����Ƿ����P
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
    fill(L,L+nb+1,0);
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
    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}

int N,P;
bool read(){
    scanf("%d%d",&P,&N);

    initGraph(N,P);
    int n,a;
    for(int i=1;i<=P;++i){
        scanf("%d",&n);
        while(n--){
            scanf("%d",&a);
            Graph[a][i] = true;
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
        printf(P==Hungary(N,P)?"YES\n":"NO\n");
    }
    return 0;
}
