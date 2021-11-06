/**
    三种类型的点集，要求从中选3个点，类型各不相同
    且三角形面积最大
    
    对三种类型分别做凸包，然后暴力
    注意要用不严格凸包，严格凸包WA
    要看看严格凸包的模板是不是有问题，还是原理上就是不严格凸包
    最后发现严格凸包中爆longlong了。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

inline llt ABS(llt x){return x>=0?x:-x;}

struct point_t{
    llt x,y;
    point_t(llt a=0,llt b=0):x(a),y(b){}
}P[3][3010];

llt cross(point_t const&O,point_t const&A,point_t const&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

//A如果比B更靠下更靠左返回真
bool isLowLeft(point_t const&A,point_t const&B){
	return A.y < B.y || ( A.y == B.y && A.x < B.x );
}

//按对于pO的极角排序，极角相等的距离近的排在前面
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
    llt t = cross(*pO,A,B);
	if ( t ) return t > (llt)0;

	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 < a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 < a2;
}

//Graham求凸包，结果当中有共线点，起点总是最下最左点
int Graham(point_t P[],int n){
    if ( 1 == n ) return 1;

	//寻找最下最左点
	point_t *p = min_element(P,P+n,isLowLeft);

	//交换
	swap(*p,P[0]);

	if ( 2 == n ) return 2;

	//按极角排序，极角相等，距离近的排在前面
	pO = P;
	sort(P+1,P+n,comp4Graham);

	//将最后一条边的共线点倒过来排序
	int k = n - 1;
	while( k && 0LL == cross(P[0],P[n-1],P[--k]) );//k为0说明所有点共线
	if ( k ) for(int i=k+1;i<(n+k+1)>>1;++i) swap(P[i],P[n+k-i]);

	//真正的Graham循环
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) < (llt)0 )
			--top;
		P[top++] = P[i];
	}
	return top;
}

int N;
int R,G,B;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        R = G = B = 0;
        for(int x,y,i=0;i<N;++i){
            x = getInt();
            y = getInt();
            switch(getInt()){
            case 0:P[0][R].x=x,P[0][R++].y=y;break;
            case 1:P[1][G].x=x,P[1][G++].y=y;break;
            case 2:P[2][B].x=x,P[2][B++].y=y;break;
            }
        }
        if(0==R||0==G||0==B){
            puts("0.0");
            continue;
        }

        //求凸包
        R = Graham(P[0],R);
        G = Graham(P[1],G);
        B = Graham(P[2],B);

        llt ans = 0LL;
        for(int i=0;i<R;++i)for(int j=0;j<G;++j)for(int k=0;k<B;++k){
            ans = max(ans, ABS(cross(P[0][i],P[1][j],P[2][k])));
        }
        printf("%I64d.",ans>>1);
        puts(ans&1?"5":"0");
    }
    return 0;
}
