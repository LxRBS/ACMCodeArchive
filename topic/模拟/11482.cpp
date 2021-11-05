#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 501
//并查集数组
int Father[SIZE];

//初始化
inline void init(int n){for(int i=1;i<=n;++i)Father[i]=i;}

//查找父节点
inline int find(int x){return Father[x]==x?x:Father[x]=find(Father[x]);}

//合并，无优化
inline void unite(int x,int y){Father[find(y)]=find(x);}

struct edge_t{
	int node;
	edge_t* next;
}Edge[2000];
int ECnt;

edge_t* Ver[501];
int Degree[501];

void mkEdge(int a,int b){
    Edge[ECnt].node = b;
    Edge[ECnt].next = Ver[a];
    Ver[a] = Edge + ECnt ++;

    Edge[ECnt].node = a;
    Edge[ECnt].next = Ver[b];
    Ver[b] = Edge + ECnt ++;

    ++Degree[a];
    ++Degree[b];
}

int N,M;
inline void init(){
	ECnt = 0;
	fill(Degree+1,Degree+N+1,0);
	fill(Ver+1,Ver+N+1,(edge_t*)0);
}

void read(){
    scanf("%d%d",&N,&M);
    init();init(N);
    for(int i=0;i<M;++i){
    	int a,b;
    	scanf("%d%d",&a,&b);
    	mkEdge(a,b);
    	unite(a,b);
    }
}

//中间全部由度为2的节点连接,s-s2-...-e
int calcPath(int s,int s2,int e){
	if ( s2 == e ) return 1;
	int ret = 1;
	while ( s2 != e ){
		int ss = 0;
        for(edge_t*p=Ver[s2];p;p=p->next)
        	ss += p->node;
        ss -= s;
        s = s2;
        s2 = ss;
        ++ret;
	}
    return ret;
}

int Ans;
struct _t{
	int digit;
	int degree;
}T[1000];

bool is1(){
	if ( M % 2 || N != M + 1 ) return false;
	return M / 2 - 1 >= 0;
}
bool is25(){
	if ( M % 5 || N != M + 1 ) return false;
	return M / 5 - 1 >= 0;
}
bool is7(){
	if ( M % 3 || N != M + 1 ) return false;
	return M / 3 - 1 >= 0;
}
bool is3(){
    if ( M % 5 || N != M + 1 ) return false;
    if ( M / 5 - 1 < 0 ) return false;

    //找到度为1和度为3的节点
    int s[4] = {0};
    int k = 0;
    for(int i=1;i<=N;++i){
    	if ( 1 == Degree[i] || 3 == Degree[i] ){
    		s[k++] = i;
    		if ( 4 == k ) break;
    	}
    }
    for(int i=0;i<3;++i){
    	if( 3 == Degree[s[i]] ){
    		swap(s[3],s[i]);
    		break;
    	}
    }

    int len[3];
    for(int i=0;i<3;++i){
    	len[i] = calcPath(s[i],Ver[s[i]]->node,s[3]);
    }

    swap(len[0],*min_element(len,len+3));

    return 2 * len[0] == len[1] && len[1] == len[2];
}

