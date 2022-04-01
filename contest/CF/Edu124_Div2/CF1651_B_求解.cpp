/**
 * 给一个数组A，任选ai和aj，均替换为|ai-aj|
 * 要使得替换后数组和不变小，给出具体方案
 * ai+aj<=2(ai-aj)，所以ai>=3aj即可
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 1E5+5;
#endif

int N;

void proc(){
    if(N > 19) return (void)puts("NO");
    puts("YES");
    printf("1");
    for(int k=3,i=1;i<N;++i,k*=3)printf(" %d", k);
    puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; cin>>nofkase;
    while(nofkase--){
        cin>>N;
        proc();
    }
    return 0;
}