/**
 * һ���ǳ��޴����ȫ��������������ǰ�ڵ㣬�Լ�һ���ַ�����ʾǰ������
 * ���ַ�������֮�����ͣ���Ľڵ��š���֤����1E18��
 * ���ڱ�֤�˴𰸣���������г�����Χ��L��R����һ����Uȥ����
 * ��������LR������ջ������������U�Ͱ�ǰ���LR��ջ�������û��ƥ���U����ֱ�Ӽ���
 * ����ٰ�û��ƥ���LR����һ��
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
int const SIZE = 1E6+5;
#endif

typedef unsigned long long llt;
llt N, X;
char A[SIZE];
vector<char> St;

llt proc(){
    St.clear();
    llt ans = X;
    for(char *p=A;*p;++p){
        if('U' == *p){
            if(St.empty()){
                St.push_back(*p);
                ans = ans / 2;
            }else{
                if('L' == St.back() || 'R' == St.back()){
                    St.pop_back();
                }else if('U' == St.back()){
                    St.push_back(*p);
                    ans = ans / 2;
                }else{
                    throw runtime_error("XXX");
                }
            }
        }else if('L'==*p||'R'==*p){
            if(St.empty()){
                St.push_back(*p);
            }else{
                if('U' == St.back()){
                    St.pop_back();
                    if('L' == *p) ans = ans << 1;
                    else ans = (ans<<1)|1;
                }else if('L'==St.back()||'R'==St.back()){
                    St.push_back(*p);
                }else{
                    throw runtime_error("yy");
                }
            }
        }else{
            throw runtime_error("XX");
        }
    }
    
    for(char ch: St){
        if('R' == ch) ans = ans + ans + 1;
        else if('L' == ch) ans <<= 1;
        
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    while(cin>>N>>X>>A){
        cout<<proc()<<endl;
    }    
    return 0;
}