bool is4(){
    if ( M % 4 || N != M + 1 ) return false;
    int d = M / 4 - 1;
    if ( d < 0 ) return false;

    //找到度为1和度为3的节点
    int s[4] = {0};
    int k = 0;
    for(int i=1;i<=N;++i){
    	if ( 1 == Degree[i] || 3 == Degree[i] ){
    		s[k++] = i;
    		if ( 4 == k ) break;
    	}
    }
    for(int i=0;i<3;++i){
    	if( 3 == Degree[s[i]] ){
    		swap(s[3],s[i]);
    		break;
    	}
    }
    //计算度1到度3的距离
    int len[3];
    for(int i=0;i<3;++i){
    	len[i] = calcPath(s[i],Ver[s[i]]->node,s[3]);
    }

    swap(len[0],*max_element(len,len+3));
    return len[1] == len[2] && 2 * len[1] == len[0];
}
bool is69(){
    if ( N != M || N % 6 ) return false;
    int x = N / 6 - 1;

    //找到度为1的点与度为3的节点
    int s[2] = {0,0};
    int k = 0;
    for(int i=1;i<=N;++i){
    	if ( 1 == Degree[i] || 3 == Degree[i] ){
    		s[k++] = i;
    		if ( 2 == k ) break;
    	}
    }

    if ( 3 == Degree[s[0]] ) swap(s[0],s[1]);

    //计算到度为3的路径长度
    int s2 = Ver[s[0]]->node;
    return calcPath(s[0],s2,s[1]) == 2 * x + 2;
}
bool is8(){
	if ( M % 7 || M != N + 1 ) return false;
	int d1 = M / 7 - 1;
	int d2 = ( N - 6 ) / 7;
	if ( d1 != d2 || d1 < 0 ) return false;
    //找到度为3的2个点
	int s[2]={0,0};
	int k = 0;
	for(int i=1;i<=N;++i){
		if ( 3 == Degree[i] ){
			s[k++] = i;
			if ( 2 == k ) break;
		}
	}
	//检查路径长度，测试数据似乎不包含该检查
    int len[3]={0};
    k = 0;
    for(edge_t*p=Ver[s[0]];p;p=p->next){
    	len[k++] = calcPath(s[0],p->node,s[1]);
    }

    swap(len[0],*min_element(len,len+3));
    return len[1] == 3 * len[0] && len[2] == len[1];
}
void proc(){
	Ans = 0;

	//判连通
	for(int i=2;i<=N;++i){
        if ( find(1) != find(i) )
        	return;
	}

	//检查度数
	int cnt[4] = {0};
	for(int i=1;i<=N;++i){
		if ( Degree[i] > 3 || 0 == Degree[i] ){
			Ans = 0;
			return;
		}
		++cnt[Degree[i]];
	}

	if ( 0 == cnt[1] && 0 == cnt[3] ){//0
        if ( N == M && 0 == N % 6 ){
        	T[Ans].digit = 0;
        	T[Ans].degree = N / 6 - 1;
        	Ans = 1;
        }
        return;
	}

	if ( 0 == cnt[1] && 2 == cnt[3] ){//8
		if ( is8() ){
        	T[Ans].digit = 8;
        	T[Ans].degree = M / 7 - 1;
        	Ans = 1;
		}
        return;
	}

	if ( 1 == cnt[1] && 1 == cnt[3] ){//69
		if ( is69() ){
            T[0].digit = 6;
            T[1].digit = 9;
            T[0].degree = T[1].degree = N / 6 - 1;
            Ans = 2;
		}
        return;
	}

	if ( 3 == cnt[1] && 1 == cnt[3] ){//34
        if ( is3() ){
        	T[0].digit = 3;
        	T[0].degree = M / 5 - 1;
        	Ans = 1;
        }else if ( is4() ){
        	T[0].digit = 4;
        	T[0].degree = M / 4 - 1;
        	Ans = 1;
        }
		return;
	}

	if ( 2 == cnt[1] && 0 == cnt[3] ){//1257
		if ( is1() ){
			T[0].digit = 1;
			T[0].degree = M / 2 - 1;
			Ans = 1;
		}
		if ( is25() ){
			T[Ans].digit = 2;
			T[Ans+1].digit = 5;
			T[Ans].degree = T[Ans+1].degree = M / 5 - 1;
			Ans += 2;
		}
		if ( is7() ){
			T[Ans].digit = 7;
			T[Ans].degree = M / 3 - 1;
			++Ans;
		}
		return;
	}
}
int main() {
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
        read();
        proc();
        if ( kase != 1 )printf("\n");
        printf("Case %d: %d\n",kase,Ans);
        for(int i=0;i<Ans;++i){
            printf("%d %d\n",T[i].digit,T[i].degree);
        }
	}
	return 0;
}
