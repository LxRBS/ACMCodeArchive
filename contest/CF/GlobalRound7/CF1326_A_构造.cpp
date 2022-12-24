/**
 * 给定N，要求生成一个N长度的不含0的数字串s
 * 使得s不被它的任意数字整除
 * 除去特殊情况，只需要写
 * x22...223即可，x不是2就是3，保证整个数不被3整除即可
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
    int kase = getUnsigned();
    while(kase--){
        int n = getUnsigned();
        if(1==n){
            printf("-1\n");
            continue;
        }
        int m = n % 3;
        if (1==m) putchar('3');
        else putchar('2');
        for(int i=2;i<n;++i)putchar('2');
        printf("3\n");
    }
    return 0;
}
