/**
  考虑有一个桶子，初始里面有一个元素；还有一个数组A
  每一次从数组中挑出若干个数放在桶子里面，假设当前挑出的数量为n，桶子里现在有m，要求满足：
  对每一个挑出来的ai，ai都要小于n+m
   排序以后，令Ai-=i，然后找到最后一个小于等于0的位置即可。
   因为对于这样的i，显然可以一次性的把1~i的所有数拿出来放进桶里。然后剩下的就都不行了。
*/
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
typedef vector<int> vi;

template<typename T>string value2string(const T &t){
    stringstream ss;
    ss<<t;
    return ss.str();
}

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 120;
#else
int const SIZE = 300010;
#endif

int A[SIZE], Cnt[SIZE], B[SIZE];
int N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();        
        for(int i=1;i<=N;++i){
            A[i]=getUnsigned();
        } 
        sort(A+1, A+N+1);
        int k = 0;
        for(int i=N;i;--i){
            if((A[i] -= i) <= 0){
                k = i;
                break;
            }
        }
#ifndef ONLINE_JUDGE
        for(int i=1;i<=N;++i){
            cout<<A[i]<<" ";
        }        
        cout<<endl;
#endif
        printf("%d\n", k+1);
    }
    return 0;
}
