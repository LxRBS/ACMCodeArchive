/**
    给定一个多边形，指定一个目标点，按如下规则行进：
    1. 从当前点，沿目标点方向直接走，直到撞墙
    2. 撞墙以后，向更靠近目标点的方向沿墙走，直到离开这堵墙或者刚好垂直
    3. 如果垂直或者两堵墙都走不动，则失败
    问，在多边形中是否能找到一个目标点，使得所有点都能够到达
    1000个点
    首先如果是凸多边形必然OK
    其次假设只验证多边形的交点即可，没有证明。
    对每个点进行验证，对每条边：
    如果是面对，说明要离开这条边，不用管
    如果是背对，说明要沿边走。如果垂足在边上，则失败
    否则必然走到其中一个顶点，验证顶点是否为死角即可
*/
#include<bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct point_t{
    int x,y;
    point_t(int a=0,int b=0):x(a),y(b){}
}P[1010], NormVec[1010];

int cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}
int dot(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}
int N;
bool read(){
    while(1!=scanf("%d",&N)) return false;
    for(int i=0;i<N;++i){
        P[i].x = getUnsigned();
        P[i].y = getUnsigned();
    }
    P[N] = P[0];
    return true;
}

//判断是否为凸的
bool isConvex(point_t const p[],int n){
    int status = 0;

    for(int tmp,i=1;i<n;++i){
        tmp = cross(p[i-1],p[i],p[i+1]);
        if(tmp<0) status |= 2;
        else if(tmp>0) status |= 1;
        if(status==3) return false;
    }
    //题目保证是顺时针方向
    if(status==1) throw runtime_error("XXXXX");
    return true;
}

//检查第idx个顶点是否能作为目标
bool check(int idx){
    //对每条边判断其是否面对还是背对
    //如果背对的话，判断其垂足是否恰好在线段上
    //如果垂足不在线段上，判断其最后落脚点是哪个顶点
    int cnt[1010] = {0};
    for(int i=0;i<N;++i)if(i!=idx&&i+1!=idx){
        //首先计算叉积
        int tmp = cross(P[i],P[i+1],P[idx]);
        if(tmp<0){//面对，此时会离开这条边，不用再判断
            continue;
        }
        //此时会沿着边走，需要检查
        int d1 = dot(P[i],P[i+1],P[idx]);
        int d2 = dot(P[i+1],P[i],P[idx]);
        if(d1>0&&d2>0){//此时说明垂足在边中间，不行
            return false;
        }
        //判断落脚点
        if(d1<=0){//落脚点在Pi
            if(++cnt[i]>1){//两条边都落在Pi，这是一个死角
                return false;
            }
        }else if(d2<=0){
            if(++cnt[i+1]>1){
                return false;
            }
        }else{
            throw runtime_error("XXXX");
        }
    }
    return true;
}

bool proc(){
    //如果是凸多边形，肯定OK
    if(isConvex(P,N)) return true;

    //生成每条边的法向量，顺时针，法向量始终指向右边
    /*
    for(int i=0;i<N;++i){
        NormVec[i].x = P[i+1].y-P[i].y;
        NormVec[i].y = P[i].x-P[i+1].x;
    }//*/

    //对每个顶点假设其为目标点，进行验证
    for(int i=0;i<N;++i){
        if(check(i)) {
            //printf("%d: (%d, %d)\n",i, P[i].x, P[i].y);
            return true;
        }
    }
    return false;
}
int main(){
    //freopen("1.txt","r",stdin);

    char a[][20] = {"DANGER","SAFETY"};
    while(read()){
        puts(a[proc()?1:0]);
    }
    return 0;
}

