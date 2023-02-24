/**
 * 给定N个字符串，每个字符串恰好包含从0-9的10个数字
 * 每一秒钟选择一个字符串，假设第t秒选择第i个字符串，则会选出数字S[i][t%10]
 * 现在问要选出N个相同的数字，最少需要几秒
 * 改成判定性问题即可。对于某个数值v，第i个串能够选出的时刻就是pos+10k，
 * 所有串对同一个v不能重复时刻，用贪心即可 
 */
#include <bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 105;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>;

int N;
string S[SIZE];

int proc(int value, int idx){
	const string & s = S[idx];
	int k = 0;
	while(s[k] - '0' != value) ++k;
	return k;
}

int proc(int value){
	int flag[1010] = {0};
	int ans = 0;
	for(int i=0;i<N;++i){
		int tmp = proc(value, i);
		while(flag[tmp]) tmp += 10;
		flag[tmp] = 1;
		ans = max(ans, tmp);
	}
	return ans;
}

int proc(){
	int ans = 1E9;
	for(int i=0;i<10;++i){
		ans = min(proc(i), ans);
	}
	return  ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while(cin>>N){
		for(int i=0;i<N;++i) cin>>S[i];
		cout<<proc()<<endl;		
	}
    return 0;
}