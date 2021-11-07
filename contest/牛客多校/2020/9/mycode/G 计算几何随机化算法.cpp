/**
    给定一个凸多边形(70000条边)和一条直线。
    凸多边形绕原点随机旋转一个角度，问直线在凸多边形内的线段长度超过L的概率是多少
    L事先给定，要求小数点后4位
    保证直线与多边形有公共线段
    首先，旋转多边形与旋转直线是等价的。随机旋转直线即可。
    旋转直线的话，可以直接旋转其法向量，不过要注意直线过原点的情况，需要特殊处理
    1. 使用MonteCarlo算法，将直线随机旋转一个角度，检查线段是否超过L
      将这个操作重复100万次即可。直接求直线与多边形相交需要O(N)，
      但是多边形的每条边能够交到的直线角度是连续变化的，
      因此对旋转的任意角度可以在log时间求出交点。
      不过一条边有两个区间范围，处理比较麻烦
    2. 直接将360度分成100万份，依次求这100万条直线与多边形交的情况，计数相除即可
      因为与多边形相交的边肯定是连续变化的，所以直线求交点方面要简单很多

    首先随机一个角度得到初始直线，然后O(N)求出相交的两条边的编号，
    然后重复1400万次(这是观察了次数与评测时间得出的总数上限)，
    每次角度增加一个delta，检查相交线段是否符合条件，
    最后计数相除。
*/
#include <bits/stdc++.h>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-9;
inline int sgn(double x){return x>EPS?+1:(x<-EPS?-1:0);}
inline bool is0(double x){return 0==sgn(x);}
inline bool isEq(double x,double y){return is0(x-y);}
inline bool isLE(double x,double y){return sgn(x-y)<=0;}

struct point64f_t{
    double x,y;
    point64f_t(double a=0.,double b=0.):x(a),y(b){}
    void disp(FILE*fp=stdout)const{fprintf(fp,"(%.3f,%.3f)",x,y);}
    point64f_t rotate(double theta)const{//返回绕原点逆时针旋转theta得到的点
        return point64f_t(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta));
    }
    //返回与p的距离
    double dist(point64f_t const&p){double xx=this->x-p.x,yy=this->y-p.y;return sqrt(xx*xx+yy*yy);}
    bool operator < (point64f_t const&rhs){
        return isLE(this->x,rhs.x) || (isEq(this->x,rhs.x)&&isLE(this->y,rhs.y));
    }
    bool operator == (point64f_t const&rhs){
        return isEq(this->x,rhs.x) && isEq(this->y,rhs.y);
    }
}P[70010];

//判断点p是否在线段AB上
inline bool isIn(point64f_t const&p,point64f_t const&A,point64f_t const&B){
    return isLE(p.x,max(A.x,B.x)) && isLE(min(A.x,B.x),p.x)
        && isLE(p.y,max(A.y,B.y)) && isLE(min(A.y,B.y),p.y);
}

struct line_t{
    double a,b,c;
    line_t(double aa=0.0,double bb=0.0,double cc=0.0):a(aa),b(bb),c(cc){}
    //过A/B两点的直线
    line_t(point64f_t const&A,point64f_t const&B){
        a = A.y - B.y;
        b = B.x - A.x;
        c = A.x * B.y - A.y * B.x;
    }
    //直线求交点，保证有
    point64f_t inter(line_t const&rhs)const{
        double x = b * rhs.c - rhs.b * c;
        double y = c * rhs.a - a * rhs.c;
        double t = a * rhs.b - b * rhs.a;
        return point64f_t(x/t,y/t);
    }
}Lines[70010];

//返回一条直线，过点H，且垂直于OH
line_t chuizhi(point64f_t const&H){
    if(is0(H.x)){
        return line_t(0.0,1.0,-H.y);
    }
    if(is0(H.y)){
        return line_t(1.0,0.0,-H.x);
    }
    double k = -H.x / H.y;
    return line_t(k,-1.0,H.y-k*H.x);
}

//求原点到直线AB的垂足
point64f_t get(point64f_t const&A,point64f_t const&B){
    if(isEq(A.x,B.x)){
        return point64f_t(A.x,0.);
    }
    if(isEq(A.y,B.y)){
        return point64f_t(0.,A.y);
    }
    //斜率
    double k = (B.y-A.y) / (B.x-A.x);
    k = -1.0 / k;
    return line_t(A,B).inter(line_t(k,-1.0,0.0));
}

//直线与第idx条边的交点
bool inter(line_t const&line,int idx,point64f_t&ans){
    ans = line.inter(Lines[idx]);
    //判断交点是否在线段内
    return isIn(ans,P[idx],P[idx+1]);
}

int N;
double L;

