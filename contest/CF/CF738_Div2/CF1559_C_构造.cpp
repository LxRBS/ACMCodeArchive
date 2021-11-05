/**
    N+1个点的图，1~N之间依次有边。 
    再给定一个N长度的01串，Ai为0表示i到N+1有边，为1表示N+1到i有边
    要求给定一个遍历顺序，使得1~N+1均访问且只访问一次
    找到最后一个0的位置，走到N+1，然后走回来
    Pos忘记初始化了。。。。。。
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
int A[11110];
int Pos;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        Pos = 0;
        for(int i=1;i<=N;++i){
            if(0==(A[i] = getUnsigned())){
                Pos = i;
            }
        }
        for(int i=1;i<=Pos;++i)printf("%d ", i);
        printf("%d ", N+1);
        for(int i=Pos+1;i<=N;++i)printf("%d ", i);
        printf("\n");
    }
    return 0;
}

