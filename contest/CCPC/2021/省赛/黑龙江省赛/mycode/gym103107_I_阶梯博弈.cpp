/**
 * n个赛道，每条赛道m辆车，每个车各有位置
 * 每次选择一辆车向右移动一格
 * 车不能跨过车，所以如果被选车辆右边紧邻别的车，则整个车队一起右移一格
 * 移动终点或者移到紧邻终点车队就不能再移动了
 * 两个人轮流移车，问先手胜负
 * 显然是一个ICG问题，只需要考虑一条赛道的SG函数即可
 * 考虑车队的情况，对一个车队而言，显然就是可以选任意数量往右移一格
 * 再考虑单个车，无论如何，对某个车它只能往右移动右边空格的数量
 * 因此可以看做是一个阶梯博弈，阶梯数就是右边空格的数量
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#define pb push_back
typedef vector<int> vi;

int f(){
	int m = getUnsigned();
	int e = getUnsigned();

    vi cnt, pos;
	for(int x,i=0;i<m;++i){
        x = getUnsigned();
        if(pos.empty() || pos.back()+1!=x){
			pos.pb(x);
			cnt.pb(1);
		}else{
			++cnt.back();
			pos.back() = x;
		}
	}
	assert(pos.size() == cnt.size());

	int ans = 0;
	int sum = 0;
	for(int x,i=pos.size()-1;i>=0;--i){
        x = e - pos[i] - sum;
        if(x&1) ans ^= cnt[i];
		sum += cnt[i];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
		int n = getUnsigned();
		int ans = 0;
		for(int i=0;i<n;++i){
			ans ^= f();
		}
		puts(ans?"Alice":"Bob");
	}
    return 0;
}
