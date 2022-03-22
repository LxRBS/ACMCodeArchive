#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,m;
    int i,j,k;
    int a,b,c;
    cin>>n;
    int s=0;
    for(i=0;i<n;i++){
        cin>>a>>b;
        if(b%2){
            s^=a%2;
            continue;
        }else{
            a%=b+1;
            if(a==b)s^=2;
            else s^=a%2;
        }
    }
    if(s)cout<<"Alice"<<endl;
    else cout<<"Bob"<<endl;
}
