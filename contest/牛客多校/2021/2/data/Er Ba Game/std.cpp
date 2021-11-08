#include<bits/stdc++.h>
using namespace std;
int js(int a,int b){
    if(a>b)swap(a,b);
    if(a==2&&b==8)return 10000;
    if(a==b)return 9000+a;
    return 8000+(a+b)%10*100+b*10;
}
int main(){
    int t,a,b,c,d;
    cin>>t;
    while(t--){
        cin>>a>>b>>c>>d;
        int e=js(a,b),f=js(c,d);
        if(e>f)printf("first\n");
        else if(e<f)printf("second\n");
        else printf("tie\n");
    }
    return 0;
}
