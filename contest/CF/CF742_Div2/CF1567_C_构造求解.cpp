/**
 * 现在有一种加法，如果有进位的话，会进到高两位
 * 例如: 9 + 6 本来等于15，向十位进位
 * 按照新规则要向百位进位，所以 9 + 6 = 105
 * 现在给定n，问在新加法下，一共有多少对数，使得其新加法结果为n
 * 在新加法下，奇偶数位上的加法是符合原有加法的
 * 例如，新加法 2039 + 2976 = 15005
 * 将每个加数按奇偶位拆开:
 * 2 3  + 2 7  =  5 0
 *  0 9 +  9 6 = 1 0 5
 * 因此把n拆成a和b，有多少对数加起来等于a，有多少对数加起来等于b
*/
#include <bits/stdc++.h>
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

typedef long long llt;

llt proc(){
	char s[22];
	scanf("%s", s);
    llt a = 0;
    llt b = 0;
    for(int i=0,n=strlen(s);i<n;++i){
        if(i&1){
            a = a * 10 + s[i] - '0';
        }else{
            b = b * 10 + s[i] - '0';
        }
    }
    return (a+1) * (b+1) - 2;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
	scanf("%d", &nofkase);
    while(nofkase--){
        printf("%lld\n", proc());
    }
    return 0;
}
