/**
   ���������εĵ�ͼ������(x,y,z)
   �����Ϊ3�ı����ĵ��Ϊ����Դ����������10%
   �ܹ����������εĵ��Ϊa����
   ����Դ���м䣬���߸���һ�����Ϊb����
   ����Ҫ����һЩ�㣬ʹ�ò����ڹ�����������������
   ע�⵽����ذ��������㣬��������Ϊ���ģ�����Χ6���Ϊ2��
   ���鲻��ͬʱȡ��
   ��ģ3��Ϊ0/1/2���飬����Ժ�S����1����0����2����T��
   �����ܳ�������������γɹ����ֵ
   ��������ֵ��ȥ���ֵ������ȥ�������Ժ�����ֵ
   ע����һ���ĵ����
*/
#include <bits/stdc++.h>
using namespace std;
typedef int weight_t;

int const SIZE_OF_VERTICES = 100010;//���������ֵ
int const SIZE_OF_EDGES = 100010<<2;//���������ֵ
weight_t const INF = 0x3f3f3f3f;

struct edge_t{
    int to;
    weight_t cap;//����
    weight_t flow;//����
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
inline void mkEdge(int a,int b,weight_t w){
    Edge[ECnt].to = b;
    Edge[ECnt].cap = w;
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].cap = 0;//����ͼ�ķ����Ϊ0������ͼ�ķ����ͬ�����
    Edge[ECnt].flow = 0;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int __D[SIZE_OF_VERTICES];//Di��ʾi����ľ���
int __Cnt[SIZE_OF_VERTICES];//Cnti��ʾ����Ϊi�Ķ���ĸ���
int Queue[SIZE_OF_VERTICES];//��������

//����BFS���������㵽��ľ��룬tΪ�㣬nΪ��������
void bfs(int t,int n){
    fill(__D,__D+n+1,-1);
    fill(__Cnt,__Cnt+n+1,0);

    int u,v, head = 0, tail = 0;
    __Cnt[ __D[ Queue[tail++]=t ] = 0 ] = 1;

    while(head != tail){
        for(int p = Vertex[ u = Queue[head++] ]; p ; p = Edge[p].next){
            if ( -1 == __D[ v = Edge[p].to ] ){
                ++ __Cnt[ __D[ Queue[tail++]=v ] = __D[u] + 1 ];
            }
        }
    }
}

int Cur[SIZE_OF_VERTICES];//��ǰ��
int Stack[SIZE_OF_VERTICES];//����ջ

//Improved shortest argument path algorithm
//sΪԴ��tΪ�㣬nΪ�������
weight_t isap(int s,int t,int n){
    bfs(t,n);
    copy(Vertex,Vertex+n+1,Cur);

    weight_t ans = 0;
    int u = s, top = 0;

    while(__D[s] < n){
        if(u == t){//�ҵ�һ������·
            int inser;
            weight_t wtmp,flow = INF;
            for(int i=0;i<top;++i)if( flow > ( wtmp = Edge[Stack[i]].cap - Edge[Stack[i]].flow ) ){
                flow = wtmp, inser = i;
            }
            for(int i=0;i<top;++i){
                Edge[Stack[i]].flow += flow;  //�����
                Edge[Stack[i]^1].flow -= flow;//�����
            }
            ans += flow;
            top = inser;
            u = Edge[Stack[top]^1].to;
            continue;
        }

        //���ҿ��л�
        int v, ava = 0;
        for(int p=Cur[u];p;p=Edge[p].next){
            if(Edge[p].cap - Edge[p].flow && __D[ v = Edge[p].to ] + 1 == __D[u]){
                Cur[u] = ava = p;
                break;
            }
        }

        if(ava){//�ҵ����л��Ժ��ƽ�
            Stack[top++] = Cur[u];
            u = v;
            continue;
        }

        //�Ҳ������л�������
        int tmpd = n;
        for(int p=Vertex[u];p;p=Edge[p].next)
        if( Edge[p].cap - Edge[p].flow && __D[Edge[p].to] < tmpd ){
            tmpd = __D[Edge[p].to];
            Cur[u] = p;
        }
        --__Cnt[__D[u]];

        if(!__Cnt[__D[u]])return ans;

        ++__Cnt[ __D[u] = tmpd + 1 ];

        if(u != s) u = Edge[Stack[--top]^1].to;
    }

    return ans;
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

map<pair<int,int>,int> Map;
map<pair<int,int>,int>::iterator It;
int W[51000];
int main(){
    //freopen("1.txt","r",stdin);
    int x,y,z,n = getInt();
    int cnt = 0;
    for(int i=1;i<=n;++i){
        x = getInt();
        y = getInt();
        z = getInt();
        x -= z, y -= z;
        if(Map.end()!=(It=Map.find(make_pair(x,y)))){
            W[It->second] += getInt();
        }else{
            Map.insert(It,make_pair(make_pair(x,y),++cnt));
            W[cnt] = getInt();
        }
    }
    n = cnt;
    int vn = n + n + 2;
    int s = vn - 1, t = vn;
    initGraph(vn);
    //��ÿһ����Դ��
    int sum = 0;
    for(map<pair<int,int>,int>::const_iterator it=Map.begin();it!=Map.end();++it){
        x = it->first.first;
        y = it->first.second;
        int index = it->second;
        int mod = ((x+y)%3+3)%3;
        if(0==mod){
            sum += W[index]*11;
            mkEdge(index,index+n,W[index]*11);
            if((It=Map.find(make_pair(x+1,y)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x,y+1)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x-1,y-1)))!=Map.end()){
                mkEdge(It->second+n,index,INF);
            }
            if((It=Map.find(make_pair(x-1,y)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
            if((It=Map.find(make_pair(x,y-1)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
            if((It=Map.find(make_pair(x+1,y+1)))!=Map.end()){
                mkEdge(index+n,It->second,INF);
            }
        }else if(1==mod){
            sum += W[index]*10;
            mkEdge(index,index+n,W[index]*10);
            mkEdge(s,index,INF);
        }else if(2==mod){
            sum += W[index]*10;
            mkEdge(index,index+n,W[index]*10);
            mkEdge(index+n,t,INF);
        }else{
            throw runtime_error("XXX");
        }
    }
    printf("%.1f\n",(sum-isap(s,t,vn))/10.0);
    return 0;
}
