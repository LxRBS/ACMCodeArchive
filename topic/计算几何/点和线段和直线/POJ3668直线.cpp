//射影几何实现
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int gcd(int a,int b){
    int r;
	while( r = a % b ){
		a = b;
		b = r;
	}
	return b;
}

struct proj_t{
	int x;
	int y;
	int t;
	proj_t(int a=0.0,int b=0.0,int c=0.0)
		:x(a),y(b),t(c){}
	//归一化
	inline void norm(){
		if ( 0 == y ){
			x = 1;return;
		}
		if ( 0 == x ){
			y = 1;return;
		}
		int g = gcd(x,y);
		x /= g;
		y /= g;
		if ( x < 0 ){
			x = -x;
			y = -y;
		}
		//t不需要，因为这道题不用
	}
};

//叉积
proj_t operator * (proj_t const&l,proj_t const&r){
	return proj_t(l.y * r.t - r.y * l.t, r.x * l.t - l.x * r.t, l.x * r.y - r.x * l.y);
}

//随便定义一个小于
bool operator < (proj_t const&l,proj_t const&r){
    return l.x < r.x || ( l.x==r.x && l.y < r.y );     
}

bool cmp(proj_t const&l,proj_t const&r){
    return 0 == l.x * r.y - r.x * l.y;
}

proj_t P[203];
proj_t L[20000];

int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			P[i].t = 1;
		}
		P[n] = P[0];

		int ans = 0;
		int k = 0;
		for(int i=0;i<n-1;++i)for(int j=i+1;j<n;++j){
			L[k] = P[i] * P[j]; 
			L[k].norm();
			++k;
		}

		sort(L,L+k);
		proj_t* it = unique(L,L+k,cmp);

		printf("%d\n",it-L);
	}
	return 0;
}
