/**
 * 交互式。有一个字符串未知
 * 每次询问，给出若干个字母，返回这若干字母在字符串中位置
 * 要求询问6次，还原这个字符串。
 * 这是标程的做法，采用二进制的方式，将a~z编号1~26，二进制数一共是5位，做5次询问即可
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


vector<vi> Vec(5, vi());

vi bing(const vi & idx){
    vi ans;
    for(int i : idx){
		const vi & v = Vec[i];
		vi tmp;
		set_union(ans.begin(), ans.end(), v.begin(), v.end(), back_inserter(tmp));
		ans.assign(tmp.begin(), tmp.end());
	}
	return ans;
}

vi jiao(const vi & idx){
    vi ans;
	if(idx.empty()) return ans;
	ans.assign(Vec[idx[0]].begin(), Vec[idx[0]].end());
	for(int i=1,n=idx.size();i<n;++i){
		const vi & v = Vec[idx[i]];
		vi tmp;
		set_intersection(ans.begin(), ans.end(), v.begin(), v.end(), back_inserter(tmp));
		ans.assign(tmp.begin(), tmp.end());
	}
	return ans;	
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    vector<string> ss(5, "");
    for(int i=1;i<=26;++i){
        for(int j=0;j<5;++j){
			if(i & (1 << j)){
                ss[j] += ((char)('a' + i - 1)); 
			}
		}
	}

	
	for(int i=0;i<5;++i){
		ask(ss[i], Vec[i]);
	}

	vi quan = bing({0, 1, 2, 3, 4});
	int total = quan.size();
	string ans(total, ' ');

	for(int i=1;i<=26;++i){
		vi you, mei;
		for(int j=0;j<5;++j){
			if(i & (1 << j)) you.push_back(j);
			else mei.push_back(j);
		}

		vi youyou = jiao(you);
		vi meimei = bing(mei);
		vi bu;
		set_difference(quan.begin(), quan.end(), meimei.begin(), meimei.end(), back_inserter(bu));
		vi last;
		set_intersection(bu.begin(), bu.end(), youyou.begin(), youyou.end(), back_inserter(last));

		for(int k : last){
			ans[k - 1] = 'a' + i - 1;
		}
	}

	printf("! %s\n", ans.c_str());
    return 0;
}
