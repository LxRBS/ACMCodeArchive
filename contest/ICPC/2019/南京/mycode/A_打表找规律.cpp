/**
   给定集合{1,2,...,n}，要求一个k
   满足任选k子集，其中必然包含一对数可以整除
   且k是最小的
   打表找规律
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        printf("%d\n",(n>>1)+(n&1)+1);
    }
    return 0;
}
