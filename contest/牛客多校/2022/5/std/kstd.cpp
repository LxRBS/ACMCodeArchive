#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n,k;
    cin>>n>>k;
    long long res=2*(n-k);
    if(n+1<=res)
        cout<<(n+1)<<endl;
    else cout<<"-1"<<endl;

    return 0;
}