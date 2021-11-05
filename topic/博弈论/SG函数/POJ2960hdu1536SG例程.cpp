/**
  ���ɶ����ɸ�ʯ�ӣ�˫������ȡ�������ȡ���и���
  ���ǣ�ÿ��ȡ��ʯ�ӵĸ����ܵ����ƣ���һ���������Ϲ涨�������ֵ�ʤ����
*/
#include <iostream>
#include <algorithm>
using namespace std;

int const MAX = 10001; 
int g[MAX];
int S[101];
int stone[101];

//�����Ϸ�����S���������е�sgֵ
//����num��S��size
void calsg(int num){
	g[0] = 0;
	char flag[101];
	int i,j,n;
    for(i=1;i<MAX;i++){
		memset(flag,0,sizeof(flag));
        for(j=0;j<num;j++){
			if ( i - S[j] >= 0 ){ 
				flag[ g[ i - S[j] ] ] = 1;
			}
		}
		for(j=0;;j++)if(!flag[j]) {
			g[i] = j;
			break;
		}
	}
	return;
}

int main(){
	int k=0;
	int cases;//���Եĸ���
	while(cin>>k && k){
		memset(g,-1,MAX);
        int i;
		for(i=0;i<k;i++) cin>>S[i];
		sort(S,S+k);
		calsg(k);

		cin>>cases;
        while(cases--){
			int num;//ʯ�Ӷ���
			cin>>num;
			cin>>stone[0];
			int ans = g[stone[0]];
            for(i=1;i<num;i++) {
				cin>>stone[i];
				ans ^= g[stone[i]];
			}
			if ( ans ) cout<<'W';
			else       cout<<'L';
		}
		cout<<endl;
	}
	return 0;
}
