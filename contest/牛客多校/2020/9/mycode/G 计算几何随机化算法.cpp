/**
    ����һ��͹�����(70000����)��һ��ֱ�ߡ�
    ͹�������ԭ�������תһ���Ƕȣ���ֱ����͹������ڵ��߶γ��ȳ���L�ĸ����Ƕ���
    L���ȸ�����Ҫ��С�����4λ
    ��ֱ֤���������й����߶�
    ���ȣ���ת���������תֱ���ǵȼ۵ġ������תֱ�߼��ɡ�
    ��תֱ�ߵĻ�������ֱ����ת�䷨����������Ҫע��ֱ�߹�ԭ����������Ҫ���⴦��
    1. ʹ��MonteCarlo�㷨����ֱ�������תһ���Ƕȣ�����߶��Ƿ񳬹�L
      ����������ظ�100��μ��ɡ�ֱ����ֱ���������ཻ��ҪO(N)��
      ���Ƕ���ε�ÿ�����ܹ�������ֱ�߽Ƕ��������仯�ģ�
      ��˶���ת������Ƕȿ�����logʱ��������㡣
      ����һ�������������䷶Χ������Ƚ��鷳
    2. ֱ�ӽ�360�ȷֳ�100��ݣ���������100����ֱ�������ν�������������������
      ��Ϊ�������ཻ�ı߿϶��������仯�ģ�����ֱ���󽻵㷽��Ҫ�򵥺ܶ�

    �������һ���Ƕȵõ���ʼֱ�ߣ�Ȼ��O(N)����ཻ�������ߵı�ţ�
    Ȼ���ظ�1400���(���ǹ۲��˴���������ʱ��ó�����������)��
    ÿ�νǶ�����һ��delta������ཻ�߶��Ƿ����������
    �����������
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
    point64f_t rotate(double theta)const{//������ԭ����ʱ����תtheta�õ��ĵ�
        return point64f_t(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta));
    }
    //������p�ľ���
    double dist(point64f_t const&p){double xx=this->x-p.x,yy=this->y-p.y;return sqrt(xx*xx+yy*yy);}
    bool operator < (point64f_t const&rhs){
        return isLE(this->x,rhs.x) || (isEq(this->x,rhs.x)&&isLE(this->y,rhs.y));
    }
    bool operator == (point64f_t const&rhs){
        return isEq(this->x,rhs.x) && isEq(this->y,rhs.y);
    }
}P[70010];

//�жϵ�p�Ƿ����߶�AB��
inline bool isIn(point64f_t const&p,point64f_t const&A,point64f_t const&B){
    return isLE(p.x,max(A.x,B.x)) && isLE(min(A.x,B.x),p.x)
        && isLE(p.y,max(A.y,B.y)) && isLE(min(A.y,B.y),p.y);
}

struct line_t{
    double a,b,c;
    line_t(double aa=0.0,double bb=0.0,double cc=0.0):a(aa),b(bb),c(cc){}
    //��A/B�����ֱ��
    line_t(point64f_t const&A,point64f_t const&B){
        a = A.y - B.y;
        b = B.x - A.x;
        c = A.x * B.y - A.y * B.x;
    }
    //ֱ���󽻵㣬��֤��
    point64f_t inter(line_t const&rhs)const{
        double x = b * rhs.c - rhs.b * c;
        double y = c * rhs.a - a * rhs.c;
        double t = a * rhs.b - b * rhs.a;
        return point64f_t(x/t,y/t);
    }
}Lines[70010];

//����һ��ֱ�ߣ�����H���Ҵ�ֱ��OH
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

//��ԭ�㵽ֱ��AB�Ĵ���
point64f_t get(point64f_t const&A,point64f_t const&B){
    if(isEq(A.x,B.x)){
        return point64f_t(A.x,0.);
    }
    if(isEq(A.y,B.y)){
        return point64f_t(0.,A.y);
    }
    //б��
    double k = (B.y-A.y) / (B.x-A.x);
    k = -1.0 / k;
    return line_t(A,B).inter(line_t(k,-1.0,0.0));
}

//ֱ�����idx���ߵĽ���
bool inter(line_t const&line,int idx,point64f_t&ans){
    ans = line.inter(Lines[idx]);
    //�жϽ����Ƿ����߶���
    return isIn(ans,P[idx],P[idx+1]);
}

int N;
double L;

//�ҵ�ֱ��line�������ཻ�������ߵı�ţ����4��
int bian2(line_t const&line,int a[]){
    int idx1 = 0;
    point64f_t tp;
    while(idx1<N){
        if(!inter(line,idx1,tp)) ++idx1;
        break;
    }

    int ret = 0;
    //line���idx1�����ཻ
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


//������תtheta���γɵ�ֱ�ߣ��Ƿ��������,cnt�϶���2
bool isOK(point64f_t const&chuizu,double theta,int a[],int cnt){
    //�����γ�ֱ��
    line_t line = chuizhi(chuizu.rotate(theta));
    //�ж�ֱ���Ƿ���a����ı��ཻ
    point64f_t p[2];
    int idx = a[0];
    //һ���н���
    while(!inter(line,idx,p[0])) idx = (idx+1)%N;
    int idx2 = a[1];
    if(idx2==idx) idx2 = (idx2+1)%N;
    while(!inter(line,idx2,p[1])) idx2 = (idx2+1)%N;

    a[0] = idx, a[1] = idx2;
    //cout<<"dist: "<<p[0].dist(p[1])<<endl;
    return ! isLE(p[0].dist(p[1]),L);
}

//��ԭ���ֱ�ߣ���תangle���Ƿ��������
bool isOK(double angle,int a[]){
    line_t line(sin(angle),-cos(angle),0.0);
    //�ж�ֱ���Ƿ���a����ı��ཻ
    point64f_t p[2];
    int idx = a[0];
    //һ���н���
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

    //�����ʼ��һ����ʼ�ĽǶ�
    double start_angle = distribution(generator) * 2.0 * PI;
    int const LIMIT = 14000000;//��������
    double const DELTA = PI / LIMIT;

    int ans = 0;
    int bidx[4];
    int bcnt = 0;

    if(is0(chuizu.x)&&is0(chuizu.y)){//���ֱ�߹�ԭ��
        //��������ʼ����
        line_t start_line2(sin(start_angle),-cos(start_angle),0.0);
        point64f_t ptmp;
        for(int i=0;i<N;++i){
            if(inter(start_line2,i,ptmp)){
                bidx[bcnt++] = i;
            }
        }
        zhengli(bidx,bcnt);

        //��ת180�ȣ�������
        for(int i=0;i<LIMIT;++i){
            if(isOK(start_angle,bidx)){
                ++ans;
            }
            start_angle += DELTA;
        }
        printf("%.4f\n",(double)ans/LIMIT);
        return 0;
    }

    //��ֱͨ�ߣ�������Ȼ��һ��
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
