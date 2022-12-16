/**
 * 给定数组X和Y，要求把元素分组，使得每一组的Yi之和大于等于Xi之和
 * 问最多能划分的组
 * 贪心即可，每一组没有必要多塞元素，两个元素即可
 * 首先求得Y-X，然后尽可能多的令一正一负搭配。
 * 再把剩下的非负数两个两个一分即可。
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

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N;
vi X, Y;

int proc(){
	int ans = 0;
    vi z, f, o;
	z.reserve(N);
	f.reserve(N);
	o.reserve(N);
	for(int i=0;i<N;++i) {
		int tmp = Y[i] - X[i];
		if(tmp > 0) z.push_back(tmp);
		else if(tmp < 0) f.push_back(tmp);
		else o.push_back(tmp);
	}
	
	sort(f.begin(), f.end());
	sort(z.begin(), z.end(), greater<int>());
    
	int kf = 0, kz = 0;
	int fn = f.size(), zn = z.size();
	while(kf<fn && kz<zn){
        int tmp = f[kf] + z[kz];
		if(tmp >= 0){
			++kf, ++kz, ++ans;
		}else{
			++kf;
		}
	}

	ans += o.size() / 2;
	if(kz != zn){
		int t = zn - kz;
		ans += t / 2;
		if((o.size() & 1) && (t & 1)) ++ ans;
	}	
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        X.assign(N=getInt(), 0);
		Y.assign(N, 0);
		for(int & i : X) i = getInt();
		for(int & i : Y) i = getInt();
		printf("%d\n", proc());
	}

    return 0;
}


