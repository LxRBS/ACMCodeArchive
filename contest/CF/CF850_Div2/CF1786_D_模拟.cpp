/**
 * 有3M个字母，其中w，i，n各占三分之一
 * 打乱构成了M个单词，每个单词三个字母。
 * 给定一个方案，每次选定两个单词，交换一个字母，使得所有单词都变成 "win"，注意不要求顺序
 * 一共只有10种可能性，其中win是好的，不用管，将诸如 wwi, wwn, www 等格式的单词分别保存
 * 考虑 wwi，这是缺少了n，因此首先查看inn，然后查看nnn，最后查看wnn，执行交换。
 * 然后依次处理 wwn, wii, iin, wnn, inn。
 * 全部处理完，剩下的必然是 www, iii, nnn，且数量相等，一起处理一下即可
 * 由于每一步至少能够构造出一个合法的单词，因此是O(M)的。
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

char getChar(){
	char ch = __hv007();
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int const W = 0;
int const I = 2;
int const N = 4;

int M;
array<vi, 64> Map;
vector<tuple<int, char, int, char>> Ans;

inline int get(vi & vec){
	if(vec.empty()) return 0;
	int ret = vec.back();
	vec.pop_back();
	return ret;
}

void proc(){
    Ans.clear();

	bool flag = false;

    auto & wwi = Map[6];
	auto & inn = Map[0x24];
	auto & nnn = Map[0x30];
	auto & wnn = Map[0x21];
	auto & wwn = Map[0x12];
	auto & iin = Map[0x18];
	auto & wii = Map[9];
	auto & iii = Map[12];
	auto & www = Map[3];

L:
	while(!wwi.empty()){
		flag = true;
		int b, a = get(wwi);
		if(b = get(inn)){
			Ans.emplace_back(a, 'w', b, 'n');
		}else if(b = get(nnn)){
			Ans.emplace_back(a, 'w', b, 'n');
            wnn.push_back(b);
		}else if(b = get(wnn)){
			Ans.emplace_back(a, 'w', b, 'n');
			wwn.push_back(b);
		}else{
			assert(0);
		}
	}

	while(!wwn.empty()){
		flag = true;
		int b, a = get(wwn);
		if(b = get(iin)){
            Ans.emplace_back(a, 'w', b, 'i');
		}else if(b = get(iii)){
			Ans.emplace_back(a, 'w', b, 'i');
			wii.push_back(b);
		}else if(b = get(wii)){
			Ans.emplace_back(a, 'w', b, 'i');
			wwi.push_back(b);
		}else{
			assert(0);
		}
	}

	while(!wii.empty()){
        flag = true;
		int b, a = get(wii);
		if(b = get(wnn)){
            Ans.emplace_back(a, 'i', b, 'n');
		}else if(b = get(nnn)){
			Ans.emplace_back(a, 'i', b, 'n');
			inn.push_back(b);
		}else if(b = get(inn)){
			Ans.emplace_back(a, 'i', b, 'n');
			iin.push_back(b);
		}else{
			assert(0);
		}
	}

	while(!iin.empty()){
        flag = true;
		int b, a = get(iin);
		if(b = get(wwn)){
            Ans.emplace_back(a, 'i', b, 'w');
		}else if(b = get(www)){
			Ans.emplace_back(a, 'i', b, 'w');
			wwi.push_back(b);
		}else if(b = get(wwi)){
			Ans.emplace_back(a, 'i', b, 'w');
			wii.push_back(b);
		}else{
			assert(0);
		}
	}

	while(!wnn.empty()){
        flag = true;
		int b, a = get(wnn);
		if(b = get(wii)){
            Ans.emplace_back(a, 'n', b, 'i');
		}else if(b = get(iii)){
			Ans.emplace_back(a, 'n', b, 'i');
			iin.push_back(b);
		}else if(b = get(iin)){
			Ans.emplace_back(a, 'n', b, 'i');
			inn.push_back(b);
		}else{
			assert(0);
		}
	}

	while(!inn.empty()){
        flag = true;
		int b, a = get(inn);
		if(b = get(wwi)){
            Ans.emplace_back(a, 'n', b, 'w');
		}else if(b = get(www)){
			Ans.emplace_back(a, 'n', b, 'w');
			wwn.push_back(b);
		}else if(b = get(wwn)){
			Ans.emplace_back(a, 'n', b, 'w');
			wnn.push_back(b);
		}else{
			assert(0);
		}
	}

	if(flag) {
		flag = false;
		goto L;
	}

	assert(www.size() == iii.size() && iii.size() == nnn.size());

    for(int i=0,sz=www.size();i<sz;++i){
		int wj = www[i], ij = iii[i], nj = nnn[i];
		Ans.emplace_back(wj, 'w', ij, 'i');
		Ans.emplace_back(wj, 'w', nj, 'n');
		Ans.emplace_back(ij, 'i', nj, 'n');
	}

	printf("%d\n", (int)Ans.size());
	for(const auto & p : Ans)printf("%d %c %d %c\n", get<0>(p), get<1>(p), get<2>(p), get<3>(p));
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase = getInt();
	int nofkase; cin >> nofkase;
    while(nofkase--){
		for(auto & a : Map) a.clear();
        cin >> M;
		for(int i=1;i<=M;++i){
			string s;
			cin >> s;
			int c[5] = {0};
			for(char ch : s){
                if('w' == ch) ++c[W];
				else if('i' == ch) ++c[I];
				else if('n' == ch) ++c[N];
				else assert(0);
			}
			Map[(c[W]<<W)|(c[I]<<I)|(c[N]<<N)].push_back(i);
		}
		proc();
	}
	return 0; 
}