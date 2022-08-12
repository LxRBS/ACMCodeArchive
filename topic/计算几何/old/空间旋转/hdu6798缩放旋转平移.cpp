/**
   ���������ٶȣ��ٸ���һ����������
   �ʷ�����k����ײ��ʱ��
   �����ԣ�������ײ����Ҫ���㷴����ֱ�ӻ�ֱ�߼���
   ���ٶ�ʸ���任Ϊex�����������ϵĵ�λ����
   ����������ͬ���ı任
   ���ֻ�迴x������������ƽ��ֱ����k��������������꼴��
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

double const EPS = 1E-8;
double const PI = acos(-1.0);
inline double is0(double x){return -EPS<=x&&x<=EPS;}
inline double isEq(double x,double y){return is0(x-y);}

struct matrix_t{//�任����
    double data[3][3];
    matrix_t(){memset(data,0,sizeof(data));}
    void disp(FILE*fp=stdout)const{
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                fprintf(fp,"%10.3f",data[i][j]);
            }
            fprintf(fp,"\n");
        }
    }

    //����һ�����ž���,sΪ����ϵ��
    static matrix_t scale(double s){
        matrix_t m;
        m.data[0][0] = s; m.data[1][1] = s;
        m.data[2][2] = 1.0;
        return m;
    }

    //����һ����ת������ת�Ƕ�Ϊtheta
    //ע��������ϵ��ת�����sin�ĸ���λ������ͨ��ת��һ��
    static matrix_t rotate(double theta){
        matrix_t m;
        m.data[0][0] = m.data[1][1] = cos(theta);
        m.data[1][0] = -(m.data[0][1] = sin(theta));
        m.data[2][2] = 1.0;
        return m;
    }

    //����һ��ƽ�ƾ���
    static matrix_t translate(double dx,double dy){
        matrix_t m;
        m.data[0][0] = m.data[1][1] = m.data[2][2] = 1.0;
        m.data[0][2] = -dx;m.data[1][2] = -dy;
        return m;
    }

    friend const matrix_t operator * (const matrix_t&,const matrix_t&);
    //����һ�����š���ת��ƽ�ƾ���ע��˳��
    static matrix_t transform(double s,double theta,double dx,double dy){
        matrix_t m1 = matrix_t::scale(s);
        matrix_t m2 = matrix_t::rotate(theta);
        matrix_t m3 = matrix_t::translate(dx,dy);
        return m1*m2*m3;
    }
};

struct point64f_t{
    double x,y;
    void disp(FILE*fp=stdout)const{
        fprintf(fp,"(%.3f,%.3f)\n",x,y);
    }
};

const matrix_t operator * (const matrix_t&lhs,const matrix_t&rhs){
    matrix_t ret;
    for(int i=0;i<3;++i)for(int j=0;j<3;++j){
        for(int k=0;k<3;++k){
            ret.data[i][j] += lhs.data[i][k]*rhs.data[k][j];
        }
    }
    return ret;
}

const point64f_t operator * (const matrix_t&lhs,const point64f_t&rhs){
    point64f_t ret;
    ret.x = lhs.data[0][0] * rhs.x + lhs.data[0][1] * rhs.y + lhs.data[0][2];
    ret.y = lhs.data[1][0] * rhs.x + lhs.data[1][1] * rhs.y + lhs.data[1][2];
    double tmp = lhs.data[2][0] * rhs.x + lhs.data[2][1] * rhs.y + lhs.data[2][2];
    assert(isEq(tmp,1.0));
    ret.x /= tmp; ret.y /= tmp;
    return ret;
}

struct line_t{
    double a,b,c;
    line_t():a(0),b(0),c(0){}
    line_t(point64f_t const&A,point64f_t const&B){
        a = A.y - B.y;
        b = B.x - A.x;
        c = A.x * B.y - B.x * A.y;
        if(is0(a)){
            a = 0.0;c /= b;b = 1.0;
        }else{
           b /= a;c /= a;a = 1.0;
        }

        if(is0(a)) a=0.0;
        if(is0(b)) b=0.0;
        if(is0(c)) c=0.0;
    }
    //�ط��߷����ƶ�d���γɵ���ֱ��
    line_t move(double d)const{
        line_t ret;
        ret.a = this->a;
        ret.b = this->b;
        ret.c = sqrt(a*a+b*b)*d + this->c;
        return ret;
    }
};

point64f_t A,B,C;
point64f_t Ap,Bp,Cp;

//����ֱ���壬����x������ĵ�һ�������빫��
//�������a���淵��
int f(line_t const&one,double dist,double a[]){
    if(is0(one.a)) return 0;

    line_t one2 = one.move(dist);
    double x0 = -one.c/one.a;
    double x1 = -one2.c/one2.a;
    if(x0>x1) swap(x0,x1);
    double d = x1-x0;
    int n = (int)(-x0/d);
    double x = x0 + n * d;
    while(x>d) x-=d;
    while(x<0) x+=d;
    a[0] = x;a[1] = d;
    return 1;
}

//[0,x]�Ƿ����k������
bool check(double x,double a[][2],int t,int k){
    int cnt = 0;
    for(int i=0;i<t;++i){
        cnt += (x-a[i][0])/a[i][1] + 1;
    }
    return cnt < k;
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int k,nofkase = getInt();
    double L,x,y,vx,vy;
    while(nofkase--){
        L = getInt();
        x = getInt(); y = getInt();
        vx = getInt();vy = getInt();
        k = getInt();

        //�����ε�������
        A.x = 0.0, A.y = L*sqrt(3)*0.5;
        B.x = L*0.5,B.y = 0;
        C.x = -B.x,C.y = 0;

        //������һ������仯������㶨Ϊԭ�㣬�ٶȶ�Ϊex
        double theta = atan2(vy, vx);
        double s = sqrt(vx*vx+vy*vy);

        //��ȡ�任����
        matrix_t matrix = matrix_t::transform(1.0/s,theta,x,y);

        //��ȡ�任���������
        Ap = matrix * A;
        Bp = matrix * B;
        Cp = matrix * C;

        double vec[3][2];
        int t = 0;
        double d = L*sqrt(3)*0.5/s;

        //������ֱ���壬�Լ���㡢����
        t += f(line_t(Ap,Bp), d, vec[t]);
        t += f(line_t(Bp,Cp), d, vec[t]);
        t += f(line_t(Ap,Cp), d, vec[t]);

        //�����������ұ߽����ȷ����
        double mid,left = EPS, right = 1.3E8;
        do{//�������������ʹ�ý���С�ڵ���k
            double mid = (left+right)*0.5;
            if(check(mid,vec,t,k)) left = mid + EPS;
            else right = mid - EPS;
        }while(left<=right);//left���Ǵ�
        printf("%.12f\n",left);
    }
    return 0;
}