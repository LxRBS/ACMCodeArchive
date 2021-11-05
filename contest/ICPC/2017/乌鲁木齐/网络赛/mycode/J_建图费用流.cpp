/*
    ����ͼ��ͼ����3�������A/B/C
    Ҫ���ҵ�һ����A��C�ٵ�B�����·������û�е�ᱻ�ظ�����
    ��С���������
    ÿ������i��i'��
    ԭͼ��a��b��һ���߳���Ϊw���ȼ���a'��b��һ��������Ϊ1������Ϊw��
    ÿ��i��i'��һ��������Ϊ1����Ϊ0��
    ����һ������ԴS��S��A��һ���ߣ�����Ϊ1����Ϊ0��S��B��һ���ߣ�����Ϊ1����Ϊ0��
    ��󣬰�C��C'�ı���������Ϊ2������Ϊ0��
    ��һ����С�������������������Ϊ2������С����Ϊ�𰸡�
    �����޽⡣
    ��ͼ����ʹ���ֵ�������hash��Ŀ���ַ������Ȳ�����1000����ֻ����Сд��ĸ��
*/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 20010;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 52;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){
    for(int i=0;i<26;++i) L2I[i + 'a'] = i;//TODO
    for(int i=0;i<26;++i) L2I[i+'A'] = i + 26;
}

//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    return SCnt++;
}

int insertAndFind(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    return state;
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

typedef int weight_t;
int const SIZE_OF_VERTICES = 20010<<1;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int from,to;
    weight_t cap;//����
    weight_t cost;//����
    int next;
}Edge[SIZE_OF_EDGES];
int ECnt;

int Vertex[SIZE_OF_VERTICES];

//��ʼ��
inline void initGraph(int n){
    ECnt = 2;//ECnt��2��ʼ����ָ����0��ʾ���������^1����
    fill(Vertex,Vertex+n+1,0);
}

//���ɱ�
inline void mkEdge(int a,int b,weight_t capa,weight_t cost){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].cap = capa;
    Edge[ECnt].cost = cost;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].from = b;
    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;
    Edge[ECnt].cost = -cost;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

//s��ʾԴ��vnΪ��������������Ϊ��������
void spfa(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);
    fill(pre,pre+vn+1,0);

    queue<int> q;
    q.push(s);

    d[s] = 0;
    flag[s] = true;

    int u,v;
    weight_t tmp;
    while( !q.empty() ){
        flag[ u = q.front() ] = false;
        q.pop();

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( Edge[p].cap > 0 && ( tmp = d[u] + Edge[p].cost ) < d[ v=Edge[p].to ] ){
                d[v] = tmp;pre[v] = p;
                if ( !flag[v] ) q.push(v), flag[v] = true;
            }
        }
    }
}

//��С�����������sΪԴ��tΪ�㣬vnΪ�ܵ���
//����Ϊ��������
pair<weight_t,weight_t> mcmf(int s,int t,int vn,weight_t d[],int pre[],bool flag[]){
    weight_t miniCost = 0;
    weight_t maxFlow = 0;
    while(1){
        spfa(s,vn,d,pre,flag);
        //˵���Ҳ�������·
        if ( INF == d[t] ) break;

        //�ҳ�������·�ϵĿ�����
        weight_t curFlow = INF;
        for(int p=pre[t];p;p=pre[Edge[p].from])if(curFlow>Edge[p].cap)curFlow = Edge[p].cap;

        //�䶯����
        for(int p=pre[t];p;p=pre[Edge[p].from]){
            Edge[p].cap -= curFlow;
            Edge[p^1].cap += curFlow;
        }

        //���������ͷ���
        miniCost += d[t] * curFlow;
        maxFlow += curFlow;
    }

    return make_pair(maxFlow,miniCost);
}


int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

char const Dalian[]="Dalian";
char const Xian[]="Xian";
char const Shanghai[]="Shanghai";

char City[2][1001];
int M,N;
int A,B,C;
void read(){
    M = getUnsigned();

    initTrie();
    initGraph(40000+1);

    N = 0;
    int a,b,w;
    int state;
    for(int i=0;i<M;++i){
        scanf("%s%s%d",City[0],City[1],&w);

        state = insertAndFind(City[0]);
        if ( !Flag[state] ) Flag[state] = ++N,++N;
        a = Flag[state];

        state = insertAndFind(City[1]);
        if ( !Flag[state] ) Flag[state] = ++N,++N;
        b = Flag[state];

        mkEdge(a+1,b,1,w);
        mkEdge(b+1,a,1,w);

        if ( 0==strcmp(City[0],Dalian) ) A = a;
        else if ( 0==strcmp(City[0],Xian) ) B = a;
        else if ( 0==strcmp(City[0],Shanghai) ) C = a;

        if ( 0==strcmp(City[1],Dalian) ) A = b;
        else if ( 0==strcmp(City[1],Xian) ) B = b;
        else if ( 0==strcmp(City[1],Shanghai) ) C = b;
    }

    for(int i=1;i<=N+N;i+=2) mkEdge(i,i+1,1,0);
    mkEdge(C,C+1,1,0);

    //����Դ
    mkEdge(N+N+1,A,1,0);
    mkEdge(N+N+1,B,1,0);
}

int D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool F[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();
    int nofkase = getUnsigned();
    while(nofkase--){
        read();
        pair<int,int> ans = mcmf(N+N+1,C+1,N+N+1,D,Pre,F);
        if ( 2 == ans.first ) printf("%d\n",ans.second);
        else printf("-1\n");
    }
    return 0;
}

