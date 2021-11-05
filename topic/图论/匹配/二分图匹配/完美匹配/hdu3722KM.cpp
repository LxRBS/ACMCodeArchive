/*
    N���ַ������ų����ɸ���
    ÿ�������ڵ��ַ����ķ���Ϊ��
    ǰһ������ͺ�һ���������ǰ׺
    �����л��Ŀ��ܵ�������
    һ���ַ���Ҳ�����ų�һ����������Ϊ0

    ��Hamilton��·
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

int N;
char S[SIZE][110];
int Len[SIZE];

int f(int idx,int jdx){
    int i = Len[idx] - 1, j = 0;
    while( i >= 0 /*&& S[jdx][j]*/ && S[idx][i] == S[jdx][j] ) --i, ++j;
    return j;
}

bool read(){
    if ( 1 != scanf("%d",&N) ) return false;

    for(int i=1;i<=N;++i){
        scanf("%s",S[i]);
        Len[i] = strlen(S[i]);
    }

    initGraph(N);
    for(int i=1;i<=N;++i)for(int j=1;j<=N;++j)if(i!=j){
        Graph[i][j] = f(i,j);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(;read();){
        weight_t ans = KM(N);
        printf("%d\n",ans);
    }
    return 0;
}
