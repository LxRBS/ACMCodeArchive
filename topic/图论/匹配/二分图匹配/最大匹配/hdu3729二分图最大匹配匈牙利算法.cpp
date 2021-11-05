/*
    N��ѧ����
    ÿ��ѧ��˵��һ����Χ[X,Y]
    ��ʾ�����ڸ�����
    ����Щ�˵�˵����ì�ܵ�
    ������ж��ٸ���û��ì��
    ����ж���𰸣����ѧ��������
    ���������㷨�У���������·��ʱ������������
*/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

bool Graph[66][100010];//����ͼ����
int L[100010];//LiΪA����Biƥ��ĵ�
int LinkA[65];
bool Flag[100010];//Fi��ʾBi�Ƿ���������·�У���һ��������

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
            LinkA[node] = i;
            return 1;
        }
    }
    return 0;
}
//naΪA��������nbΪB������
int Hungary(int na,int nb){
    fill(L,L+nb+1,0);
    fill(LinkA,LinkA+na+1,0);

    int ret = 0;
    //����ž����ܴ�����ƥ�䣬������
    for(int i=na;i>=1;--i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb);
    }
    return ret;
}


int N,M;

bool read(){
    if ( 1 != scanf("%d",&N) ) return false;

    initGraph(N,100000);
    int x,y;
    M = 0;
    for(int i=1;i<=N;++i){
        scanf("%d%d",&x,&y);
        M = max(M,y);
        for(int j=x;j<=y;++j)Graph[i][j] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(;nofkase--;){
        read();
        int ans = Hungary(N,M);
        printf("%d\n",ans);
        bool flag = true;
        for(int i=1;i<=N;++i)if(LinkA[i]){
            if ( flag ){
                printf("%d",i);
                flag = false;
            }else{
                printf(" %d",i);
            }
        }
        putchar('\n');
    }
    return 0;
}
