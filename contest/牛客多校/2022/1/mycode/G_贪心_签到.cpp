/// 给一个数N（一百万位），问[1, N]之间按字典序计最大的数是多少
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 106;
#else
int const SIZE = 1E6+7;
#endif

using llt = long long;

char A[SIZE];
char * proc(){
    int n = strlen(A);
    if(1 == n) return A;

    bool flag = false;
    for(int i=0;i<n-1;++i){
        if('9' == A[i]) continue;

        A[i] = '9';
        flag = true;
    }
    if(flag) A[n-1] = '\0';
    return A;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> A;
    cout << proc() << endl;
    return 0;
}