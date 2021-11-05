/*
    һȺ�ˣ����д��ڻ�����ʶ��ĳЩ��
    �ʣ����Ƚ���Ⱥ�˷ֳ����飬Ҫ��ͬ���˶�����ʶ
    ��Σ�����ÿһ����ʶ�������£�������ܰ��Ŷ��ٶ�
    ��һ�����ж϶���ͼ���ڶ����Ƕ���ͼ���ƥ��
    �ر�Ҫע��������û�е�һ��ֱ�������ƥ�䣬�Ͳ��Ƕ���ͼƥ�����һ��ͼƥ��
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

int Q[SIZE];
int Color[SIZE];
bool isOK(int vn){
    fill(Color,Color+vn+1,0);

    int u,v,head = 0, tail = 0;

    for(int i=1;i<=vn;++i)if(0==Color[i]){
        Color[Q[tail++] = i] = 1;

        while( head != tail ){
            u = Q[head++];
            for(v=1;v<=vn;++v)if(Graph[u][v]){
                if ( 0 == Color[v] ){
                    Color[Q[tail++] = v] = Color[u] ^ 3;
                }else if ( Color[v] == Color[u] ){
                    return false;
                }
            }
        }
    }
}

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initGraph(N,N);
    int a,b;
    for(int i=0;i<M;++i){
        scanf("%d%d",&a,&b);
        Graph[a][b] = Graph[b][a] = true;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        if ( isOK(N) ){
            printf("%d\n",Hungary(N,N)/2);
        }else{
            printf("No\n");
        }
    }
    return 0;
}
