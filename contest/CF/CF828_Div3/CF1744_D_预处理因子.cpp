/**
 * ����һ��N���ȵ�����A����ÿ��Ai������һ�β�����Ai*=i
 * ��ʹ����Ai�ĳ˻��ܹ�����2^N���������������β���
 * ��һ��ԭʼAi��2���������������N����left�Ĳ�࣬
 * ��̰��ʹ�ú���2�����±�
 * ����ɸ��Ԥ����������±��ܹ��ṩ��2������
 * ������map���μ�¼N�����ṩ2���������±������
 * i��ʾ�ܹ��ṩi��2�����ӣ�map[i]��ʾ�ܹ��ṩi��2���±�һ���ж��ٸ�
 * �Ӷൽ�ٱ���һ�Σ���left����0�����д𰸡�
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