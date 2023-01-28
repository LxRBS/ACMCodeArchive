/**
 * 交互题，有一个长度为N，从0到N-1的排列，每一次询问i和j，会返回gcd(Ai, Aj)
 * 要求在2N次询问内，找到(x, y)，满足Ax或者Ay为0， 特别的 gcd(0, x) = x，对任意x
 * 每次拿出三个数a,b,c，询问3次,(a, b), (a, c), (b, c)
 * 假设(a, b)的答案最大，则a和b中可能有0，但c一定不是0，排除c。其他类似
 * 如果三个询问的结果一样，则3个数均排除。
 * 每次询问至少排除1个数，但也有可能是3个数。似乎可以证明一下
 * 总之2N次询问以后得到了结果。
 * 标程每次询问(a, b)和(a, c)
 * 如果结果相同，则a必然不是0，可以排除
 * 如果(a, b)大，则c不可能是0。可以排除
 * 因此标程每次询问可以排除1个。
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
int const SIZE = 13;
#else
int const SIZE = 2E5+10;
#endif

using llt = int;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int N;

map<int, map<int, int>> Map;

inline int ask(int a, int b){
	if(a > b) swap(a, b);
	auto it = Map.find(a);
	if(it != Map.end()){
		auto jt = it->second.find(b);
		if(jt != it->second.end()){
			return jt->second;
		}
	}
	printf("? %d %d\n", a, b);
	fflush(stdout);
	int tmp;
	scanf("%d", &tmp);
	return Map[a][b] = tmp;
}

inline int answer(int a, int b){
	printf("! %d %d\n", a, b);
	fflush(stdout);	
	int tmp;
	scanf("%d", &tmp);
	return tmp;	
}

void proc(int pos, const vi & src, vi & dst){
	int n = src.size();
	int m = 0;
	for(int i=0;i<n;++i){
		if(i==pos) continue;
		int tmp = ask(src[i], src[pos]);
		if(m < tmp){
			m = tmp;
			dst.assign(1, src[i]);
		}else if(m == tmp){
			dst.push_back(src[i]);
		}
	}
	return;
}

vi proc(int a, int b, int c){
	int tab = ask(a, b);
	int tbc = ask(b, c);
	int tca = ask(c, a);

	if(tab == tbc && tbc == tca){
        return vi();
	}

    vi ans;
    if(tab >= tbc && tab >= tca){
		ans.push_back(a); ans.push_back(b);
		return ans;
	}
	if(tbc >= tab && tbc >= tca){
		ans.push_back(b);
		ans.push_back(c);
		return ans;
	}
	ans.push_back(c); ans.push_back(a);
	return ans;
}

void proc(){
	if(2 == N){
		int tmp = answer(1, 2);
		assert(1 == tmp);
		return;
	}
	if(3 == N){		
		int tmp = ask(1, 2);
		if(2 == tmp){
			tmp = answer(1, 2);
			assert(1 == tmp);
			return;
		}
		tmp = ask(1, 3);
		if(2 == tmp){
			tmp = answer(1, 3);
			assert(1 == tmp);
			return;
		}		
		tmp = answer(2, 3);
		assert(1 == tmp);
		return;
	}

    vector<int> q;
	for(int i=1;i<=N;++i) q.push_back(i);
    while(q.size() >= 3){
		int a = q.back(); q.pop_back();
		int b = q.back(); q.pop_back();
		int c = q.back(); q.pop_back();
		auto vec = proc(a, b, c);
		for(int i : vec) q.push_back(i);
	}
	int a = q.back(); q.pop_back();
	int b = a;
	if(q.size() == 1){
		b = q.back(); q.pop_back();
	} 
	int tmp = answer(a, b);
	assert(1 == tmp);
	return;
}


int main(){
#ifndef ONLINE_JUDGE
    // freopen("1.txt", "r", stdin);
#endif
    srand((unsigned)time(nullptr));
	int nofkase;
	scanf("%d", &nofkase);
    while(nofkase--){
		Map.clear();
		scanf("%d", &N);
		proc();
	}
    return 0;
}


