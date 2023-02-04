/**
 * 给定字符串，修改一个字母使得udu的子序列数量最少。
 * 问改后的字符串。显然只可能更改u和d。
 * 首先可以枚举每一个d，其对子序列总数的贡献显然是前面u的数量乘以后面u的数量
 * 这也就是改掉这个d减少的数量。
 * 再考虑改u，显然只需要更改第一个u或者最后一个u。
 * 然后把这三类比较一下即可。
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
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vi = vector<int>;

int N;
char A[SIZE];
vi Suf, Pre;

void proc(){
    Suf.assign(N, 0);
    Pre.assign(N, 0);
    
    int prepos = -1;
    if('u' == A[0]) {
        Pre[0] = 1;
        prepos = 0;
    }
    for(int i=1;i<N;++i){
        if('u' == A[i]) {
            Pre[i] = 1 + Pre[i - 1];
            if(-1 == prepos) prepos = i;
        }
        else Pre[i] = Pre[i - 1];
    }

    if(-1 == prepos) return (void)puts(A);


    int sufpos = -1;
    if('u' == A[N - 1]) {
        Suf[N-1] = 1;
        sufpos = N - 1;
    }
    for(int i=N-2;i>=0;--i){
        if('u' == A[i]) {
            Suf[i] = 1 + Suf[i+1];
            if(-1 == sufpos) sufpos = i;
        }
        else Suf[i] = Suf[i + 1];
    }

    llt ansd = 0LL;
    int dpos = -1;
    for(int i=1;i<N-1;++i){
        if('d' == A[i]){
            auto tmp = 1LL * Pre[i] * Suf[i];
            if(ansd < tmp){
                ansd = tmp;
                dpos = i;
            }     
        }
    }

    llt firstu = 0LL;
    for(int i=prepos+1;i<N-1;++i){
        if('d' == A[i]){
            firstu += Suf[i]; 
        }
    }

    llt lastu = 0LL;
    for(int i=sufpos-1;i>=1;--i){
        if('d' == A[i]){
            lastu += Pre[i];
        }
    }
    vector<pair<llt, int>> vec = {{ansd, dpos}, {firstu, prepos}, {lastu, sufpos}};
    sort(vec.begin(), vec.end());
    auto & pp = vec.back();
    if(0 == pp.first) return (void)puts(A);

    A[pp.second] = 'z';
    puts(A);
    return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%s", A);
    N = strlen(A);
    proc();
    return 0;
}