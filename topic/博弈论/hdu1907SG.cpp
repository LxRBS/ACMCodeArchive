#include <iostream>
using namespace std;
int main()
{
	int N;
	cin>>N;
	int i,k,num,ans;
	int pile[50];
	for( i=0;i<N;i++ ){
		bool flag = true;
		cin>>num;
		cin>>ans;
		if ( ans != 1 ) flag = false; 
		for( k=1;k<num;k++ ){
			cin>>pile[k];
			ans ^= pile[k];
			if ( pile[k] != 1 ) flag = false;
		}
		if ( flag ) if( ans ) cout<<"Brother\n";
		            else cout<<"John\n";
		else if ( ans )  cout<<"John\n";
		     else cout<<"Brother\n";
	}
    return 1;
}