//找到直线line与多边形相交的两条边的编号，最多4个
int bian2(line_t const&line,int a[]){
    int idx1 = 0;
    point64f_t tp;
    while(idx1<N){
        if(!inter(line,idx1,tp)) ++idx1;
        break;
    }

    int ret = 0;
    //line与第idx1条边相交
    if(tp==P[idx1]){
        a[0] = (idx1-1+N)%N;
        a[1] = idx1;
        ret = 2;
    }else if(tp==P[idx1+1]){
        a[0] = idx1;
        a[1] = (idx1 + 1)%N;
        ret = 2;
    }else{
        a[0] = idx1;
        ret = 1;
    }
    ++idx1;
    while(idx1<N){
        if(!inter(line,idx1,tp)) ++idx1;
        break;
    }
    if(tp==P[idx1]){
        a[ret++] = (idx1-1+N)%N;
        a[ret++] = idx1;
    }else if(tp==P[idx1+1]){
        a[ret++] = idx1;
        a[ret++] = (idx1 + 1)%N;
    }else{
        a[ret++] = idx1;
    }
    sort(a,a+ret);
    ret = unique(a,a+ret) - a;
    return ret;
}

int zhengli(int a[],int cnt){
    if(cnt==2) return 2;
    if(3==cnt){
        if(a[0]+1==a[1]){
            a[1] = a[2];
            return 2;
        }
        if(a[1]+1==a[2]){
            return 2;
        }
        if(a[0]==0&&a[2]==N-1){
            a[0] = a[1];
            a[1] = N-1;
            return 2;
        }
    }
    if(4==cnt){
        if(a[0]==0&&a[3]==N-1){
            a[0]=a[1];
            a[2]=N-1;
            return 2;
        }
        a[1] = a[2];
        return 2;
    }
    throw runtime_error("XXXXXXXX");
}


//垂足旋转theta，形成的直线，是否符合条件,cnt肯定是2
bool isOK(point64f_t const&chuizu,double theta,int a[],int cnt){
    //垂足形成直线
    line_t line = chuizhi(chuizu.rotate(theta));
    //判断直线是否与a里面的边相交
    point64f_t p[2];
    int idx = a[0];
    //一定有交点
    while(!inter(line,idx,p[0])) idx = (idx+1)%N;
    int idx2 = a[1];
    if(idx2==idx) idx2 = (idx2+1)%N;
    while(!inter(line,idx2,p[1])) idx2 = (idx2+1)%N;

    a[0] = idx, a[1] = idx2;
    //cout<<"dist: "<<p[0].dist(p[1])<<endl;
    return ! isLE(p[0].dist(p[1]),L);
}

//过原点的直线，旋转angle，是否符合条件
bool isOK(double angle,int a[]){
    line_t line(sin(angle),-cos(angle),0.0);
    //判断直线是否与a里面的边相交
    point64f_t p[2];
    int idx = a[0];
    //一定有交点
    while(!inter(line,idx,p[0])) idx = (idx+1)%N;
    int idx2 = a[1];
    if(idx2==idx) idx2 = (idx2+1)%N;
    while(!inter(line,idx2,p[1])) idx2 = (idx2+1)%N;

    a[0] = idx, a[1] = idx2;
    //cout<<"dist: "<<p[0].dist(p[1])<<endl;
    return ! isLE(p[0].dist(p[1]),L);
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    scanf("%d",&N);
    for(int i=0;i<N;++i){
        scanf("%lf%lf",&P[i].x,&P[i].y);
    }
    P[N] = P[0];
    for(int i=0;i<N;++i){
        Lines[i] = line_t(P[i],P[i+1]);
    }
    scanf("%lf",&L);
    double x1,y1,x2,y2;
    scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
    point64f_t chuizu = get(point64f_t(x1,y1),point64f_t(x2,y2));

    //srand((unsigned)time(NULL));
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    //随机初始化一个开始的角度
    double start_angle = distribution(generator) * 2.0 * PI;
    int const LIMIT = 14000000;//采样次数
    double const DELTA = PI / LIMIT;

    int ans = 0;
    int bidx[4];
    int bcnt = 0;

    if(is0(chuizu.x)&&is0(chuizu.y)){//如果直线过原点
        //首先求解初始交点
        line_t start_line2(sin(start_angle),-cos(start_angle),0.0);
        point64f_t ptmp;
        for(int i=0;i<N;++i){
            if(inter(start_line2,i,ptmp)){
                bidx[bcnt++] = i;
            }
        }
        zhengli(bidx,bcnt);

        //旋转180度，依次求
        for(int i=0;i<LIMIT;++i){
            if(isOK(start_angle,bidx)){
                ++ans;
            }
            start_angle += DELTA;
        }
        printf("%.4f\n",(double)ans/LIMIT);
        return 0;
    }

    //普通直线，首先仍然求一个
    line_t start_line = chuizhi(chuizu.rotate(start_angle));
    bcnt = bian2(start_line,bidx);
    zhengli(bidx,bcnt);
    double const DELTA2 = DELTA+DELTA;

    for(int i=0;i<LIMIT;++i){
        if(isOK(chuizu,start_angle,bidx,bcnt)){
            ++ans;
        }
        start_angle += DELTA2;
    }
    printf("%.4f\n",(double)ans/LIMIT);
    return 0;
}
