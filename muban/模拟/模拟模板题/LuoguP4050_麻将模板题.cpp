/**
 * 花色只有一种，点数最多400，牌张数不限，最简单的和牌规则
 * 问所听牌, O(400^3)，常数较大，O2才能过，否则会T两个点
 */
#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;


namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}


namespace Majhong{


int const ZI = 0;
int const TIAO = 1;
int const BING = 2;
int const WAN = 3;

/// 牌类型，正常是4，不正常看题目要求
/// [0, TYPE_SIZE)
int const TYPE_SIZE = 1;
/// 点数，正常是9，不正常看题目
/// [1, Dian_SIZE)
int DIAN_SIZE = 10;
/// 牌的张数限制，正常是4
int const LIMIT_PER_PAI = 4000;

/// 牌, <类型, 点数>
using PaiTy = pair<int, int>;
using ShouPaiTy = array<vector<int>, TYPE_SIZE>;

map<string, function<bool(ShouPaiTy &, int)>> CheckHu = {
    {"normal", [](ShouPaiTy & shoupai, int total)->bool{
        function<bool(int, int)> dfs = [&](int type, int dian)->bool{
            if(0 == total) return true;
 
            while(type < TYPE_SIZE){
				while(0 == shoupai[type][dian] && dian < DIAN_SIZE) ++dian;
				if(shoupai[type][dian]) break;
				if(DIAN_SIZE == dian) dian = 0, type += 1;
			}
			if(TYPE_SIZE == type) return false;
			

            auto & c = shoupai[type][dian];		
			int kezi = c / 3; // 最多刻子的数量
			int shunzi = c;   // 最多顺子的数量
			if(dian + 2 >= DIAN_SIZE) shunzi = 0;
			else shunzi = min(c, min(shoupai[type][dian+1], shoupai[type][dian+2]));

            int left = c - kezi * 3;
			if(left > shunzi) return false;
			
            /// 贪心，用最多的刻子必然不影响结果的正确性
			total -= c + left + left; c = 0;
			shoupai[type][dian+1] -= left;
			shoupai[type][dian+2] -= left;
			auto ans = dfs(type, dian + 1);
			total += (c = kezi * 3 + left) + left + left;
			shoupai[type][dian+1] += left;
			shoupai[type][dian+2] += left;
            return ans;
		};

		bool ret = false;
		/// 首先拿出一对
		for(int type=0;type<TYPE_SIZE;++type)for(int dian=1;dian<DIAN_SIZE;++dian){
			auto & c = shoupai[type][dian];
			if(c < 2) continue;

			c -= 2; total -= 2;
			ret = dfs(0, 1);
			c += 2; total += 2;
			if(ret) break;
		}
		return ret;
	}}

};

/// 对于给定的手牌和摸到的新牌，能否和牌，和牌类型可以获取
bool isHu(ShouPaiTy & shoupai, PaiTy mopai, int total){
	bool ret = false;
    shoupai[mopai.first][mopai.second] += 1;
	total += 1;
	for(const auto & p : CheckHu){
        auto f = p.second;
		if(f(shoupai, total)){
			ret = true;
			break;
		}
	}
	shoupai[mopai.first][mopai.second] -= 1;
	return ret;
}

/// 对于给定的手牌，是否听牌，铳牌放在ret中, 暴力
bool isTing(ShouPaiTy & shoupai, vector<PaiTy> & ret){
    ret.clear();
	int total = 0;
	for(int type=0;type<TYPE_SIZE;++type)for(int dian=1;dian<DIAN_SIZE;++dian)total+=shoupai[type][dian];
	
	bool flag = false;
    for(int type=0;type<TYPE_SIZE;++type){
		for(int dian=1;dian<DIAN_SIZE;++dian){
			if(shoupai[type][dian] == LIMIT_PER_PAI) continue;
			if(!isHu(shoupai, {type, dian}, total)) continue;
			
			ret.emplace_back(type, dian);
			flag = true;

		}
	}
	return flag;
}


}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
    using namespace IO;
    Majhong::DIAN_SIZE = getInt() + 1;
	int m = getInt();
	Majhong::ShouPaiTy shoupai;
	for(int i=0;i<Majhong::TYPE_SIZE;++i) shoupai[i].assign(Majhong::DIAN_SIZE, 0);
	for(int i=0;i<3*m+1;++i){
		++shoupai[0][getInt()];
	}
	vector<Majhong::PaiTy> ret;
	bool b = Majhong::isTing(shoupai, ret);
	if(!b) return printf("NO\n"), 0;
	for(const auto & p : ret)printf("%d ", p.second);printf("\n");
    return 0;
}