/**
    �������Բ�ཻ�����
*/
#include <bits/stdc++.h>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-8;
inline int sign(double x){
    if(x>EPS) return 1;
    return x<-EPS?-1:0;
}

inline double myasin(double x){
    if(x>1.0) x=1.0;
    if(x<-1.0) x=-1.0;
    return asin(x);
}

//���һԪ���η��̸������ظ���������С����ǰ������ں�
inline int root(double a,double b,double c,double&x1,double&x2){
    double delta = b*b-4.0*a*c;
    int tmp = sign(delta);

    if(tmp<0) return 0;

    if(0==tmp){
        x1 = x2 = -b / ( a + a );
        return 1;
    }

    delta = sqrt(delta);
    x1 = ( -b - (delta) ) / ( a + a );
    x2 = ( -b + (delta) ) / ( a + a );
    return 2;
}

//������ݽṹ
struct point_t{
	double x,y;
	point_t(int a=0,int b=0):x(a),y(b){}
};

//���OA��OB
double cross(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
double dot(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * xob + yob * yoa;
}
double dist2(point_t const&A,point_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return x*x+y*y;
}
//���ط���ǣ���(-180,180]֮�䣬O��A��B������ͬ
inline double getAngle(point_t const&O,point_t const&A,point_t const&B){
    double area = cross(O,A,B)*0.5;
    double ddot = dot(O,A,B);
    if(0==sign(area)){//OAB��һ��ֱ��
        if(sign(ddot)>0) return 0.0;
        return PI;
    }

    double OA = sqrt(dist2(O,A));
    double OB = sqrt(dist2(O,B));

    //������Ƕ�
    double theta = myasin(area*2.0/(OA*OB));
    if(sign(ddot)>=0)return theta;//˵������ǣ�ֱ�ӷ���
    //���Ķ۽�
    if(sign(area)>0) return PI-theta;
    //���Ķ۽�
    return -theta - PI;
}

//��������OAB��ԲO�ཻ�����������A��B��Ȼ��ͬ
//��AB��Բ�Ľ���ΪP����P=(1-t)A+tB����|OP|^2=radius^2
//���Խ�һ������t��һԪ���η���
//[t(B.x-A.x)+(A.x-O.x)]^2+[t(B.y-A.y)+(A.y-O.y)]^2 = radius^2
//ע���������������
double triangleAndCircleArea(point_t const&O,point_t const&A,point_t const&B,double radius){
    double area = cross(O,A,B)*0.5;
    int s = sign(area);
    if(0==s) return 0.0;

    double a = (B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y);
    double b = 2.0*( (B.x-A.x)*(A.x-O.x)+(B.y-A.y)*(A.y-O.y) );
    double c = (A.x-O.x)*(A.x-O.x)+(A.y-O.y)*(A.y-O.y)-radius*radius;

    double x1,x2;
    int cnt = root(a,b,c,x1,x2);

    double OA = sqrt(dist2(O,A));
    double OB = sqrt(dist2(O,B));
    double AB = sqrt(dist2(A,B));

    //ֱ��A��B��Բ�޽��㣬�������������ֻ��1������Ҳ���������
    if(0==cnt||1==cnt){
        double theta = getAngle(O,A,B);
        return 0.5*radius*radius*theta;
    }

    /**��������[0,1]���佫����ʵ����Ϊ���Σ�һ����6�ֿ�����*/
    //������������[0,1]��Χ�ڣ�����ͬһ�ߣ������������
    if( sign(x2) < 0 || sign(x1-1.0) > 0 ){
        double theta = myasin(area*2.0/(OA*OB));
        return 0.5*radius*radius*theta;
    }

    //������������[0,1]��Χ�ڣ��Ҹ���һ�ߣ�˵��A��B��Բ��
    if( sign(x1) < 0 && sign(x2-1.0) > 0 ){
        return area;
    }

    //˵��x1���ڡ�x2�ڷ�Χ�ڣ���ӦA��Բ�ڡ�B��Բ������
    //��ʱ�����������OAP������
    if( sign(x1) < 0 && sign(x2) >= 0 && sign(x2-1.0) <= 0 ){
        double theta = myasin(area*(1.0-x2)*2.0/(radius*OB));
        return area*x2 + 0.5*radius*radius*theta;
    }

    //˵��x2���ڡ�x1�ڷ�Χ�ڣ���ӦB��Բ�ڡ�A��Բ������
    //��ʱ�����������OPB������
    if( sign(x1) >= 0 && sign(x1-1.0) <= 0 && sign(x2-1.0) > 0 ){
        double theta = myasin(area*x1*2.0/(radius*OA));
        return area * (1.0-x1) + 0.5 * radius * radius * theta;
    }

    //x1��x2����A��B֮�䣬��ʱ������������μ�һ��������
    double theta1 = myasin(area*x1*2.0/(radius*OA));
    double theta2 = myasin(area*(1.0-x2)*2.0/(radius*OB));
    return area*(x2-x1) + 0.5*radius*radius*(theta1+theta2);
}

point_t O,P[100100];
double Radius;
point_t T,Speed;
double H;
int main(){
    //freopen("1.txt","r",stdin);
    while(EOF!=scanf("%lf%lf%lf%lf%lf%lf",&T.x,&T.y,&H,&Speed.x,&Speed.y,&Radius)){
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%lf%lf",&P[i].x,&P[i].y);
        P[n] = P[0];

        //������ʱ��
        double t = sqrt(H/5.0);
        //��Բ��
        O.x = T.x + Speed.x * t;
        O.y = T.y + Speed.y * t;

        double ans = 0.0;
        for(int i=0;i<n;++i){
            ans += triangleAndCircleArea(O,P[i],P[i+1],Radius);
        }
        printf("%.2f\n",fabs(ans));
    }
}
