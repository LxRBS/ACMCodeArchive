//给定先序和中序，求后序
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;


void f(string const&a,string const&b){
    if ( a.empty() ) return;
    //a的第一个字母为当前树根
    int pos = b.find(a[0]);

    f(a.substr(1,pos),b.substr(0,pos));
    f(a.substr(pos+1),b.substr(pos+1));
    cout<<a[0];
}

string A,B;

int main(){
    while( cin>>A>>B ){
        f(A,B);
        cout<<endl;
    }
    return 0;
}
