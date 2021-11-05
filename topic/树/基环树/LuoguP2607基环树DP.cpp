/**
   N���㣬ÿ������һ��Ȩֵ
   ÿ������һ������ĵ㣬�����������ĵ㲻��ͬʱѡ
   �����ѡ����ʹ�õ�Ȩ�����
   ����ÿ����ͨ�飬��Ȼ��һ������������
   ���ڻ��ϵ�����һ���ߣ���Ȼ�����㲻��ͬʱѡ��
   �˱߿�����Ϊ�����ڣ����ǿ�������������ֱ���������һ������DP
*/
#include<bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;

//just as its names
int const SIZE_OF_VERTICES = 1000100;
int const SIZE_OF_EDGES = 1000100<<1;

struct edge_t{
	int from,to;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

int N;
int Father[1000100];
vector<int> Graph[1000100];
llt W[1000100];
bool Flag[1000100];

//�һ������ػ��ϵ�һ��
int find_circle(int x){
    Flag[x] = true;
    return Flag[Father[x]]?x:find_circle(Father[x]);
}

//Di��ʾѡ��i�����ֵ��Fi��ʾ��ѡi�����ֵ
llt D[1000100], F[1000100];
int Root;

//����DP
void dp(int x){
    Flag[x] = true;
    D[x] = W[x];
    F[x] = 0LL;

    /*
    vector<int>const&vec=Graph[x];
    for(vector<int>::const_iterator it=vec.begin();it!=vec.end();++it){
        if(*it!=Root){
            dp(*it);
            D[x] += F[*it];
            F[x] += max(D[*it],F[*it]);
        }else{//���ﲻ���ظ�ѡ������һ��������󣬿���ֱ�ӴﵽЧ��
            D[*it] = -20000000000000LL;
        }
    }//*/
    for(int v,p=Vertex[x];p;p=Edge[p].next){
        if((v=Edge[p].to)!=Root){
            dp(v);
            D[x] += F[v];
            F[x] += max(D[v], F[v]);
        }else{
            D[v] = -20000000000000LL;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    initGraph(N = getUnsigned());
    for(int i=1;i<=N;++i){
        W[i] = getUnsigned();
        //Graph[Father[i] = getUnsigned()].push_back(i);
        mkEdge(Father[i] = getUnsigned(), i);
    }
    llt ans = 0LL;
    for(int i=1;i<=N;++i){
        if(Flag[i]) continue;
        Root = find_circle(i);
        dp(Root);
        llt tmp = max(D[Root],F[Root]);
        Root = Father[Root];
        dp(Root);
        ans += max(tmp, max(D[Root],F[Root]));
    }
    printf("%lld\n",ans);
    return 0;
}
