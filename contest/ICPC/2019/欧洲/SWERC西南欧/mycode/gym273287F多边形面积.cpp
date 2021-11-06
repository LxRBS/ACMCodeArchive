/**
    N个简单多边形求面积和
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct point_t{
    llt x,y;
}P[110];

llt cross(point_t const&O,point_t const&A,point_t const&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

int N,M;
int main(){
    //freopen("1.txt","r",stdin);

    N = getUnsigned();
    llt ans = 0;
    while(N--){
        M = getUnsigned();
        for(int i=0;i<M;++i){
            P[i].x = getUnsigned();
            P[i].y = getUnsigned();
        }

        llt tmp = 0;
        for(int i=1;i<=M-2;++i){
            tmp += cross(P[0],P[i],P[i+1]);
        }

        ans += (tmp>=0?tmp:-tmp);
    }
    cout<<(ans>>1)<<endl;

    return 0;
}

