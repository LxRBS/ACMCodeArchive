/*
    N���ˣ�M�䷿�����뷿Ϊһ��һ��ϵ
    ÿ���˶�ĳЩ����ϲ�ö�
    ���з��䣬Ҫ��ÿ���˶��з�ס����ϲ�ö����
    ���ϲ����Ϊ��������û��ϲ�öȣ����ܷ���÷���

    2 2 4
    0 0 1
    0 1 4
    1 0 -1
    1 1 1

    ����������2��������-1

    ���в��ܽ��ߵı߽�һ��������
    ��һ�����Ȩƥ��
    ���1~N��ÿ���㣬���ƥ���Ϊ�������˵���õ�ʵ����û��ƥ��
    ���򣬼�ȥ����ĸ��ߣ����Ǵ�
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef int weight_t;

int const SIZE = 510;
weight_t const INF = 1000000000;
weight_t const NEG = -20000;

weight_t Graph[SIZE][SIZE];//����ͼ���ڽӾ���A/B����Ҫ��һ����
//LinkAi��ʾ��Ai�����ĵ㣬LinkBi��ʾ��Bi�����ĵ�
int LinkA[SIZE],  LinkB[SIZE];
//�����������
bool FlagA[SIZE], FlagB[SIZE];
int Pre[SIZE];

inline void initGraph(int n){
    for(int i=1;i<=n;++i)fill(Graph[i],Graph[i]+n+1,NEG);
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


int getInt(){
    int sgn = 1;
    char ch = getchar();
    while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
    if ( '-' == ch ) {sgn = 0;ch=getchar();}

    int ret = (int)(ch-'0');
    while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
    return sgn ? ret : -ret;
}

int N,M,E;
bool read(){
    if ( 1 != scanf("%d",&N) ) return false;
    M = getInt();
    E = getInt();

    initGraph(M);

    int a,b,w;
    for(int i=0;i<E;++i){
        a = getInt() + 1;
        b = getInt() + 1;
        w = getInt();
        if ( w >= 0 ) Graph[a][b] = w;
    }

    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        printf("Case %d: ",kase);

        if ( M < N ){
            puts("-1");
            continue;
        }

        weight_t ans = KM(M);

        //����Ƿ�ÿ���˶��з���ķ���
        bool flag = true;
        for(int i=1;i<=N;++i)if(NEG==Graph[i][LinkA[i]]){
            flag = false;
            break;
        }

        if ( flag ) printf("%d\n",ans - ( M - N ) * NEG);
        else puts("-1");
    }
    return 0;
}