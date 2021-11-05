#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;

typedef vector<char> vc_t;
typedef vector<vc_t> vvc_t;
typedef pair<int,int> point_t;
typedef vector<point_t> vp_t;
typedef vector<vp_t> vvp_t;

void dispVVCT(vvc_t const&v,FILE*fp=stdout){
	for(unsigned i=0;i<v.size();++i){
		for(unsigned j=0;j<v[i].size();++j)fprintf(fp,"%c",v[i][j]);
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
}

struct trie_t{
	trie_t* son[3];//一共只有3个字母 
}Trie[3000000];
int toUsed = 0;

inline void init(){toUsed = 0;memset(Trie,0,sizeof(trie_t));}
inline trie_t* _newNode(){
	++toUsed;
    memset(Trie+toUsed,0,sizeof(trie_t));
    return Trie+toUsed;
}

//字典树内有则返回true，无返回false，并插入 
bool findAndInsert(vvc_t const&v){
	trie_t* loc = Trie;
	bool flag = true;

	for(unsigned i=0;i<v.size();++i)for(unsigned j=0;j<v[i].size();++j){
		char const& ch = v[i][j];
		int sn = ch - 'a';
		if ( !loc->son[sn] ){
			loc->son[sn] = _newNode();
			flag = false;
		}
		loc = loc -> son[sn];
	}
	return flag;
}

struct _t{
	int step;
	vvc_t v;//棋盘 
	int cur;//0表示白，1表示黑
    vvp_t pos;
	_t(int a=0,vvc_t const&b=vvc_t(),int c=0,vvp_t const&d=vvp_t())
	    :step(a),v(b),cur(c),pos(d){}
};

int const DR[] = {-1,-1,-1,0,1,1,1,0};
int const DC[] = {-1,0,1,1,1,0,-1,-1};

vvc_t S(4,vc_t(4)),T(4,vc_t(4));
vvp_t Pos(2);

FILE* fp = fopen("1.txt","w");

void read(){
    Pos[0].clear();Pos[1].clear();
	
	char a[5];
	for(unsigned i=0;i<S.size();++i){
		gets(a);
        for(unsigned j=0;j<S[i].size();++j){
        	char& ch = a[j];
			if ( '*' == ch ){
				ch = 'c';
			}else{
				if ( 'w' == ch ) ch = 'a';
				Pos[ch-'a'].push_back(point_t(i,j));
			}
			S[i][j] = ch;
	    }		
	}
	for(unsigned i=0;i<S.size();++i){
		gets(a);
        for(unsigned j=0;j<S[i].size();++j){
        	char& ch = a[j];
			if ( '*' == ch ){
				ch = 'c';
			}else{
				if ( 'w' == ch ) ch = 'a';
				Pos[ch-'a'].push_back(point_t(i,j));
			}
			T[i][j] = ch;
	    }		
	}	
}

bool isOK(vvc_t const&v){
	for(unsigned i=0;i<v.size();++i)for(unsigned j=0;j<v[i].size();++j){
		if ( v[i][j] != T[i][j] ) return false;
	}
	return true;
}

inline bool isValid(int r,int c,vvc_t const&v){
	return 0 <= r && r < 4 && 0 <= c && c < 4 && 'c' == v[r][c];
}

int bfs(){
    init();
		
	queue<_t> q;
	q.push(_t(0,S,0,Pos));	
	findAndInsert(S);

	while( !q.empty() ){
		_t u = q.front();
		q.pop();
		
		vp_t const& pos = u.pos[u.cur];
		//对每一个棋子 
		for(unsigned it=0;it<pos.size();++it){
			point_t const&p = pos[it];
			int r = p.first;
			int c = p.second;
			//找出八个可能的方向 
			for(int i=0;i<8;++i){
				int dr = r + DR[i];
				int dc = c + DC[i];
				if ( !isValid(dr,dc,u.v) ) continue;
				
				int k = 1;
				while( isValid(dr+k*DR[i],dc+k*DC[i],u.v) ) ++k;
				--k;
				if ( k > 0 ) dr += k * DR[i], dc += DC[i];
				//走棋
				_t nt(u);
				nt.v[r][c] = 'c';
				nt.v[dr][dc] = 'a' + u.cur;
				//dispVVCT(u.v,fp);dispVVCT(nt.v,fp);
				if ( isOK(nt.v) ) return u.step + 1;
				if ( findAndInsert(nt.v) ) continue;
				
				nt.pos[u.cur].erase(nt.pos[u.cur].begin()+it);
				nt.pos[u.cur].push_back(point_t(dr,dc));
				nt.cur = u.cur ^ 1;
				nt.step = u.step + 1;
				
				q.push(nt);				
			}
		}
	}
	
	return -1;
}

int main(){
	int kase;
	scanf("%d",&kase);
	char a[5];gets(a);
	while(kase--){
        read();
        if ( isOK(S) ) printf("0\n");
		else printf("%d\n",bfs());
	}
	return 0;
}

