/**
 * 给定N个字符串，长度最多8，问每个字符串si是否等于sj+sk
 * 考虑到长度只有8，对每个字符串si，对长度L从1到7，可以检查
 * si.substr(0, L)和si.substr(L)是否均存在，即可
 * 最多循环O(8N*2logN)
 * 注意可能有重复的字符串出现。
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

char getChar(){
    char ch = __hv007();
    while(!isalpha(ch)) ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

int N;
map<string, vector<int>> A;


char Out[SIZE];

char * proc(){
    for(const auto & p : A){
        auto && s = p.first;
        int n = s.length();
        for(int i=1;i<n;++i){
            auto && a = s.substr(0, i);
            auto && b = s.substr(i);
            if(A.count(a) && A.count(b)){
                for(auto j : p.second) Out[j] = '1';
                break;
            }
        }
    }
    Out[N] = '\0';
    return Out;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin.sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int nofkase; cin >> nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        cin >> N;
        A.clear(); 
        fill(Out, Out+N, '0');
        for(int i=0;i<N;++i){
            string s; cin >> s;
            A[s].push_back(i);
        }
        cout << proc() << endl;
    }
    return 0;
}

