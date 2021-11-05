/*
    n����Ҫס��m��������
    ÿ����������Ը���ס������
    ÿ�������������ai����
    �Ƿ��ܹ����з���
    
    ʹ�ö���ƥ�䣬�պ�û�г�ʱ
    ʹ��״̬ѹ��Ӧ�ø��� 
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


int Graph[100010][13];//����ͼ����
int L[13][100010];//LiΪA����Biƥ��ĵ�ļ���
int LCnt[13];//Ŀǰ��Bi��ƥ��ĵ������
bool Flag[13];//Fi��ʾBi�Ƿ���������·�У���һ��������
int Limit[13];//Limit[i]ΪBi��ƥ��������

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//nodeΪA�еĽڵ��ţ���1��ʼ
int dfs(int node,int nb){
    for(int i=1;i<=nb;++i){
        //���û�бߣ������Ѿ�������·��
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        if ( LCnt[i] < Limit[i] ){
            L[i][LCnt[i]++] = node;
            return 1;
        }

        for(int j=0;j<LCnt[i];++j)if ( dfs(L[i][j],nb) ){
            L[i][j] = node;
            return 1;
        }
    }
    return 0;
}
//naΪA��������nbΪB������
int Hungary(int na,int nb){
    fill(LCnt,LCnt+nb+1,0);
    for(int i=1;i<=nb;++i)fill(L[i],L[i]+na+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        
        //��������ж����ƥ���Ƿ���ڣ����ֻҪ��һ��û��ƥ����ܹ�ȷ����
        if ( 0 == dfs(i,nb) ) return ret;
        ret += 1;
    }
    return ret;
}


int N,M;
bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    initGraph(N,M);

    for(int i=1;i<=N;++i){
        for(int j=1;j<=M;++j)scanf("%d",Graph[i]+j);
    }

    for(int i=1;i<=M;++i)scanf("%d",Limit+i);

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while(read()){
        int ans = Hungary(N,M);
        printf(ans==N?"YES\n":"NO\n");
    }
    return 0;
}
