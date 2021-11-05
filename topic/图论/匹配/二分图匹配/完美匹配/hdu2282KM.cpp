/*
    N������ΧһȦ�����N���ɿ�����������
    ÿһ�Σ����԰�һ���ɿ�����һ�������Ƶ����ں���
    ��ʹÿ������ǡ������ֻ��һ���ɿ�����
    ����Ҫ�ƶ����ٴ�

    ���ɿ����ĺ���Ϊһ�ߣ��պ���Ϊ��һ��
    ��ĳ��������n���ɿ���
    ��������Ӳ��n-1���㣬ÿ���㵽�����պ��ӵı�ȨΪ�ƶ�����
    ��һ����СȨƥ��
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 510;
weight_t const INF = 1000000000;
weight_t const MAG = 10000;

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

int N,V[SIZE];
int NA;
bool read(){
    if ( 1 != scanf("%d",&N) ) return false;

    vector<int> va,vb;
    for(int i=1;i<=N;++i){
        scanf("%d",V+i);
        if ( V[i] > 1 ) va.push_back(i);
        else if ( 0 == V[i] ) vb.push_back(i);
    }

    initGraph(N);
    NA = 0;
    for(vector<int>::iterator it=va.begin();it!=va.end();++it){
        //�ظ�V[*it]-1��
        for(int i=1,tn=V[*it]-1;i<=tn;++i)for(unsigned j=0;j<vb.size();++j){
            int t1 = *it - vb[j];
            if ( t1 < 0 ) t1 = -t1;
            if ( ( t1 << 1 ) > N ) t1 = N - t1;

            Graph[i+NA][j+1] = MAG - t1;
        }
        NA += V[*it]-1;
    }

    N = vb.size();
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%d\n",MAG*NA-KM(N));
    }
    return 0;
}