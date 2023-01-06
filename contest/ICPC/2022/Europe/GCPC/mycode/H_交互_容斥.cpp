/**
 * 交互式。有一个字符串未知
 * 每次询问，给出若干个字母，返回这若干字母在字符串中位置
 * 要求询问6次，还原这个字符串。
 * 假设只有abc三个字母，则分别询问ab和bc可以得到结果
 * 类似的，将26个字母分组
 * abc def ghi 
 * jkl mno pqr
 * st  uvw xyz
 * 
 * 询问2次
 * abc def ghi jkl mno pqr
 * jkl mno pqr st uvw xyz
 * 可以求出如下3组字母的位置
 * abc def ghi
 * jkl mno pqr
 * st uvw xyz
 * 
 * 再询问2次
 * abc def jkl mno st uvw
 * def ghi mno pqr uvw xyz
 * 可以求出如下3组字母的位置
 * abc jkl st
 * def mno uvw
 * ghi pqr xyz
 * 
 * 两两结合可以得知如下9组字母的位置
 * abc def ghi jkl mno pqr st  uvw xyz
 * 
 * 最后再问2次，分别是
 * adgjmpsux和behknqtvy
 * 结合全集的结果还能求出 cfilorwz
 * 
 * 把9组与最后三组的结果结合，即可依次得到每个字母的位置
 * 一共询问6次，加上最后输出1次，一共交互7次。
 * 
 * 标程采用二进制的方式，将a~z编号1~26，二进制数一共是5位，做5次询问
 * 第i次询问，询问第i位为1的那些字母
 * 这样对每一个字母i而言，询问的结果可以分为A和B两部分，
 * 其中A部分一定都包含了i，B部分一定不含字母i，则
 * 字母i的位置 = JIAO{A} JIAO (全集 - BING{B}) 
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
int const SIZE = 30;
#else
int const SIZE = 30;
#endif

using vi = vector<int>;

void ask(const string & s, vi & v){
	printf("? %s\n", s.c_str());
	fflush(stdout);

	int n; scanf("%d", &n);
	v.clear(); v.reserve(n);
	for(int t,i=0;i<n;++i){
        scanf("%d", &t);
		v.push_back(t);
	}
	sort(v.begin(), v.end());
	return;
}

const string S1 = "abcdefghijklmnopqr";
const string S2 = "jklmnopqrstuvwxyz";
vi A1, A2;

const string S3 = "abcdefjklmnostuvw";
const string S4 = "ghipqrxyzdefmnouvw";
vi A3, A4;

map<string, vi> Map;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ask(S1, A1);
	ask(S2, A2);

    auto it = Map.find("abcdefghijklmnopqrstuvwxyz");
	assert(it == Map.end());
	it = Map.insert(it, {string("abcdefghijklmnopqrstuvwxyz"), vi()});
    set_union(A1.begin(), A1.end(), A2.begin(), A2.end(), back_inserter(it->second));

	int total = it->second.size();

    it = Map.find("jklmnopqr");
	assert(it == Map.end());
	it = Map.insert(it, {"jklmnopqr", vi()});
    set_intersection(A1.begin(), A1.end(), A2.begin(), A2.end(), back_inserter(it->second));

	auto jt = Map.find("abcdefghi");
	assert(jt == Map.end());
	jt = Map.insert(jt, {"abcdefghi", vi()});
    set_difference(A1.begin(), A1.end(), it->second.begin(), it->second.end(), back_inserter(jt->second));

	jt = Map.find("stuvwxyz");
	assert(jt == Map.end());
	jt = Map.insert(jt, {"stuvwxyz", vi()});
	set_difference(A2.begin(), A2.end(), it->second.begin(), it->second.end(), back_inserter(jt->second));

    ask(S3, A3);
	ask(S4, A4);

    it = Map.find("defmnouvw");
	assert(it == Map.end());
	it = Map.insert(it, {"defmnouvw", vi()});
	set_intersection(A3.begin(), A3.end(), A4.begin(), A4.end(), back_inserter(it->second));
	set_difference(A3.begin(), A3.end(), it->second.begin(), it->second.end(), back_inserter(Map["abcjklst"]));
	set_difference(A4.begin(), A4.end(), it->second.begin(), it->second.end(), back_inserter(Map["ghipqrxyz"]));


    map<string, vi> another;

	string a[] = {"abcdefghi", "jklmnopqr", "stuvwxyz"};
	string b[] = {"abcjklst", "defmnouvw", "ghipqrxyz"};

	for(const auto & sa : a){
		auto it = Map.find(sa);
		assert(it != Map.end());

		for(const auto & sb : b){
            auto jt = Map.find(sb);
			assert(jt != Map.end());

			string s;
			set_intersection(sa.begin(), sa.end(), sb.begin(), sb.end(), back_inserter(s));
			
			auto kt = Map.find(s);
			assert(kt == Map.end());
			kt = Map.insert(kt, {s, vi()});
			set_intersection(it->second.begin(), it->second.end(), jt->second.begin(), jt->second.end(), back_inserter(kt->second));
			
			auto pp = another.insert(*kt);
			assert(pp.second);
		}
	}

	string last[] = {
		"adgjmpsux", "behknqtvy", "cfilorwz"
	};

	vi lastvec[3];

	ask(last[0], lastvec[0]);
	ask(last[1], lastvec[1]);

	vi tmp;
	auto & quanji = Map["abcdefghijklmnopqrstuvwxyz"];
    set_difference(quanji.begin(), quanji.end(), lastvec[0].begin(), lastvec[0].end(), back_inserter(tmp));
	set_difference(tmp.begin(), tmp.end(), lastvec[1].begin(), lastvec[1].end(), back_inserter(lastvec[2]));

	map<string, vi> ans;

	for(int i=0;i<3;++i){
		string s = last[i];
		const vi & vec = lastvec[i];
		
        for(const auto & p : another){
			string t;
			set_intersection(p.first.begin(), p.first.end(), s.begin(), s.end(), back_inserter(t));

			assert(t.length() <= 1);
			if(t.empty()) continue;
			vi tt;
			set_intersection(p.second.begin(), p.second.end(), vec.begin(), vec.end(), back_inserter(tt));

			auto pp = ans.insert({t, tt});
			assert(pp.second);
		}		
	}

	string s(total, ' ');
	for(const auto & p : ans){
		assert(p.first.length() == 1);
		char ch = p.first[0];

		for(int i : p.second){
			s[i-1] = ch;
		}
	}

	printf("! %s\n", s.c_str());
    return 0;
}
