/*
  给定N个点，问能否构成正N边形

  首先做一个极角排序，然后依次验证
*/
#include <bits/stdc++.h>
using namespace std;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

struct point_t{
    int x,y;
}P[110];
int N;

//叉积OA×OB
int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

int dist2(point_t const&A,point_t const&B){
    int x = A.x - B.x;
    int y = A.y - B.y;
    return x*x+y*y;
}

//判断点l是否比点r更下更左
bool isBottomLeft(point_t const&l,point_t const&r){
	if ( l.y != r.y ) return l.y < r.y;
	return l.x < r.x;
}

//为Graham排序做准备
point_t* pOrigin;
bool is4Graham(point_t const&l,point_t const&r){
	int t = cross(*pOrigin,l,r);
	if ( t ) return t > 0;
	return (l.x-pOrigin->x)*(l.x-pOrigin->x)<(r.x-pOrigin->x)*(r.x-pOrigin->x);
}

bool proc(){
    //求最下最左点
	point_t* t = min_element(P,P+N,isBottomLeft);

	//与0点交换位置
	point_t ptmp(*t);
	*t = P[0];
	P[0] = ptmp;

	//相对于0点排序
	pOrigin = P;
	sort(P+1,P+N,is4Graham);

	int tmp = dist2(P[N-1],P[0]);
	//依次计算距离是否相等
	for(int i=1;i<N;++i){
        if(dist2(P[i-1],P[i])!=tmp){
            return false;
        }
	}
	//依次计算角度是否相等
	tmp = cross(P[N-2],P[N-1],P[0]);
	if(cross(P[N-1],P[0],P[1])!=tmp)return false;
	for(int i=2;i<N;++i)if(cross(P[i-2],P[i-1],P[i])!=tmp) return false;
	return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=0;i<N;++i)P[i].x=getInt(),P[i].y=getInt();

        printf(proc()?"YES\n":"NO\n");
    }
    return 0;
}

