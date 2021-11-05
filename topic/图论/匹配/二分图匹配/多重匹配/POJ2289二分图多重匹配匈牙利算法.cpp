/*
    n���˷�m���飬ÿ��������������Ժ�ѡ
    ����ô��ʹ����������������

    ��ÿһ�����ƣ�ʹ���������㷨�����ƥ��
    ��С�����Ƽ�Ϊ��
*/

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
int const SIZE = 1010;

bool Graph[SIZE][SIZE];//����ͼ����
int L[SIZE][SIZE];//LiΪA����Biƥ��ĵ�ļ���
int LCnt[SIZE];//Ŀǰ��Bi��ƥ��ĵ������
bool Flag[SIZE];//Fi��ʾBi�Ƿ���������·�У���һ��������

inline void initGraph(int na,int nb){
    memset(Graph,0,sizeof(Graph));
}

//nodeΪA�еĽڵ��ţ���1��ʼ
int dfs(int node,int nb,int limit){
    for(int i=1;i<=nb;++i){
        //���û�бߣ������Ѿ�������·��
        if ( !Graph[node][i] || Flag[i] ) continue;
        Flag[i] = true;

        if ( LCnt[i] < limit ){
            L[i][LCnt[i]++] = node;
            return 1;
        }

        for(int j=0;j<LCnt[i];++j)if ( dfs(L[i][j],nb,limit) ){
            L[i][j] = node;
            return 1;
        }
    }
    return 0;
}
//naΪA��������nbΪB������
int Hungary(int na,int nb,int limit){
    fill(LCnt,LCnt+nb+1,0);
    for(int i=1;i<=nb;++i)fill(L[i],L[i]+na+1,0);

    int ret = 0;
    for(int i=1;i<=na;++i){
        fill(Flag,Flag+nb+1,false);
        ret += dfs(i,nb,limit);
    }
    return ret;
}

int N,M;
char Input[5000];
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false;

    fgets(Input,4999,stdin);

    initGraph(N,M);

    for(int i=1;i<=N;++i){
        fgets(Input,4999,stdin);
        stringstream ss(Input);
        string name;
        ss>>name;
        int b;
        while(ss>>b){
            Graph[i][++b] = true;
        }
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        int left = 0,right = N,mid;

        do{
            mid = ( left + right ) >> 1;
            if ( Hungary(N,M,mid) == N ) right = mid - 1;
            else left = mid + 1;
        }while( left <= right );

        printf("%d\n",left);
    }
    return 0;
}
