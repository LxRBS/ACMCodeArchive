/**
 * ������������Ϊ3���ַ���S��T������RGB���
 * ��Sʵʩ������ÿ��ѡ������λ�ý��н�����
 * ���Ƿ���ǡ�ò���10^18�Σ���S���T
 * S������һ����6�֣��²����ֿ������ֲ��С�
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
int const SIZE = 45;
#else
int const SIZE = 1E5+5;
#endif

bool proc(string s, string r){
	if(s == r) return true;
    string t;
	t.push_back(s[1]); t.push_back(s[2]); t.push_back(s[0]);
	if(t == r) return true;

	// t.clear();
	// t = s; reverse(t.begin(), t.end());
	// if(t == r) return true;

	t.clear();
    t.push_back(s[2]); t.push_back(s[0]); t.push_back(s[1]);
	if(t == r) return true;

	return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	char ch;
	string s; for(int i=0;i<3;++i){cin>>ch;s+=ch;}
	string r; for(int i=0;i<3;++i){cin>>ch;r+=ch;}
	cout<<(proc(s, r)?"Yes":"No")<<endl;
	// cout<<"Yes"<<endl;
    return 0;
}