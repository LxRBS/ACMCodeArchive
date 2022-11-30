/**
 * 给定一个N长度的数组A，对每个Ai可以做一次操作令Ai*=i
 * 欲使所有Ai的乘积能够整除2^N，问最少有做几次操作
 * 数一下原始Ai的2的数量，假设距离N还有left的差距，
 * 则贪心使用含有2最多的下标
 * 利用筛法预处理出所有下标能够提供的2的数量
 * 再利用map依次记录N以内提供2的数量的下标的数量
 * i表示能够提供i个2的因子，map[i]表示能够提供i个2的下标一共有多少个
 * 从多到少遍历一次，当left减到0，即有答案。
 */
#include <assert.h>
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
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;

int D[SIZE] = {0};
map<int, int> Cnt;
void init(){
	for(llt i=2;i<SIZE;i<<=1){
        for(llt j=i;j<SIZE;j+=i){
            ++D[j];
		}
	}
}

int N;
vi A;

int proc(){
	Cnt.clear();
	for(int i=2;i<=N;i+=2) ++Cnt[D[i]];

	int left = N;
	for(auto i : A){
		while(i % 2 == 0) i /= 2, --left;
		if(left <= 0) return 0;
	}
  
    int ans = 0;
    for(auto it=Cnt.rbegin(),et=Cnt.rend();it!=et;++it){
		llt c2 = it->first, c = it->second;
        if(left <= c2 * c){
			int tmp = left / c2;
			if(left % c2 == 0) return ans + tmp;
			return ans + tmp + 1;
		}
		left -= c2 * c;
		ans += c;
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   
    init(); 
    int nofkase = getInt();
	while(nofkase--){
		A.assign(N = getInt(), 0); 
		for(auto & c : A) c = getInt();
		printf("%d\n", proc());		
	}
    return 0;
}