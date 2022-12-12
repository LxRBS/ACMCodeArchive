/**
 * 给定一个原始的字符串T0，每次将T中的某个字母c全部从T中删除得到一个新的字符串Ti，将Ti接到T0...T[i-1]之后
 * 如此反复，得到一个新的字符串S
 * 现在给出S，问S能否通过上述操作得到，如果能，输出T0以及操作的顺序。
 * S的最后一个字母显然是最后一个删除的，那倒数第二个删除的是？
 * 反向遍历S，显然字母依次出现的顺序就是其删除的倒序，因为不可能越过后面的字母
 * 于是就得到了字母删除的顺序，记作Order。同时容易观察到，字母的数量显然是与段数成比例的。
 * 假设Order的长度是D，则Order[D-1]的数量一定是D的倍数，Order[1]的数量一定是2的倍数，Order[0]的数量一定是1的倍数
 * 于是T0的长度也可以确定。记作OriginLength。
 * 最后再验证一下顺序即可。
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
	while(!islower(ch)) ch = __hv007();
	return ch;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 53;
#else
int const SIZE = 5e5+5;
#endif

using llt = long long;
using vi = vector<int>;

/// N表示字符串长度，Total表示字符串不同字母的数量
int N, Total;
char Input[SIZE];
int A[SIZE];
int Cnt[26][SIZE];
vi Order;
vi Origin;
int OriginLength;

bool check(){
	int curlen = OriginLength;
	int pos = OriginLength;
	set<int> deled;
	for(auto i : Order){
		if(Cnt[i][pos] != Cnt[i][N]) return false;
		int ori = pos + 1;
		pos += (curlen -= Cnt[i][OriginLength]);
        deled.insert(i);
		if(deled.size() == Order.size()) break;

		int k = 1;
		for(int j=ori;j<pos;++j){
            while(k<=OriginLength && deled.count(A[k])) ++k;
			if(k > OriginLength) return false;
			if(A[k] != A[j]) return false;
			++k;
		}
	}
	return true;
}

void proc(){
	Order.clear();
	N = 1; Total = 0;
    for(auto p=Input;*p;++p,++N){       
		for(int i=0;i<26;++i) Cnt[i][N] = Cnt[i][N-1]; 
        if(1 == ++Cnt[A[N] = *p - 'a'][N]) ++Total;
	}
	N -= 1;
	int cnt[26] = {0};
	for(int i=N;i>=1;--i){
		if(1 == ++cnt[A[i]]){
            Order.push_back(A[i]);
		}
	}
	/// 必须按照order的顺序来处理，且原字符串的长度必须是OriginLength
	reverse(Order.begin(), Order.end());
	OriginLength = 0;
	for(int i=0,n=Order.size();i<n;++i){
        int v = Order[i];
		if(Cnt[v][N] % (i + 1)) {
			return (void)printf("-1\n");
		}
		OriginLength += Cnt[v][N] / (i + 1);
	}
	if(!check()) return (void)printf("-1\n");
	for(int i=1;i<=OriginLength;++i)printf("%c", A[i]+'a');
	printf(" ");
	for(auto i : Order) printf("%c", i+'a');
	printf("\n");	 
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s", Input);
		proc();
	}
    return 0;
}