/**
 * ����N��22���ڣ���ÿ�����ͿRGB������ɫ
 * �ٸ���M��������a c1 b c2����ʾa��Ϳc1b��Ϳc2�ǽ�ֹ��
 * �ʺϷ���Ϳɫ�����ж��ٸ�
 * ֱ��������Ȼ��3^22�����С���Ҫ��֦
 * ���й������������飬������֮�����˷�����
 * ��һ�����ڲ�����һ�����ѡ���ÿһ��
 * ���R�������������BҲ���������������ֻ��Ҫ����һ�μ���
 * ʵ���Ͼ���˵���ĳ��ĳ����ɫ�������µĽ���Ϳ���ֻ��һ��
 * ��ǰ�������ֻ��11���ܹ�ÿ�ζ��ں�������µ���ɫ��
 * ���������֦�Ժ���3^11��
 * �����֦�쳣ǿ��ʵ���϶����÷��飬ֱ�����Ѿ�����
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char getChar(){
	char ch = __hv007();
	while(ch != 'R' && ch != 'G' && ch != 'B') ch = __hv007();
	return ch;
}

int Father[25];
void init(int n){for(int i=0;i<n;++i)Father[i]=i;}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x, int y){Father[find(y)] = find(x);}

typedef long long llt;
typedef __int128_t bitt;
typedef vector<int> vi;
bitt const ONE = 1;

int S2I[256] = {0};
int TT[23][3]; // TTij��ʾ��i����ɫj��Ӧ�ı��
bitt BB[23][3]; // ��ʾ�ڸ���ɫj����Ӧ��λ������1ULL<<TTij
vector<bitt> G[70];
int Has[30] = {0};
int Flag[30] = {0};

int N, M;
vi Vec[33];
vi IdxVec;

vi * pVec;
int Sz; 

llt dfs(int idx, bitt forbidden){
	if(idx == Sz){
		return 1;
	}

    llt ans = 0;
	int cnt = 0;
	int cur = pVec->at(idx); // ��ǰ��
	/// ������ɫ
	for(int c=0;c<3;++c){
        if(BB[cur][c] & forbidden) continue;

		/// �鿴Ϳ�ϴ���ɫ�Ľ���
		bitt nf = forbidden;
		for(const auto &b: G[TT[cur][c]]){
            nf |= b;
		}
		if(nf == forbidden) ++cnt;
		else ans += dfs(idx+1, nf);
	}
	if(cnt) ans += cnt * dfs(idx+1, forbidden);
	return ans;
}

llt proc(int id){
    pVec = Vec + id;
	Sz = pVec->size();
	return dfs(0, 0);
}

llt proc(){
    llt ans = 1LL;
	for(int i=0;i<N;++i)if(0==Has[i]) ans *= 3;
	if(0 == M) return ans;

    for(int i=0;i<N;++i)if(Has[i])Vec[find(i)].push_back(i);
	for(int i=0;i<N;++i)if(!Vec[i].empty())IdxVec.push_back(i);

    for(auto i: IdxVec){
		llt tmp = proc(i);
		ans *= tmp;
		if(0 == ans) break;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    S2I['G'] = 1; S2I['B'] = 2;
    N = getInt(); M = getInt();
	init(N);
    for(int i=0;i<22;++i)for(int j=0;j<3;++j){
		BB[i][j] = (ONE << (TT[i][j] = i + j * N));
	} 	
	for(int a,c1,b,c2,i=0;i<M;++i){
		a = getInt()-1; c1 = S2I[getChar()];
		b = getInt()-1; c2 = S2I[getChar()];
		G[TT[a][c1]].push_back(BB[b][c2]);
		// G[TT[b][c2]].push_back(TT[a][c1]);
		Has[a] = Has[b] = 1;
		unite(a, b);
	}
	cout<<proc()<<endl;
    return 0;
}
