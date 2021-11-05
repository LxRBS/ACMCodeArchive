#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE_OF_VERTIECES = 550;
weight_t const INF = 0x3F3F3F3F;

weight_t Graph[SIZE_OF_VERTIECES][SIZE_OF_VERTIECES];//ͼ���ڽӱ�������1��ʼ

inline void initGraph(int vn=0){
    memset(Graph,0,sizeof(Graph));
}

//�������������������������С��ֵ�Լ�S��T,O(N*N)
//w��flag��behalf�Ǹ������飬behalf[i]Ϊ��˵����i���Ƕ����Ķ��Ǳ������˱�ĵ���
weight_t contract(int vn,int&s,int&t,weight_t w[],bool flag[],bool behalf[]){
    fill(w,w+vn+1,0);
    fill(flag,flag+vn+1,false);

    weight_t ans;
    for(int j,k,i=1;i<=vn;++i){
        k = 0;
        //�ҵ������м�������Ȩֵ���ĵ�k
        for(j=1;j<=vn;++j)if(!behalf[j]&&!flag[j]&&(!k||w[j]>w[k])) k = j;
        if (!k) break;
        //������¼s��t�����ҽ�k�����м���
        s = t; flag[t=k] = true;
        ans = w[k];
        for(j=1;j<=vn;++j)if(!behalf[j]&&!flag[j]) w[j] += Graph[k][j];
    }
    return ans;
}

//vnΪ����������w��flag��behalf�Ǹ�������
weight_t StoerWagner(int vn,weight_t w[],bool flag[],bool behalf[]){
    weight_t ans = INF;
    fill(behalf,behalf+vn+1,0);

    for(int s,t,i=1;i<vn;++i){
        ans = min(ans,contract(vn,s,t,w,flag,behalf));
        //˵��ͼ����Ͳ���ͨ
        if ( 0 == ans ) return 0;
        //��t����s��
        behalf[t] = true;
        for(int j=1;j<=vn;++j)if(!behalf[j])Graph[s][j] += Graph[t][j],Graph[j][s] += Graph[j][t];
    }
    return ans;
}

int N,M;
bool read(){
    if ( 2!=scanf("%d%d",&N,&M) ) return false;
    initGraph();
    for(int a,b,c,i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&c);
        Graph[++a][++b] += c;
        Graph[b][a] += c;
    }
    return true;
}

bool F1[SIZE_OF_VERTIECES],F2[SIZE_OF_VERTIECES];
int W[SIZE_OF_VERTIECES];
int main(){
    //freopen("1.txt","r",stdin);
    while(read()){
        printf("%d\n",StoerWagner(N,W,F1,F2));
    }
    return 0;
}
