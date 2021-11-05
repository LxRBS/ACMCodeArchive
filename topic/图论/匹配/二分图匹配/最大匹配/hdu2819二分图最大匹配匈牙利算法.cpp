/*
    ����һ��01���󣬿��Ի������С����߻�������
    ���ܷ�ͨ�����������Խ���ȫ��Ϊ1���������
    �����н��ߣ������ƥ���Ƿ�ΪN
    ���������΢�鷳һ�㣬���԰�˳�����
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

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N,N);

    int a;
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        scanf("%d",&a);
        Graph[i][j] = a;
    }

    return true;
}

char Output[110][110];

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        if ( N != Hungary(N,N) ){
            printf("-1\n");
        }else{
            int ret = 0;
            //��ÿһ���ҵ�Ӧ��ƥ����У����н���
            for(int i=1,j;i<=N;++i){
                j = 1;
                while( j <= N && L[j] != i ) ++j;

                if ( i != j ){
                    sprintf(Output[ret++],"C %d %d\n",i,j);
                    swap(L[i],L[j]);
                }

            }
            printf("%d\n",ret);
            for(int i=0;i<ret;++i)printf("%s",Output[i]);
        }
    }
    return 0;
}
