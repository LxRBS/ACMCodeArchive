//������������������
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;


void f(string const&a,string const&b){
    if ( a.empty() ) return;
    //a�ĵ�һ����ĸΪ��ǰ����
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
