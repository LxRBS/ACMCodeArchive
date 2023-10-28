/**
   给定一个数列A，从1~N，但是不包含3的倍数，也不包含末尾为3的数
   问Ai是多少。打表
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

int N;
int A[1100];
bool isOK(int c){
    return !(0==c%3 || 3==c%10);
}
void init(){
    for(int i=1,c=1;i<=1000;++c){
        if(isOK(c)){
            A[i++] = c;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    init();
    int nofkase = getUnsigned();
    while(nofkase--){
        printf("%d\n", A[getUnsigned()]);
    }
    return 0;
}

