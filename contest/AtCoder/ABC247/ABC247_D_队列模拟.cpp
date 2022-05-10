/**
  两种操作：
  1 x c: 入队c个x
  2 c: 出队c个元素
  c和x都在1E9，由于c比较大，不能一个一个入队
  因此做一个pair的队列，分别记录数量与数值即可    
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000+1];
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
int const SIZE = 11;
#else
int const SIZE = 2e6+5;
#endif

using llt = long long;
using pii = pair<llt, llt>;

int N;
pii Q[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d", &N);
    pii *head = Q, *tail = Q;
    for(int op,x,c,q=1;q<=N;++q){
        scanf("%d", &op);
        if(1 == (op)){
            scanf("%d%d", &x, &c);
            *tail++ = {c, x};
        }else if(2 == op){
            scanf("%d", &c);
            llt ans = 0;
            while(head != tail && c >= head->first){
                c -= head->first;
                ans += head->second * head->first;
                ++head;
            }
            if(c){
                head->first -= c;
                ans += c * head->second;                
            }
            printf("%lld\n", ans);
        }else{
            while(1);
        }
    }
    return 0;
}
