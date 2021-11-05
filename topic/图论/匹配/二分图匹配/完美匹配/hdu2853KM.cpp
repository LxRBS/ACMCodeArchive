/*
    �ڴ�Ȩ����ͼ�ϣ�
    �Ѿ�������һ��ƥ��

    ����Ҫ�����Ȩƥ��
    ͬʱҪ�����ԭƥ��䶯����

    Ҫ���������ԭƥ��䶯���٣�
    Ҳ����˵��������Ȩֵ����Ҷ��ܹ�������ƥ��ʱ��
    Ҫ����ѡ��ԭƥ��ı�

    ���Ҫ��ԭƥ��ߵ�ȨֵҪ������ͨ��
    ������ʹ�ö�Ԫ������ʾȨֵ����Ϊ����Ҫ����Ӽ��������鷳
    ��Ȩֵ����һ��

    �����ܵ�ƥ������Ϊ50��
    ������Ȩֵ������55
    ԭƥ����ټ�1�������߾ͱ����ֿ���
    ���Ĵ𰸳���55���õ�����ƥ���Ȩֵ
    ��55ȡ�������õ�����ƥ���ʵ�ʱ���
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 210;
weight_t const INF = 1000000000;

weight_t Graph[SIZE][SIZE];//����ͼ���ڽӾ���A/B����Ҫ��һ����
//LinkAi��ʾ��Ai�����ĵ㣬LinkBi��ʾ��Bi�����ĵ�
int LinkA[SIZE],  LinkB[SIZE];
//�����������
bool FlagA[SIZE], FlagB[SIZE];
int Pre[SIZE];

inline void initGraph(int n){
    for(int i=1;i<=n;++i)fill(Graph[i],Graph[i]+n+1,0);
}

weight_t LabelA[SIZE], LabelB[SIZE];
weight_t Slack[SIZE];

int Q[SIZE<<1];//��������
inline void bfs(int u,int n) {
    weight_t tmp;
    int v, head=0, tail = 0;
    FlagA[Q[tail++] = u] = true;

DEAD_LOOP:
    while(head < tail) {

        for(u = Q[head++],v=1;v<=n;++v)if(!FlagB[v]){
            if ( (tmp = LabelA[u]+LabelB[v]-Graph[u][v]) > Slack[v] ) continue;

            Pre[v] = u;
            if(!tmp) {
                FlagB[v] = true;
                if(!LinkB[v]) {
                    while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
                    return;
                }
                FlagA[ Q[tail++]=LinkB[v] ] = true;
            }else{
                Slack[v] = tmp;
            }
        }
    }

    tmp = INF;
    for(int i=1;i<=n;++i) if(!FlagB[i]&&Slack[i]<tmp) tmp = Slack[i];
    for(int i=1;i<=n;++i) {
        if(FlagA[i]) LabelA[i] -= tmp;
        if(FlagB[i]) LabelB[i] += tmp;
        else Slack[i] -= tmp;
    }

    for(v = 1; v <= n; ++v) {
        if(!FlagB[v] && !Slack[v]) {
            FlagB[v] = true;
            if(!LinkB[v]) {
                while(v) LinkB[v] = Pre[v], swap(LinkA[Pre[v]], v);
                return;
            }
            FlagA[ Q[tail++] = LinkB[v] ] = true;
        }
    }
    goto DEAD_LOOP;
}

weight_t KM(int n){
    fill(LinkA,LinkA+n+1,0);
    fill(LinkB,LinkB+n+1,0);
    fill(LabelB,LabelB+n+1,0);
    fill(Pre,Pre+n+1,0);
    for(int i=1;i<=n;++i) LabelA[i] = *max_element(Graph[i]+1,Graph[i]+n+1);

    for(int i=1;i<=n;++i){
        fill(Slack,Slack+n+1,INF);
        fill(FlagA,FlagA+n+1,false);
        fill(FlagB,FlagB+n+1,false);
        bfs(i,n);
    }

    weight_t ret = 0;
    for(int i=1;i<=n;++i) ret += LabelA[i] + LabelB[i];
    return ret;
}

int N,M;
weight_t OriginAns;
int OriginLA[SIZE];
bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    initGraph(M);
    int w;
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        scanf("%d",&w);
        Graph[i][j] = w * 55;
    }

    OriginAns = 0;
    for(int i=1;i<=N;++i){
        scanf("%d",OriginLA+i);
        OriginAns += Graph[i][OriginLA[i]]++;
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(;read();){
        weight_t ans = KM(M);

        //��ѯ�䶯���
        int cnt = 0;
        for(int i=1;i<=N;++i)if(LinkA[i]!=OriginLA[i])++cnt;

        printf("%d %d\n",cnt,ans/55-OriginAns/55);
    }
    return 0;
}
