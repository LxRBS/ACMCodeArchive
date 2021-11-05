/**
    给一个数组，要求从开头或者结尾连续删除若干个数字，使得整个和不能被x整除。要求保留最多的数字
   首先求个和，看看是不是x的倍数。然后分别从开头和结尾检查Ai是否为x的倍数。
*/
#include<bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int const SIZE = 100010;
int A[SIZE];
int N, X;

int f(int sum){
    if(sum%X) return N;
    int ans = -1;
    for(int i=1;i<=N;++i){
        if(A[i]%X){
            ans = N - i;
            break;
        }
    }
    for(int i=N;i;--i){
        if(A[i]%X){
            ans = max(ans, i-1);
            break;
        }
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        X = getUnsigned();
        int sum = 0;
        for(int i=1;i<=N;++i){
            sum += (A[i]=getUnsigned());
        }

        printf("%d\n", f(sum));
    }
    return 0;
}

