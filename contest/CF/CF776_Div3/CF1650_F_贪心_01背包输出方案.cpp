/**
 * 有N个任务，第i个任务的时限是Ai
 * 有M个操作，每个操作是(e, t, p)，意思是花t个时间可以将第e个任务的进度增加p
 * 当某个任务的进度大于等于100即视为完成
 * 问能否选择操作完成所有任务，如果能需要给出方案
 * 首先贪心，直接按照时限顺序完成任务即可，而且对指定的任务i，用最短时间完成即可
 * 求最短时间需要用到DP，时间数值比较大，所以要用进度作为代价，时间作为收益，做一个01背包
 * 总代价在200以内即可，背包有在100到199之间找收益最小的即可，并给出方案
 * DP方程：Div = min(D[i-1][v], D[i-1][v-cost]+gain)
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

#ifndef ONLINE_JUDGE
int const SIZE = 37;
#else
int const SIZE = 1E5+10;
#endif

typedef long long llt;
typedef tuple<int, int, int> pii;
typedef vector<pii> vpii;
llt const INF = 0x3F3F3F3FFFFFFFFF;

int N, M;
int A[SIZE];
vpii B[SIZE];
llt D[SIZE][200];
int G[SIZE][200];
vector<int> Ans;
int Now;

bool proc(int idx){
    const vpii &vec = B[idx];
	int n = vec.size();
	for(int i=0;i<n;++i) {
		fill(D[i], D[i]+200, -1);
		fill(G[i], G[i]+200, 0);
	}

    D[0][0] = 0; D[0][get<1>(vec.front())] = get<0>(vec.front());
	G[0][0] = 1; G[0][get<1>(vec.front())] = 2;

	for(int i=1;i<n;++i){
		int cost = get<1>(vec[i]);
		int gain = get<0>(vec[i]);
		for(int v=0;v<200;++v){
			if(-1 != D[i-1][v]){
				D[i][v] = D[i-1][v];
				G[i][v] = 1;
			}
			if(v>=cost && -1 != D[i-1][v-cost]){
				if(-1 == D[i][v] || D[i][v] > D[i-1][v-cost]+gain){
					G[i][v] = 2;
					D[i][v] = D[i-1][v-cost]+gain;
				}
			}

		}
	}

	/// �Ҵ�
	int k = -1;
	for(int i=100;i<=199;++i){
		if(-1 == D[n-1][i]) continue;
		if(-1 == k || D[n-1][k] > D[n-1][i]){
			k = i;
		}
	}
	/// ����ʱ��D[n-1][k]��ɵ�idx������
	if(Now + D[n-1][k] > A[idx]){
		return false;
	}
	Now += D[n-1][k];
	/// ��¼����
	for(int i=n-1;i>=0;--i){
		if(2 == G[i][k]){ // ѡ��i��
            Ans.push_back(get<2>(vec[i]));
			k -= get<1>(vec[i]);
		}else if(1 == G[i][k]){
            
		}else{
			throw runtime_error("XX");
		}
	}
	return true;
}

void proc(){
    for(int i=1;i<=N;++i){
		int total = 0;
		for(const auto &p: B[i]){
			if((total += get<1>(p)) >= 100){
				break;
			}
		}
		if(total < 100){
			return (void)puts("-1");
		}
	}

    Ans.clear();
	Now = 0;
	for(int i=1;i<=N;++i){
		if(!proc(i)){
			return (void)puts("-1");
		}
	}
	printf("%d\n", Ans.size());
	for(auto i: Ans)printf("%d ", i);
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
        N = getInt(); M = getInt();
		for(int i=1;i<=N;++i) B[i].clear();
		for(int i=1;i<=N;++i) A[i] = getInt();
        for(int e,t,p,i=0;i<M;++i){
			e = getInt(); t = getInt(); p = getInt();
			B[e].emplace_back(t, p, i+1);
		}
		proc();
	}
    return 0;
}
