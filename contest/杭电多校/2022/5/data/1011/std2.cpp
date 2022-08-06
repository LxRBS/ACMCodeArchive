#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
string op[]={"2134","1342","2413"};
void calc(string &s,char c){
	for(int i=0;i<4;i++)s[i]=op[c-'a'][s[i]-'1'];
}
int main(){
	int T;cin>>T;
	for(int tc=1;tc<=T;tc++){
		string s,t,p1,p2;
		cin>>s>>t;
		p1=p2="1234";
		int n=s.length(),m=t.length();
		for(int i=0;i<n;i++)calc(p1,s[i]);
		for(int i=0;i<m;i++)calc(p2,t[i]);
		if(p1==p2)cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	return 0;
}

