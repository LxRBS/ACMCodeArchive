/**
 * N*M�ķ���ͼ�����е�ש����שչ������2*2�ģ�����Ŀǰ���ڵ�����1*2����2*1��
 * �ô�д��ĸ��ʾ�ĵ�שֻ�����һ�������չ��
 * ��Сд��ĸ��ʾ�ĵ�שֻ�������������չ��
 * �������չ�����ٿ��ש������������
 * �����Խ����񽻲�Ⱦ�ɺڰ���ɫ�����ש��չ�����ֱ�Ȼ����һ��һ�ף���˿���������ͼ���ƥ��
 * �յ���Ϊ����ͼ�Ķ��㣬��Ӧ���ǵĵ�ש��Ϊ��
 * ����ƥ��󣬲鿴��Ӧ�߼��ɵõ�����
 * �������1000*1000
 * Ϊ��ֹTLE��ÿ��ֻ�ѹ����Ŀյ��ש���ó�����ͼ��Ȼ����ƥ��
 * �������������һ��ͼ���ƺ�Ҳ���ᳬʱ?
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 110;
int const SZ = 110;
#else
int const SZ = 1010;
int const SIZE = 1005050;
#endif

template<typename T>
string value2string(T t){
	stringstream ss;
	ss<<t;
	return ss.str();
}

//just as its names
int const SIZE_OF_VERTICES = SIZE;
int const SIZE_OF_EDGES = SIZE;
int const INF = 0x3F3F3F3F;

struct edge_t{
	int from,to;
	int p;
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

//�����
inline void mkEdge(int a,int b, int pp){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].p = pp;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

/// LinkAi is the matched edge of Ai 
/// LinkBi is the matched edge of Bi
/// so LinkB[Edge[LinkA[i]].from] = Ai  
/// and LinkA[Edge[LinkB[i]].to]] = Bi
int LinkA[SIZE_OF_VERTICES];
int LinkB[SIZE_OF_VERTICES];

int DA[SIZE_OF_VERTICES],DB[SIZE_OF_VERTICES];//A���ֵľ��룬B���ֵľ���
int Q[SIZE_OF_VERTICES];//��������
int _Dis;
bool bfs(int na,int nb){
    fill(DA,DA+na+1,0);
    fill(DB,DB+nb+1,0);

    int *head = Q, *tail = Q;
    for(int i=1;i<=na;++i) if ( !LinkA[i] ) *tail++ = i;//���

    _Dis = INF;
    int u,v;
    while( head < tail ){
        if ( DA[u = *head++] > _Dis ) continue;

        for(int p=Vertex[u];p;p=Edge[p].next){
            if ( 0 == DB[ v = Edge[p].to ] ){
                DB[v] = DA[u] + 1;
                if ( LinkB[v] ) DA[ *tail++ = Edge[LinkB[v]].from ] = DB[v] + 1;
                else _Dis = DB[v];
            }
        }
    }
    return _Dis < INF;
}

bool _Flag[SIZE_OF_VERTICES];//�����������
bool dfs(int u){
    int v;
    for(int p=Vertex[u];p;p=Edge[p].next){
        if ( !_Flag[v=Edge[p].to] && DB[v] == DA[u] + 1 ){
            _Flag[v] = true;
            if ( !LinkB[v] || ( DB[v] != _Dis && dfs(Edge[LinkB[v]].from) ) ){
				LinkA[Edge[LinkB[v] = p].from] = p;
                return true;
            }
        }
    }
    return false;
}

//na��A��������nb��B������
int HopcroftKarp(int na,int nb){
	fill(LinkA,LinkA+na+1,0);
	fill(LinkB,LinkB+nb+1,0);

    int ret = 0;
    while( bfs(na,nb) ){
        fill(_Flag,_Flag+nb+1,false);
        for(int i=1;i<=na;++i){
            if ( !LinkA[i] ) ret += dfs(i);
        }
    }
    return ret;
}

typedef pair<int, int> pii;
int N, M;
char A[SZ][SZ];
bool B[SZ][SZ];
bool isUsed[SZ][SZ];


inline int id(int r, int c){return r*M+c;}

int const DR[][10] = {
    {-1, -1, -1, -1, 0, 0, +1, +1, +1, +1},
	{-1, -1, -1, 0, 0, +1, +1, +2, +2, +2}
};
int const DC[][10] = {
    {-1, 0, +1, +2, -1, +2, -1, 0, +1, +2},
	{-1, 0, +1, -1, +1, -1, +1, -1, 0, +1}
};

/// (r,c)λ����Χû�д������ש��
void f(vector<pii> &vec, int k, int r, int c){
    vec.clear();
	for(int dr,dc,i=0;i<10;++i){
        dr = r + DR[k][i];
		dc = c + DC[k][i];
		if(0<=dr&&dr<N&&0<=dc&&dc<M&&isalpha(A[dr][dc])&&!isUsed[dr][dc]){
			vec.emplace_back(dr, dc);
		}
	}
}

/// ����ש��λ�ã��õ�չ�����Լ�չ���Ŀյ����Χש��
pii f(const pii &p, vector<pii>&vec){
	int r = p.first / M, c = p.first % M;
	if(1 == p.second - p.first){		
        if(isupper(A[r][c])){ // ��
            if(r != N-1 && '.' == A[r+1][c] && '.' == A[r+1][c+1]){
				f(vec, 0, r+1, c);
                return {id(r+1, c), id(r+1, c+1)};
			}else{
				return {-1, -1};
			}
		}else if(islower(A[r][c])){ // ��
            if(r != 0 && '.' == A[r-1][c] && '.' == A[r-1][c+1]){
				f(vec, 0, r-1, c);
                return {id(r-1, c), id(r-1, c+1)};
			}else{
				return {-1, -1};
			}
		}else{
			throw runtime_error("da xiao");
		}
	}else if(M == p.second - p.first){
        if(isupper(A[r][c])){ // ��
            if(c != M - 1 && '.' == A[r][c+1] && '.' == A[r+1][c+1]){
				f(vec, 1, r, c+1);
				return {id(r, c+1), id(r+1, c+1)};
			}else{
				return {-1, -1};
			}
		}else if(islower(A[r][c])){ // ��
            if(c != 0 && '.' == A[r][c-1] && '.' == A[r+1][c-1]){
				f(vec, 1, r, c-1);
                return {id(r, c-1), id(r+1, c-1)};
			}else{
				return {-1, -1};
			}
		}else{
			throw runtime_error("da xiao");
		}
	}else{
		throw runtime_error("get");
	}
}



pii Que[SIZE];
map<int, int> MapA, MapB;
int DianID2Pos[SIZE];

inline int biid(int x, map<int,int>&m){
	auto it = m.find(x);
	if(it == m.end()){
		it = m.insert(it, {x, 1+m.size()});
		if(&MapA == &m){
			DianID2Pos[it->second] = x;
		}		
		if(m.size() > SIZE) printf("%d\n", m.size());
	}
	return it->second;
}

char FF[SZ][SZ];
int Ans = 0;

/// �������id�Լ�ѡ�е�ƥ��ߣ�ȷ��չ����ש��λ���Լ���д����
int f(vector<pii>& vec, int id, int edge){
	if(0 == edge) return -1;
    vec.clear();
	/// ���ȸ���id��ȡԭʼ���
	int origin = DianID2Pos[id];
	/// �ٸ���ԭʼ��Ż�þ���λ��
	int r = origin / M, c = origin % M;
    if(A[r][c] != '.') return -1;

	/// ��ȡ��ש��λ��
	auto pp = Que[Edge[edge].p];
	int zr = pp.first / M, zc = pp.first % M;
	int mr = 1E5, mc = 1E5;
    /// ��˳���Ȱ�ש��λ�÷Ž�ȥ�ٷŵ��λ��
	if(A[zr][zc] == A[zr][zc+1]){
		assert(r == zr + 1 || r == zr - 1);
		vec.emplace_back(zr, zc);
		vec.emplace_back(zr, zc+1);
		vec.emplace_back(r, c);
		vec.emplace_back(r, zc+zc+1-c);
		mr = min(zr, r); mc = zc;
	}else if(A[zr][zc] == A[zr+1][zc]){
		assert(c == zc + 1 || c == zc - 1);
		vec.emplace_back(zr, zc);
		vec.emplace_back(zr+1, zc);
		vec.emplace_back(r, c);
		vec.emplace_back(zr+zr+1-r, c);
		mc = min(zc, c); mr = zr;
	}else{
		throw runtime_error("XXXX");
	}
    
	/// �ж�һ��Ӧ�����ĸ���
	static int const dr[] = {-1, -1, 0, +1, +2, +2, +1, 0};
	static int const dc[] = {0, +1, +2, +2, +1, 0, -1, -1};
	int cnt[10] = {0};
	for(int nr,nc,i=0;i<8;++i){
        nr = mr + dr[i];
		nc = mc + dc[i];
		if(0<=nr&&nr<N&&0<=nc&&nc<M&&isdigit(FF[nr][nc])){
			++cnt[FF[nr][nc]-'0'];
		}
	}
    vector<int> candiate;
	for(int i=0;i<=9;++i)if(0==cnt[i])candiate.push_back(i);
	int t = rand() % candiate.size();
	return candiate[t];
}

void proc(int row, int col){
	static int va = 0;	
	MapA.clear(); MapB.clear();
    int head = 1, tail = 1;
	if(A[row][col] == A[row][col+1]){
		isUsed[row][col] = isUsed[row][col+1] = true;
		Que[tail++] = {id(row, col), id(row, col+1)};
	}else if(A[row][col] == A[row+1][col]){
		isUsed[row][col] = isUsed[row+1][col] = true;
		Que[tail++] = {id(row, col), id(row+1, col)};
	}else{
		throw runtime_error("proc");
	}
	
	initGraph(va);
    while(head != tail){
		auto h = Que[head++];
		vector<pii> vec;
        auto t = f(h, vec);
		if(-1 == t.first) continue;
		if(B[t.first/M][t.first%M]){
			mkEdge(biid(t.first, MapA), biid(t.second, MapB), head-1);
		}else if(B[t.second/M][t.second%M]){
			mkEdge(biid(t.second, MapA), biid(t.first, MapB), head-1);
		}else{
			throw runtime_error("t = {"+value2string(t.first)+", "+value2string(t.second)+"}");
		}
        

		/// �鿴�յ����Χ
		for(const auto &p: vec){
			int r = p.first, c = p.second;
			if(isUsed[r][c]) continue;
			if(A[r][c] == A[r][c+1]){
				isUsed[r][c] = isUsed[r][c+1] = true;
		        Que[tail++] = {id(r, c), id(r, c+1)};
			}else if(A[r][c] == A[r+1][c]){
				isUsed[r][c] = isUsed[r+1][c] = true;
				Que[tail++] = {id(r, c), id(r+1, c)};
			}
		}
	}
    va = MapA.size();
	int vb = MapB.size();
	// if(1000==N&&1000==M&&'W'==A[0][0]&&'W'==A[0][1])printf("%d\n", va);
	if(va > SIZE){
		throw runtime_error("SIZE is too small: "+value2string(va));
	}
	int n = HopcroftKarp(va, vb);
	Ans += n;

	/// ȷ�����巽��
    for(int i=1;i<=va;++i){
		vector<pii> vec;
		int x = f(vec, i, LinkA[i]);
		for(const auto &p: vec){
			FF[p.first][p.second] = '0' + x;
		}
	}
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d%d", &N, &M);
	int sn = 0;
	for(int i=0;i<N;++i){
		scanf("%s", A[i]);
		copy(A[i], A[i]+M, FF[i]);
		for(int j=0;j<M;j+=2){
			B[i][j] = sn;
			B[i][j+1] = sn ^ 1;
		}
		sn ^= 1;
	}
	for(int i=0;i<N;++i)for(int j=0;j<M;++j){
		if(isalpha(A[i][j]) && !isUsed[i][j]){
			proc(i, j);
		}
	}
	for(int i=0;i<N;++i)for(int j=0;j<M;++j)if(isalpha(FF[i][j])){
		if(A[i][j] == A[i][j+1]){
            static int const dr[] = {-1, -1, 0, +1, +1, 0};
			static int const dc[] = {0, +1, +2, +1, 0, -1};
			int cnt[10] = {0};
			for(int nr,nc,k=0;k<6;++k){
                nr = i + dr[k];
				nc = j + dc[k];
				if(0<=nr&&nr<N&&0<=nc&&nc<M&&isdigit(FF[nr][nc])){
                    ++cnt[FF[nr][nc] - '0'];
				}
			}
			vector<int> candi;
			for(int k=0;k<10;++k)if(0==cnt[k])candi.push_back(k);
			int t = rand()%candi.size();
			FF[i][j] = FF[i][j+1] = '0' + candi[t];
			A[i][j+1] = '@';
		}else if(A[i][j] == A[i+1][j]){
            static int const dr[] = {-1, 0, +1, +2, +1, 0};
			static int const dc[] = {0, +1, +1, 0, -1, -1};
			int cnt[10] = {0};
			for(int nr,nc,k=0;k<6;++k){
                nr = i + dr[k];
				nc = j + dc[k];
				if(0<=nr&&nr<N&&0<=nc&&nc<M&&isdigit(FF[nr][nc])){
                    ++cnt[FF[nr][nc] - '0'];
				}
			}
			vector<int> candi;
			for(int k=0;k<10;++k)if(0==cnt[k])candi.push_back(k);
			int t = rand()%candi.size();
			FF[i][j] = FF[i+1][j] = '0' + candi[t];  
			A[i+1][j] = '@';  
		}else{
			throw runtime_error("i = "+value2string(i)+", j = "+value2string(j));
		}
	}
	printf("%d\n", Ans);
    for(int i=0;i<N;++i)puts(FF[i]);
	return 0;
}
