/*
    ����è����
    �е���ϲ��è���ṷ
    �е���ϲ��������è
    ������Ҫ�Ƴ����ɶ��ĳ������˵���ֻʣ����ϲ���Ķ�����ͻ��������
    ��������ö��ٸ�������

    �����ںڰ׸�Ⱦɫ������Ϊ���㣬������֮�佨��
    �����������ڶ����ȥ���ƥ��
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

//just as its names
int const SIZE_OF_VERTICES = 100000;
int const SIZE_OF_EDGES = 451000;
int const INF = 0x3F3F3F3F;

vector<int> Graph[SIZE_OF_VERTICES];//����ͼ���󣬶�������ͨ��ͼ����

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	for(int i=1;i<=n;++i) Graph[i].clear();
}

//�����
inline void mkEdge(int a,int b){
	Graph[a].push_back(b);
}

int LinkA[SIZE_OF_VERTICES];//LinkAi is the link of Ai in B
int LinkB[SIZE_OF_VERTICES];//LinkBi is the link of Bi in A

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//���

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(vector<int>::iterator it=Graph[u].begin();it!=Graph[u].end();++it){
            if ( 0 == DB[ v = *it ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = LinkB[v] ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//�����������
bool dfs(int u){
    int v;
    for(vector<int>::iterator it=Graph[u].begin();it!=Graph[u].end();++it){
        if ( !_Flag[v=*it] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(LinkB[v]) ) ){
                LinkA[ LinkB[v] = u ] = v;
                return true;
            }
        }
    }
    return false;
}

//na��A��������nb��B������
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}

int N,M,P;
char OA[100],OB[100];
vector<int> LikeCat[110],LikeDog[110],DisLikeCat[110],DisLikeDog[110];
bool read(){
    if ( EOF == scanf("%d%d%d",&N,&M,&P) ) return false;

    for(int i=1;i<=N;++i){
        LikeCat[i].clear();
        DisLikeCat[i].clear();
    }
    for(int i=1;i<=M;++i){
        LikeDog[i].clear();
        DisLikeDog[i].clear();
    }

    char ch;
    int a;
    for(int i=1;i<=P;++i){
        scanf("%s%s",OA,OB);

        sscanf(OA,"%c%d",&ch,&a);
        if ( 'C' == ch ) LikeCat[a].push_back(i);
        else LikeDog[a].push_back(i);


        sscanf(OB,"%c%d",&ch,&a);
        if ( 'C' == ch ) DisLikeCat[a].push_back(i);
        else DisLikeDog[a].push_back(i);
    }

    initGraph(P);
    for(int i=1;i<=N;++i){
        for(vector<int>::iterator it=LikeCat[i].begin();it!=LikeCat[i].end();++it)
            for(vector<int>::iterator jt=DisLikeCat[i].begin();jt!=DisLikeCat[i].end();++jt){
                mkEdge(*it,*jt);mkEdge(*jt,*it);
            }
    }

    for(int i=1;i<=M;++i){
        for(vector<int>::iterator it=LikeDog[i].begin();it!=LikeDog[i].end();++it)
            for(vector<int>::iterator jt=DisLikeDog[i].begin();jt!=DisLikeDog[i].end();++jt){
                mkEdge(*it,*jt);mkEdge(*jt,*it);
            }

    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);

    while(read()){
        printf("%d\n",P-HopcroftKarp(P,P)/2);
    }
    return 0;
}
