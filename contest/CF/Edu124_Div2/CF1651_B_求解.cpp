/**
 * ��һ������A����ѡai��aj�����滻Ϊ|ai-aj|
 * Ҫʹ���滻������Ͳ���С���������巽��
 * ai+aj<=2(ai-aj)������ai>=3aj����
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