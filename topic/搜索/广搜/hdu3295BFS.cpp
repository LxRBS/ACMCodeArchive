//初始地图可能全为零
 
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef vector<vector<int> > vvi;
FILE* fp = fopen("1.txt","w");
int const DI[] = {-1,1,0,0};
int const DJ[] = {0,0,-1,1};
inline bool isValid(vector<vector<int> >const&v,unsigned idx,unsigned jdx){
	return 0 <= idx && idx < v.size() && 0 <= jdx && jdx < v[idx].size();
}

int N,M;
vector<vector<int> > A;//列向量, 起点在左下 

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	A.assign(M,vector<int>(N,0));
	for(int i=0;i<N;++i)for(int j=0;j<M;++j)scanf("%d",&A[j][N-i-1]);
	return true;
}

bool F[6][6];
void clear(vector<vector<int> >&v,int idx,int jdx){
	F[idx][jdx] = true;
	for(int i=0;i<4;++i){
		int di = idx + DI[i];
		int dj = jdx + DJ[i];
		if ( !isValid(v,di,dj) || F[di][dj] || v[idx][jdx] != v[di][dj] ) continue;
		clear(v,di,dj);
	}
	v[idx][jdx] = 0;
}
//处理一个列 
void move(vector<int>&v){
	vector<int>::iterator it = v.begin();
	while( it != v.end() ){
		if ( 0 == *it ) it = v.erase(it);
		else ++it;
	}
}
//处理所有列
void move(vector<vector<int> >&vv){
	//首先落下
	for(unsigned i=0;i<vv.size();++i){
		move(vv[i]);
	} 
	//然后右移
	vector<vector<int> >::iterator it = vv.begin();
	while( it != vv.end() ){
		if ( it->empty() ) it = vv.erase(it);
		else ++it;
	} 
} 
void disp(FILE*fp,vector<int> const&v){
	for(unsigned i=0;i<v.size();++i)fprintf(fp,"%d ",v[i]);
	fprintf(fp,"\n");
}
void disp(FILE*fp,vector<vector<int> >const&vv){
	for(unsigned i=0;i<vv.size();++i){
		disp(fp,vv[i]);
	}
	fprintf(fp,"\n");
}
bool is0(vvi const&v){
	for(unsigned i=0;i<v.size();++i)
	    for(unsigned j=0;j<v[i].size();++j)
	        if ( v[i][j] ) return false;
	return true;
}
struct _t{
	vector<vector<int> > v;
	int step;
	_t():step(0),v(){}
	_t(_t const&r):step(r.step),v(r.v){}
	_t(int a,vector<vector<int> >const& b):step(a),v(b){}
};
int bfs(){
	if ( is0(A) )  return 0;
	
	queue<_t> q;
	q.push(_t(0,A));
	
	while( !q.empty() ){
		_t u = q.front();
		q.pop();
		
		bool f[6][6] = {false};
		vector<vector<int> >& v = u.v;
		for(unsigned i=0;i<v.size();++i){
			for(unsigned j=0;j<v[i].size();++j){
				if ( f[i][j] || 0 == v[i][j] ) continue;
				
				//清零
				vector<vector<int> > tmpv(v);
				memset(F,0,sizeof(F));
				clear(tmpv,i,j);
				move(tmpv);
				if ( tmpv.empty() ) return u.step + 1;
				q.push(_t(u.step+1,tmpv));
				
				for(int x=0;x<N;++x)for(int y=0;y<M;++y)f[x][y] = f[x][y] || F[x][y];
			}
		}
	}
}
int main(){
    while( read() ) printf("%d\n",bfs());
	return 0;
}
