/*
    K��������C��ţ
    ÿ���������������M��ţ
    ţ�������и�����
    ��ţ���䵽����
    Ҫ��ʹ���ߵ���Զ��ţ�ߵľ������
    �Ӵ�С����ÿ����ȥ������ƥ�����ܷ�C
    ȥ���Ժ�Ͳ���ƥ����Ǵ�
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
int const SIZE = 1010;

int Graph[SIZE][SIZE];//����ͼ����
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

int K,C,M;
int D[240][240];
vector<int> W;
bool read(){
    if ( EOF == scanf("%d%d%d",&K,&C,&M) ) return false;

    for(int i=1;i<=K+C;++i)for(int j=1;j<=K+C;++j){
        scanf("%d",D[i]+j);
        if ( 0 == D[i][j] ) D[i][j] = 1000000000;
    }

    //Floyd�㷨�����·
    for(int k=1;k<=K+C;++k)for(int i=1;i<=K+C;++i)for(int j=1;j<=K+C;++j)
        D[i][j] = min(D[i][j],D[i][k]+D[k][j]);

    //��ͼ
    initGraph(C,K);
    for(int i=K+1;i<=K+C;++i)for(int j=1;j<=K;++j) {Graph[i-K][j] = D[i][j];W.push_back(D[i][j]);}

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        sort(W.begin(),W.end(),greater<int>());

        //Ӧ��ʹ�ö��ַ�������������˱���
        int ans;
        for(vector<int>::iterator it=W.begin();it!=W.end();++it){
            for(int i=1;i<=C;++i)for(int j=1;j<=K;++j)if(Graph[i][j]==*it)Graph[i][j]=0;
            if ( Hungary(C,K,M) != C ) {
                ans = *it;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
