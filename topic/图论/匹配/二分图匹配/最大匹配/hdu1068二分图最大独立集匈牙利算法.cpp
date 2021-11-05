//�����ͼ���������ĵ������������ͼ��������=�ܵ���-���ƥ��
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;


int const SIZE = 1005;

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

int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initGraph(N,N);
    int a,b,c;
    for(int i=1;i<=N;++i){
        a = getUnsigned() + 1;
        c = getUnsigned();
        for(int j=0;j<c;++j){
            b = getUnsigned() + 1;
            Graph[a][b] = true;
        }
    }
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) printf("%d\n",N-Hungary(N,N)/2);
    return 0;
}
