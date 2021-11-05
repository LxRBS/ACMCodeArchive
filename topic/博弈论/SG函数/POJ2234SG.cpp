//经典Nim问题，不用解题报告
#include <iostream>
using namespace std;
int main()
{
	int i,k,num,ans,tmp;
	while(cin>>num){
	    cin>>ans;
		for( k=1;k<num;k++ ){
			cin>>tmp;
			ans ^= tmp;
		}
	    if( ans ) cout<<"Yes\n";
		else cout<<"No\n";

	}
    return 1;
}
