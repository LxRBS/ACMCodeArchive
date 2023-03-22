#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;

int N, Q;
vi Flag;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
	__gnu_pbds::priority_queue<int, greater<int>, pairing_heap_tag> queue;

    N = getInt();
	Q = getInt();
	Flag.assign(N + 1, 0);
	int k = 1;
	for(int cmd,x,q=1;q<=Q;++q){
        switch(cmd=getInt()){
			case 1:{
                queue.push(k++);
			}break;
			case 2:{
                Flag[x = getInt()] = 1;
			}break;
			case 3:{
                while(Flag[x = queue.top()]) queue.pop(); 
				printf("%d\n", queue.top());
			}break;
			default:assert(0);
		}
	}
    return 0; 
}


