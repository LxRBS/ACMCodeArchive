/**
    һ���������������Σ����������������㣬�������̶���ͬһ���㣬
    �����������������¾�ֹ������������������ĸ߶�
    ���������Լ������α߳���֪
    ������Ҫ���������������һ���Ŀ��Է�Ϊ�������
    ����ֻ��1�������á�ֻ��2�������ã�3��ȫ����
    ����������������Լ��ĸ���ȫ������һ�鼴�ɣ���Ϊ��Ȼ����ֻ��һ�����
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

#define pb push_back

typedef double Real;
typedef long long llt;

inline void output(Real a, Real b, Real c){
    //printf("%.15lf %.15lf %.15lf\n",a,b,c);
    cout<<fixed<<setprecision(15)<<a<<" "<<b<<" "<<c<<endl;
}

const Real EPS = 1E-8;
const Real PI = acos((Real)-1.0);
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0==sgn(x);}
inline bool isEq(Real x, Real y){return is0(x-y);}
inline Real myacos(Real x){
    if(sgn(x-1)>0) x=1.0;
    else if(sgn(x+1)<0)x=-1.0;
    return acos(x);
}
inline Real myasin(Real x){
    if(sgn(x-1)>0) x=1.0;
    else if(sgn(x+1)<0)x=-1.0;
    return asin(x);
}

struct Point{
    Real x, y, z;
    Point(Real a=0,Real b=0,Real c=0):x(a),y(b),z(c){}
    Real norm()const{return x*x+y*y+z*z;}
    Real dist(const Point&p)const{
        Real x = this->x - p.x;
        Real y = this->y - p.y;
        Real z = this->z - p.z;
        return sqrt(x*x+y*y+z*z);
    }
    void output(ostream&out=cout)const{
        out<<fixed<<setprecision(2)<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
}A, B, C, O, D;

const Point operator - (const Point&lhs, const Point&rhs){
    return Point(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

Real dot(const Point&O,const Point&A,const Point&B){
    Real xoa = A.x - O.x;
    Real xob = B.x - O.x;
    Real yoa = A.y - O.y;
    Real yob = B.y - O.y;
    Real zoa = A.z - O.z;
    Real zob = B.z - O.z;
    return xoa*xob + yoa*yob + zoa*zob;
}

const Point cross(const Point&O,const Point&A,const Point&B){
    Real xoa = A.x - O.x;
    Real xob = B.x - O.x;
    Real yoa = A.y - O.y;
    Real yob = B.y - O.y;
    Real zoa = A.z - O.z;
    Real zob = B.z - O.z;
    return Point(yoa*zob-zoa*yob,xob*zoa-xoa*zob,xoa*yob-xob*yoa);
}

struct Quat{ // ��Ԫ��
    Real w, x, y, z;
    Quat(Real a=0,Real b=0,Real c=0,Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{return Quat(w,-x,-y,-z);} // ����
};

const Quat operator * (const Quat&lhs, const Quat&rhs){
    return Quat(
            lhs.w*rhs.w-lhs.x*rhs.x-lhs.y*rhs.y-lhs.z*rhs.z,
            lhs.w*rhs.x+lhs.x*rhs.w+lhs.y*rhs.z-lhs.z*rhs.y,
            lhs.w*rhs.y-lhs.x*rhs.z+lhs.y*rhs.w+lhs.z*rhs.x,
            lhs.w*rhs.z+lhs.x*rhs.y-lhs.y*rhs.x+lhs.z*rhs.w
        );
}

Real AD, BD, CD, BC, AC, AB;

/// ������p���󾭹���תr֮��ĵ�
Point rotate(const Point &p, const Quat &r){
    Quat origin(0, p.x, p.y, p.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Point(after.x, after.y, after.z);
}

void qiuO(){
    //A.output();B.output();C.output();
    /// ���ȿ������x����
    O.x = 0.5*((AD*AD-BD*BD)/B.x + B.x);

    /// ����y��z
    assert(!is0(C.y));
    O.y = ((AD*AD-CD*CD-(O.x+O.x-C.x)*C.x)/C.y+C.y)*0.5;
    assert(sgn(AD*AD-O.x*O.x-O.y*O.y)>0);
    O.z = sqrt(AD*AD-O.x*O.x-O.y*O.y);
}

void proc(){
    /// ���ȼ���A����Ϊԭ�㣬B����Ϊ(AB, 0, 0)
    /// ������xc��yc
    A.x = A.y = A.z = 0.0;
    B.x = AB, B.y = B.z = 0.0;
    C.z = 0.0;
    C.x = (AB*AB+AC*AC-BC*BC)/(AB+AB);
    assert(sgn(AC*AC-C.x*C.x)>=0);
    C.y = sqrt(AC*AC-C.x*C.x);

    assert(isEq(A.dist(B), AB) && isEq(A.dist(C), AC) && isEq(B.dist(C), BC));

    /// �����O������
    qiuO();
    //O.output();
    /// ��O������ƽ�Ƶ�ԭ��
    A = A - O;
    B = B - O;
    C = C - O;
    O.x = O.y = O.z = 0;
    D = O;
    //printf("translate��\n");A.output();B.output();C.output();O.output();
    assert(isEq(A.dist(D),AD) && isEq(B.dist(D),BD) && isEq(C.dist(D),CD));
    /// �����������G
    Point G((A.x+B.x+C.x)/3.0,(A.y+B.y+C.y)/3.0,(A.z+B.z+C.z)/3.0);
    if(is0(G.x) && is0(G.y)){
        output(A.z, B.z, C.z);
        return;
    }
    Real lenOG = O.dist(G);
    assert(sgn(lenOG)>0);
    /// Ҫ��G������任Ϊ(0,0,lenOG)
    Point H(0, 0, -lenOG);
    /// ���������ת�����ת�Ƕ�
    Point axis = cross(O, G, H);
    Real lenAxis = sqrt(axis.norm());
    axis.x /= lenAxis;
    axis.y /= lenAxis;
    axis.z /= lenAxis;
    /// ���е㶼Ҫ���������ת�����ת����һ����ת������ת����Ԫ��Ϊ
    Real GH = G.dist(H);
    Real sinangle = 0.5*GH / lenOG;
    Real cosangle = isEq(1.0,sinangle)?0.0:sqrt(1.0-sinangle*sinangle);
    Quat r(cosangle, axis.x*sinangle, axis.y*sinangle, axis.z*sinangle);
    Point na = rotate(A, r);
    Point nb = rotate(B, r);
    Point nc = rotate(C, r);
    output(na.z,nb.z,nc.z);
}

/// ����Ƿ�ֻ��AD����
bool procAD(int qwe){
    /// ���һ����������ֱ���ң�BD��CD�Ƿ��ܹ�����
    /// ��BC�յ�ΪH����AH�����
    Real AH = 0.5 * sqrt(2.0*(AC*AC+AB*AB)-BC*BC);
    /// AH���������ý�AHB
    Real BH = 0.5 * BC;
    Real jiaoAHB = myacos((AH*AH+BH*BH-AB*AB)/(2.0*AH*BH));
    /// Ȼ����������ʱDB�ĳ���
    Real DH = AD + AH;
    Real xxDB = sqrt(DH*DH+BH*BH-2.0*DH*BH*cos(jiaoAHB));
    if(sgn(xxDB-BD)>0) return false;
    Real xxCD = sqrt(DH*DH+BH*BH+2.0*DH*BH*cos(jiaoAHB));
    if(sgn(xxCD-CD)>0) return false;
    /// ˵��BD��CD��������
    Real cosBDH = (DH*DH+xxDB*xxDB-BH*BH)/(2.0*(DH*xxDB));
    Real bh = xxDB*cosBDH;
    Real cosCDH = (xxCD*xxCD+DH*DH-BH*BH)/(2.0*(DH*xxCD));
    Real ch = xxCD * cosCDH;

    if(0==qwe){ // ��ӡABC
        output(-AD, -bh, -ch);
    }else if(1==qwe){ // ��ӡBAC
        output(-bh, -AD, -ch);
    }else if(2==qwe){ // ��ӡCBA
        output(-ch, -bh, -AD);
    }else{
        throw runtime_error("XXXXXX");
    }
    return true;
}

/// ����Ƿ�ֻ��1���������ã�ֻ���AD
bool proc1(){
    if(procAD(0)) return true;

    /// ����AB
    swap(AD, BD);
    swap(AC, BC);
    if(procAD(1)) return true;
    swap(AD, BD);
    swap(AC, BC);

    /// ����AC
    swap(AD, CD);
    swap(AB, BC);
    if(procAD(2)) return true;
    swap(AD, CD);
    swap(AB, BC);

    return false;
}

/// ���2����������
bool procBDCD(int qwe){
    /// AD���BD��CD������
    /// ��B������Ϊ(0,0),C������Ϊ(BC,0)
    /// �������A������
    B.x = B.y = B.z = 0; C.x = BC, C.y = C.z = 0;
    A.x = (AB*AB-AC*AC+C.x*C.x)/(C.x+C.x);
    A.y = sqrt(AB*AB-A.x*A.x);
    A.z = 0;
    /// �����D������
    D.x = ((BD*BD-CD*CD)/C.x+C.x)*0.5;
    if(sgn(BD*BD-D.x*D.x)<0) return false;
    D.y = -sqrt(BD*BD-D.x*D.x);
    D.z = 0;
    if(sgn(A.dist(D)-AD)>0) {
        return false;
    }

    /// ������ΪG�����ABC��DG�ϵ�ͶӰ����
    Point G((A.x+B.x+C.x)/3.0,(A.y+B.y+C.y)/3.0,0.0);
    Point vecDG = G - D; // ����DG
    /// B��CӦ�÷־�DG����
    Point c1 = cross(D,C,G);
    Point c2 = cross(D,G,B);
    Real tmp = c1.z * c2.z;
    if(sgn(tmp)<0) return false;
    Real lenDG = sqrt(vecDG.norm()); // DG�ĳ���
    Point vecDB = B - D; // ����DB
    Real hb = dot(D,B,G)/lenDG;
    Point vecDC = C - D;
    Real hc = dot(D,C,G)/lenDG;
    Point vecDA = A - D;
    Real ha = dot(D,A,G)/lenDG;
    if(0==qwe){ // ABC
        output(-ha,-hb,-hc);
    }else if(1==qwe){ // BAC
        output(-hb,-ha,-hc);
    }else if(2==qwe){ // CBA
        output(-hc,-hb,-ha);
    }else{
        throw runtime_error("proc2 qwe error");
    }
    return true;
}

bool proc2(){
    if(procBDCD(0)) return true;

    swap(AD, BD);
    swap(AC, BC);
    if(procBDCD(1)) return true;
    swap(AD, BD);
    swap(AC, BC);

    swap(AD, CD);
    swap(AB, BC);
    if(procBDCD(2)) return true;
    swap(AD, CD);
    swap(AB, BC);

    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        AD = getUnsigned();
        BD = getUnsigned();
        CD = getUnsigned();
        BC = getUnsigned();
        AC = getUnsigned();
        AB = getUnsigned();

        if(proc1()) {
            continue;
        }
        if(proc2()) {
            continue;
        }
        proc();
    }
    return 0;
}
