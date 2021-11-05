#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

#define SIZE 100011

typedef map<string,int> msi;
typedef msi::iterator msit;
typedef pair<int,int> pii;
typedef map<pii,int> mpi;

//并查集
int Father[SIZE];
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}

//树
int Root;
bool isRoot[SIZE];
int Depth[SIZE];//深度
vector<int> Son[SIZE];//儿子

//字符串与编号的相互映射
string I2S[SIZE];
msi S2I;

//问题
vector<int> QNode[SIZE];//与每个节点相关的问题
pii QSn[SIZE];//按顺序的问题
mpi Lca;//最近公共祖先

bool Flag[SIZE];
void Tarjan(int u){
	Father[u] = u;
	Flag[u] = true;

	//对u的每一个儿子
	for(unsigned i=0;i<Son[u].size();++i){
		int& v = Son[u][i];
		Depth[v] = Depth[u] + 1;//额外操作
		Tarjan(v);
		Father[v] = u;
	}

	//对每一个跟u有关的问题
	for(unsigned i=0;i<QNode[u].size();++i){
		int& v = QNode[u][i];
		if ( Flag[v] ){
			int r = find(v);
			Lca.insert(make_pair(make_pair(u,v),r));
			Lca.insert(make_pair(make_pair(v,u),r));
		}
	}
}

//数据结构太多，初始化一定要完全
void initClear(int n,int m){
	S2I.clear();
	Lca.clear();
	for(int i=0;i<=n;++i){
		Son[i].clear();
		QNode[i].clear();
	}
	fill(isRoot,isRoot+n,true);
	fill(Depth,Depth+n,0);
	fill(Flag,Flag+n,false);//忘记初始化该数组导致WA很久
}

void disp(int n){
	cout<<Root<<endl<<endl;
	for(int i=0;i<n;++i){
		cout<<i<<' '<<I2S[i]<<endl;
		cout<<Depth[i]<<endl<<endl;
	}
}

int main(){
	int nofkase;
	cin>>nofkase;
	while(nofkase--){
		int n,m;
		cin>>n>>m;
        
		if ( 1 == n ){
			for(int i=0;i<m;++i){
				string a,b;
				cin>>a>>b;
				cout<<'0'<<endl;
			}
			continue;
		}

		initClear(n,m);

		//建树
		for(int i=0;i<n-1;++i){
			string a,b;
			cin>>a>>b;

			int ia,ib;
			msit it = S2I.find(a);
			if ( S2I.end() == it ){
				ia = S2I.size();
				I2S[ia] = a;
				S2I.insert(make_pair(a,ia));
			}else{
				ia = it->second;
			}

			it = S2I.find(b);
			if ( S2I.end() == it ){
				ib = S2I.size();
				I2S[ib] = b;
				S2I.insert(make_pair(b,ib));
			}else{
				ib = it->second;
			}

			//a是b的儿子
			Son[ib].push_back(ia);
			isRoot[ia] = false;
		}

		for(Root=0;Root<n;++Root)if(isRoot[Root])break;
		Depth[Root] = 0;

		//读取问题
		for(int i=0;i<m;++i){
			string a,b;
			cin>>a>>b;
			int ia,ib;
			if ( a == b ) ia = ib = n;
			else ia=S2I[a],ib=S2I[b];
			QSn[i].first = ia;
			QSn[i].second = ib;
			QNode[ia].push_back(ib);
			QNode[ib].push_back(ia);
		}

		Tarjan(Root);

		//disp(n);

		//答案
		for(int i=0;i<m;++i){
			int& ia = QSn[i].first;
			int& ib = QSn[i].second;
			if ( ia == ib ){
				cout<<'0'<<endl;
				continue;
			}
			int t = Lca[QSn[i]];
			int ret = Depth[ia]-Depth[t];
			
			if ( t == ia ){
				cout<<'1'<<endl;
			}else if( t == ib ){
				cout<<ret<<endl;
			}else{
				cout<<ret+1<<endl;
			}
		}
	}
	return 0;
}
