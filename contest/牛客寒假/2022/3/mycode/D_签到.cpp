#include<bits/stdc++.h>
using namespace std;
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 100010;
#endif
 
int N;
char A[SIZE];
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d%s", &N, A);
    char *p0 = nullptr, *p1 = nullptr;
    for(char *p = A;*p;++p){
        if(p0 == nullptr && *p == '0') p0 = p;
        if(p1 == nullptr && *p == '1') p1 = p;
        if(p0 != nullptr && p1 != nullptr){
            break;
        }
    }
    swap(*p0, *p1);
    puts(A);
    return 0;
}