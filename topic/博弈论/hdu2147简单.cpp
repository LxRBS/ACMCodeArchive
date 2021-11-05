#include <iostream>
using namespace std;
int main(){
	int n,m;
	while ( cin>>n>>m && ( n!=0 && m!=0 ) )
	{
		int flag = 0;
		if ( n > m ){
            flag = ( m - 1 ) % 2;
			flag += ( n - m ) % 2;
		}else if( n < m ){
            flag = ( n - 1 ) % 2;
			flag += ( m - n ) % 2;
		}else{
            flag = ( m - 1 ) % 2;
		}
		if ( flag ) cout<<"Wonderful!\n";
		else        cout<<"What a pity!\n";
	}
	return 1;
}
