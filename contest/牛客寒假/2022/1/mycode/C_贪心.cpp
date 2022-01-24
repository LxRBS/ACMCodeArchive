/**
 * 一个序列，如果两个元素之间有关系，则二者之间至少要相隔3个元素，如果不够，则插入空格
 * 问最少插入多少个空格，使得满足要求
 * 贪心即可，从前往后不够的地方插入空格
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000055;
#endif

typedef long long llt;

int N;
vector<int> Vec;

void get(int &x, int&y, int &z){
	x = y = z = -1;
	for(int i=Vec.size()-1;i>=0;--i){
        if(Vec[i]){
			if(-1 == z){
				z = i;
			}else if(-1 == y){
				y = i;
			}else if(-1 == x){
				x = i;
				return;
			}
		}
	}
}

void f(int t){
	if(0 == t){
		Vec.push_back(0);Vec.push_back(0);Vec.push_back(0);
	}else if(1 == t){
		Vec.push_back(0);Vec.push_back(0);
	}else if(2 == t){
		Vec.push_back(0);
	}	
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int t,x,y,z,a,b,c,i=1;i<=N;++i){
        a = getInt();
		b = getInt();
		c = getInt();    
		if(0==a&&0==b&&0==c){
			Vec.push_back(i);
			continue;
		} 
        get(x, y, z);
        if(c){
			t = Vec.size() - x - 1;
			f(t);
		}
		if(b){
			t = Vec.size() - y - 1;
			f(t);
		}
		if(a){
			t = Vec.size() - z - 1;
			f(t);
		}
		Vec.push_back(i);
	}
	printf("%d\n", Vec.size()-N);
    return 0;
}
