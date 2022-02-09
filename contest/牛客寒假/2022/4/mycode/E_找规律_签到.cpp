/**
 * 给了形如本代码中的f函数的代码，给定n，求f(n)
 * 先从1到10打一遍，发现f(x)=x，即可
*/
#include <bits/stdc++.h>
using namespace std;

long long f(long long x){
    if(x==1)return 1;
    return f(x/2)+f(x/2+x%2);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    long long n;cin>>n;cout<<n<<endl;
    return 0;
}
