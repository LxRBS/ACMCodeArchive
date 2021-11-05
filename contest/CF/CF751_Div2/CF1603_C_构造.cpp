/**
 * 给定一个数组a，再选定一个正整数k，做如下操作：
 * 每一次从a中选出k个元素，令x等于这k个元素的与
 * 然后再从这k个元素中减去x。
 * 问如何选择k，使得能够经过若干次操作，将数组清零
 * x显然是k个元素的公共位，然后减掉。
 * 因此想要清零数组，只要每次选出1个公共位进行清零即可
 * 要想将数组中所有元素特定位清零，则所选取的k必须是该位为1的数量的约数
 * 这样k必须是所有位为1的数量的公约数的约数
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

typedef int llt;

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

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
int const SIZE = 21;
#else 
int const SIZE = 201000;
#endif

int N;
int A[SIZE];
int Cnt[33];

void proc(){
	int g = 0;
	for(int i=0;i<30;++i)if(Cnt[i]){
        if(0 == g){
            g = Cnt[i];
		}else{
			g = gcd(g, Cnt[i]);
		}
	}

    if(0 == g){
		for(int i=1;i<=N;++i)printf("%d ", i);
		puts("");
		return;
	}

	vector<int> ans;
	for(llt i=1;i*i<=g;++i){
		if(g%i==0){
			ans.push_back(i);
			if(i*i!=g) ans.push_back(g/i);
		}
	}
	sort(ans.begin(), ans.end());
	for(auto i: ans){
		printf("%d ", i);
	}
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
		memset(Cnt, 0, sizeof(Cnt));
		N = getInt();
		for(int m, i=1;i<=N;++i){
			if(m = A[i] = getInt()){
				for(int i=0;i<30;++i){
					if(m&(1<<i)){
						++Cnt[i];
					}
				}				
			}
		} 

		proc();
	}
	return 0;
}