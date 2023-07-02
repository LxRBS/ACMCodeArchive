/**
 * 给一个矩阵，原始为T或者点，为T表示可以放置，为点则表示不能放置。
 * 需要将尽可能多的“PC”放置其中，问最多放多少个
 * 显然逐行解决即可。对每一行其实贪心即可。
 * 这里写了一个DFS，其实没有必要
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

using vi = vector<int>;
using vs = vector<string>;

int H, W;
vs A;
int Ans;
string T;

void dfs(string & s, int pos, int cur){
	if(pos + 1 >= W){
        if(Ans < cur){
			Ans = cur;
			T = s;
		}
		return;
	}

	if('T' == s[pos] and 'T' == s[pos + 1]){
		s[pos] = 'P'; s[pos + 1] = 'C';
		dfs(s, pos + 2, cur + 1);
		s[pos] = s[pos + 1] = 'T';
	}

	dfs(s, pos + 1, cur);
	return;
}

void proc(string & s){
    int k = 0;
	while(k + 1 < W){
		if('T' == s[k] and 'T' == s[k + 1]){
			s[k] = 'P'; s[k + 1] = 'C';
			k += 2;
		}else{
			++k;
		}
	}
	return;
}

void proc(){
    for(auto & s : A) proc(s);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> H >> W;
	A.assign(H, "");
	for(auto & s : A) cin >> s;
	proc();
	for(const auto & s : A) cout << s << endl;
    return 0; 
}
