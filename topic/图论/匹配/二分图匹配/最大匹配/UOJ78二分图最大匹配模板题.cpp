//����ͼ���ƥ�䣬ģ���⡣������ƥ�������Լ�����ƥ��
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

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int NA,NB,M;
void read(){
    NB = getUnsigned();
    NA = getUnsigned();
    M = getUnsigned();

    initGraph(NA,NB);

    int a,b;
    for(int i=0;i<M;++i){
        b = getUnsigned();
        a = getUnsigned();
        Graph[a][b] = true;
    }
}
int main(){
    read();
    printf("%d\n",Hungary(NA,NB));
    printf("%d",L[1]);
    for(int i=2;i<=NB;++i)printf(" %d",L[i]);
    putchar('\n');
    return 0;
}
