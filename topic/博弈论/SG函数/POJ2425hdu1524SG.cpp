#include <iostream>
using namespace std;

int const MAXSIZE = 1001;
char Graph[MAXSIZE][MAXSIZE];
int SG[MAXSIZE];
int n;//全局变量，表示图的尺寸
int sg(int x){
	if ( SG[x] != -1 ) return SG[x];
    int i;
	bool flag[MAXSIZE] = {false};
	for( i=0;i<n;i++ ){
        if ( Graph[x][i] ){
		    if ( SG[i] != -1 ) flag[SG[i]] = true;
			else {
				SG[i] = sg(i);
				flag[SG[i]] = true;
			}
		}
	}
	for(i=0;;i++)if(!flag[i]) return SG[x] = i;
}
int main(){
	while( cin>>n ){
        int i;
		memset(Graph,0,sizeof(Graph));
		memset(SG,-1,sizeof(SG));
		for( i=0;i<n;i++ ){
            int k;
			cin>>k;
			if ( k == 0 ) SG[i] = 0;
			else while( k-- ){
                int a;
				cin>>a;
				Graph[i][a] = 1;
			}
		}
		int m;
		while( cin>>m && m){
            int ans = 0;
			while( m-- ){
				int k;
				cin>>k;
                if ( SG[k] == -1 ) SG[k] = sg(k);
				ans ^= SG[k];

			}
            if ( ans ) cout<<"WIN\n";
		    else       cout<<"LOSE\n";
		}

	}
	return 0;
}
