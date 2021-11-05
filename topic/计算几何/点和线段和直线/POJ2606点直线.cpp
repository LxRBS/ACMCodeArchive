//射影几何实现
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

double const EPS = 1E-9;

#define is0(x) ( - EPS <= (x) && (x) <= EPS )
#define isEq(x,y) is0((x)-(y))

struct proj_t{
	double x;
	double y;
	double t;
    proj_t(double a=0.0,double b=0.0,double c=0.0)
		:x(a),y(b),t(c){}
	//归一化
	void norm(){
		if( !is0(t) ){
			x /= t, y /= t, t = 1.0;
			return;
		}
		if ( !is0(y) ){
			x /= y, y = 1.0, t = 0.0;
			return;
		}
		x = 1.0; y = 0.0; t = 0.0;
        return;
	}
};

//叉积
proj_t operator * (proj_t const&l,proj_t const&r){
    return proj_t(l.y * r.t - r.y * l.t, r.x * l.t - l.x * r.t, l.x * r.y - r.x * l.y);
}
//矩阵形式的乘积，也就是点积
double dot(proj_t const&l,proj_t const&r){
	return l.x * r.x + l.y * r.y + l.t * r.t;
}

//随便定义一个小于
bool operator < (proj_t const&l,proj_t const&r){
    if ( !isEq(l.x,r.x) ) return l.x < r.x;
	if ( !isEq(l.y,r.y) ) return l.y < r.y;
	return l.t < r.t;
}

proj_t P[203];

int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		for(int i=0;i<n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			P[i].x = (double)x;
			P[i].y = (double)y;
			P[i].t = 1.0;
		}
		P[n] = P[0];

		map<proj_t,int> m;
		int ans = 0;
		for(int i=0;i<n-1;++i)for(int j=i+1;j<n;++j){
			proj_t line = P[i] * P[j]; 
			line.norm();
			++m[line];
		}

		map<proj_t,int>::iterator it;
		for(it=m.begin();it!=m.end();++it){
			if ( it->second > ans ) ans = it->second;
		}
		
		printf("%d\n",((int)(sqrt((double)(1+ans*8))+1.1))>>1);
	}
	return 0;
}
