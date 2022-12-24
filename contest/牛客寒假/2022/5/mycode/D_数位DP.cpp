/**
 * 数位DP，要求相邻数位和为质数，且至少有1个1
 * 设Dijk，其中i表示数位，j表示前一个数是几，k表示有没有1
 * 搜索参数再加一个limit即可
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int const Flag[] = {
    0, 
	0, 1, 1, 0, 1, // 12345
	0, 1, 0, 0, 0, // 678910
	1, 0, 1, 0, 0, // 112345
	0, 1, 0, 1, 0  // 16789 20    
};

int Dig[13];
llt D[13][10][2];

llt dfs(int pos, int pre, int hasOne, bool limit){
	if(-1 == pos){
		return hasOne;
	}
	if(-1 != pre && !limit && -1 != D[pos][pre][hasOne]){
		return D[pos][pre][hasOne];
	}

	int last = limit ? Dig[pos] : 9;
	llt ans = 0;
	for(int i=0;i<=last;++i){
        if(-1 == pre){
			if(0 == i){
				ans += dfs(pos-1, -1, 0, limit&&i==Dig[pos]);
			}else{
				ans += dfs(pos-1, i, i==1?1:0, limit&&i==Dig[pos]);
			}
		}else if(Flag[i+pre]){
            ans += dfs(pos-1, i, hasOne==1||i==1?1:0, limit&&i==Dig[pos]);
		}
	}	
	return -1 != pre && !limit ? (D[pos][pre][hasOne]=ans) : ans;
}

llt f(llt n){
	fill(Dig, Dig+13, 0);
    int k = 0;
	while(n){
		Dig[k++] = n % 10;
		n /= 10;
	}
	// llt t1 = dfsTotal(k-1, -1, true);
	llt t1 = dfs(k-1, -1, 0, true);
	return t1;
}

llt f(llt a, llt b){
	llt cnt = 0;
	for(int i=a;i<=b;++i){
		cnt += [](int n)->int{
			if(n<10) return 1 == n;
			vector<int> v;
			while(n){
				v.push_back(n%10); n/=10;
			}
			int t = v[0] == 1 ? 1 : 0;
			for(int i=1,n=v.size();i<n;++i){
				if(!Flag[v[i-1]+v[i]]) return 0;
				if(1 == v[i]) t = 1;
			}
			return t;
		}(i);
	}
	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
	memset(D, -1, sizeof(D));
    llt s, e;
	cin>>s>>e;
	llt anss = f(s-1);
	llt anse = f(e);
	cout<<anse-anss<<endl;
#ifndef ONLINE_JUDGE
    cout<<"check: "<<f(s, e)<<endl;
#endif 	
    return 0;
}