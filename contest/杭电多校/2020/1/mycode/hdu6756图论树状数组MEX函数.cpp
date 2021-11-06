/**
   ����һ������ͼ�����������
   1: ��u�ĵ�Ȩ��Ϊx
   2: ��ѯu��mex����ֵ
   �����ͱ�����Ϊ10��
   ���ڵ㰴�ն�����Ϊ��ڵ��С�ڵ㣬Ȼ��ֱ���в���
   ��ڵ��1������forÿһ�����ھӣ��޸�����״����
   С�ڵ��1������forÿһ�����ھӣ��޸�����״����
   ��ڵ��2��������״����ͳ�ƽ��
   С�ڵ��2����������
   ע����״����ֻ���治����������ֵ
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 100010;
int const SIZE_OF_EDGES = 100010<<1;

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

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int W[SIZE_OF_VERTICES];
int Deg[SIZE_OF_VERTICES];
vector<int> C[SIZE_OF_VERTICES];
vector<int> G[SIZE_OF_VERTICES];
vector<int> T[SIZE_OF_VERTICES];
int const LIMIT = 300;

//����x�Ķ�����λ�����λ1�������ֵ
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//��ѯC[idx]�е�ǰx��֮��
int query(int x,int idx){
    vector<int>const&v=C[idx];
    int s = 0;
    while(x>0) s+=v[x],x-=lowbit(x);
    return s;
}
//��C[idx]�ϵĵ�idx���delta
void modify(int x,int delta,int idx){
    vector<int>&v=C[idx];
    int n = v.size()-1;
    while(x<=n)v[x]+=delta,x+=lowbit(x);
}

//��ѯu��mex����ֵ
int query(int u){
    int deg = Deg[u];
    if(deg<LIMIT){//С�ڵ㣬����
        bool flag[deg+1] = {false};
        for(int tmp,p=Vertex[u];p;p=Edge[p].next){
            if((tmp=W[Edge[p].to])<=deg){
                flag[tmp] = true;
            }
        }
        int k = 1;
        while(k<=deg && flag[k]) ++k;
        return k;
    }

    //ʹ����״����
    vector<int> const&v = C[u];
    int mid, left = 1, right = v.size()-1;
    do{//����������������������x��ʹ��x-sum(x)>=1
        mid = (left+right)>>1;
        if(mid-query(mid,u)>=1) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);

    return left;
}

//��v��Ȩֵ��origin�޸ĳ�newValue
//��֤uv�ұߣ���u�Ǵ�ڵ�
//�ò�����Ҫ�޸�u����״����
void change(int u,int v,int origin,int newValue){
    if(origin){//originΪ0��ʾ�ǳ�ʼ����������Ϊ0���Ǻ������޸Ĳ���
        if(origin<=Deg[u]){
            if(0==--T[u][origin]){
                modify(origin,-1,u);
            }
        }
    }
    if(newValue<=Deg[u]){
        if(1==++T[u][newValue]){
            modify(newValue,+1,u);
        }
    }
}
//��u�ڵ��Ȩֵ�޸�ΪnewValue
void change(int u,int newValue){
    vector<int>const& v = G[u];
    //forÿһ�����ھӣ��޸�����״����
    for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
        change(*it,u,W[u],newValue);
    }
    W[u] = newValue;
}
int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int a,b,n,m,nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        initGraph(n = getUnsigned());
        m = getUnsigned();

        fill(Deg,Deg+n+1,0);
        for(int i=1;i<=n;++i){
            W[i]=getUnsigned() + 1;
            C[i].clear();
            G[i].clear();
            T[i].clear();
        }
        for(int i=0;i<m;++i){
            ++Deg[a=getUnsigned()];
            ++Deg[b=getUnsigned()];
            mkEdge(a,b);
        }

        //ͳ�ƴ��ھ�
        for(int i=1;i<=n;++i){
            for(int to,p=Vertex[i];p;p=Edge[p].next){
                if(Deg[to=Edge[p].to]>=LIMIT){
                    G[i].push_back(to);
                }
            }
        }

        //��ÿһ����ڵ㽨��״����
        for(int deg,i=1;i<=n;++i)if((deg=Deg[i])>=LIMIT){
            C[i].assign(deg+1,0);
            T[i].assign(deg+1,0);
            for(int p=Vertex[i];p;p=Edge[p].next){
                change(i,Edge[p].to,0,W[Edge[p].to]);
            }
        }

        int cmd,u,newValue,q = getUnsigned();
        for(int iq=1;iq<=q;++iq){
            switch(cmd=getUnsigned()){
            case 1:{
                u = getUnsigned();
                newValue = getUnsigned() + 1;
                change(u,newValue);
            }break;
            case 2:{
                u = getUnsigned();
                printf("%d\n",query(u)-1);
            }break;
            default:throw runtime_error("XXXXXX");
            }
        }
    }
    return 0;
}
