/// 签到
#include <bits/stdc++.h>
using namespace std;

int N, M;
int R, C, V;

inline bool proc(){
    return V > R*C - 1 && N*M - V >= (N-R+1) * (M-C+1) - 1; 
}

int main(int argc, char* argv[]) {
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    while(5 == scanf("%d%d%d%d%d", &N, &M, &R, &C, &V)){
        puts(proc()?"Yes":"No");    
    }
	return 0;
}
