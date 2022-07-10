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
typedef pair<int, int> pii;
#define fi first
#define se second

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else 
int const SIZE = 102100;
#endif

int N, K;
int A[SIZE], B[SIZE];

bool Flag[SIZE];
int Now[SIZE];

bool isOK(int m){
    fill(Flag, Flag+N+1, 0);
    fill(Now, Now+N+1, 0);
    int hit = 0;

    priority_queue<pii> q;
    int sz = 0;
    for(int i=1;i<=N;++i){
        if(Flag[A[i]]){
            if(++hit >= K) return true;
            Now[A[i]] = i;
            q.push({-i, A[i]});
        }else{
            if(sz >= m){
                while(1){
                    pii h = q.top();
                    q.pop();

                    if(Now[h.se] == -h.fi){
                        --sz;
                        Flag[h.se] = false;
                        break;
                    }
                }
            }
            Flag[A[i]] = true;
            Now[A[i]] = i;
            q.push({-i, A[i]});
            ++sz;
        }    
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    K = getInt();
    for(int i=1;i<=N;++i) B[i] = A[i] = getInt();
    sort(B+1, B+N+1);
    int n = unique(B+1, B+N+1) - B;

    for(int i=1;i<=N;++i){
        A[i] = lower_bound(B+1, B+n, A[i]) - B;
    }

    if(K + n > N + 1){
         puts("cbddl");
         return 0;
    }
    
    int left = 1, right = N, mid;
    do{
        mid = (left + right) >> 1;
        if(isOK(mid)) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);
    if(left > N) puts("cbddl");
    else printf("%d\n", left);
    return 0;
}