//检查圆括号和方括号是否匹配，标准的栈的应用

#include <string>
#include <stack>
#include <iostream>
using namespace std;

bool f(string const&s){
    stack<char> st;
    for(string::const_iterator it=s.begin();it!=s.end();++it){
        if ( '(' == *it || '[' == *it ) st.push(*it);
        else if ( ')' == *it ){
            if ( st.empty() || '(' != st.top() ) return false;
            st.pop();
        }else{
            if ( st.empty() || '[' != st.top() ) return false;
            st.pop();
        }
    }
    return st.empty();
}

int main(){
    int nofkase;
    cin>>nofkase;
    string s;
    getline(cin,s);
    while(nofkase--){
        getline(cin,s);
        cout<<(f(s)?"Yes":"No")<<endl;
    }
    return 0;
}
