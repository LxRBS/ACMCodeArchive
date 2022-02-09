/**
 * 给定规则，要求把一个字符串转换成另一个字符串
 * 模拟
*/
#include <bits/stdc++.h>
using namespace std;

string S;
int S2I[256] = {0};
string Ans;

void proc(int x, int t){
	Ans.push_back((char)('0'+x));
    if(0 == t) return;
    if(t > 0){
		Ans.append(string(t, '*'));
		return;
	}
	t = -t;
	Ans.append(string(t, '.'));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    S2I['C'] = 1; S2I['D'] = 2;
	S2I['E'] = 3; S2I['F'] = 4;
	S2I['G'] = 5; S2I['A'] = 6;
	S2I['B'] = 7;

    cin>>S;
	int cur = 0;
	for(auto ch: S){
		if('<' == ch){
			--cur;
		}else if('>' == ch){
			++cur;
		}else if('A' <= ch && ch <= 'G'){
            proc(S2I[ch], cur);
		}else{
			throw runtime_error("XX");
		}
	}
	cout<<Ans<<endl;
    return 0;
}
