/**
    一个质量均匀三角形，由三根绳连三个点，三根绳固定在同一个点，
    三角形在重力作用下静止，求是三角形三个点的高度
    三根绳长以及三角形边长已知
    首先需要考虑特殊情况，进一步的可以分为三种情况
    即：只有1根绳有用、只有2根绳有用，3根全有用
    不清楚到底是哪种以及哪根，全部测试一遍即可，因为必然有且只有一种情况
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

struct Quat{ // 四元数
    Real w, x, y, z;
    Quat(Real a=0,Real b=0,Real c=0,Real d=0):w(a),x(b),y(c),z(d){}
    Quat conj()const{return Quat(w,-x,-y,-z);} // 共轭
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

/// 给定点p，求经过旋转r之后的点
Point rotate(const Point &p, const Quat &r){
    Quat origin(0, p.x, p.y, p.z);
    Quat after = r * origin * r.conj();
    assert(is0(after.w));
    return Point(after.x, after.y, after.z);
}

void qiuO(){
    //A.output();B.output();C.output();
    /// 首先可以求出x坐标
    O.x = 0.5*((AD*AD-BD*BD)/B.x + B.x);

    /// 再求y和z
    assert(!is0(C.y));
    O.y = ((AD*AD-CD*CD-(O.x+O.x-C.x)*C.x)/C.y+C.y)*0.5;
    assert(sgn(AD*AD-O.x*O.x-O.y*O.y)>0);
    O.z = sqrt(AD*AD-O.x*O.x-O.y*O.y);
}

void proc(){
    /// 首先假设A坐标为原点，B坐标为(AB, 0, 0)
    /// 则可求出xc与yc
    A.x = A.y = A.z = 0.0;
    B.x = AB, B.y = B.z = 0.0;
    C.z = 0.0;
    C.x = (AB*AB+AC*AC-BC*BC)/(AB+AB);
    assert(sgn(AC*AC-C.x*C.x)>=0);
    C.y = sqrt(AC*AC-C.x*C.x);

    assert(isEq(A.dist(B), AB) && isEq(A.dist(C), AC) && isEq(B.dist(C), BC));

    /// 再求出O点坐标
    qiuO();
    //O.output();
    /// 将O点坐标平移到原点
    A = A - O;
    B = B - O;
    C = C - O;
    O.x = O.y = O.z = 0;
    D = O;
    //printf("translate：\n");A.output();B.output();C.output();O.output();
    assert(isEq(A.dist(D),AD) && isEq(B.dist(D),BD) && isEq(C.dist(D),CD));
    /// 求出重心坐标G
    Point G((A.x+B.x+C.x)/3.0,(A.y+B.y+C.y)/3.0,(A.z+B.z+C.z)/3.0);
    if(is0(G.x) && is0(G.y)){
        output(A.z, B.z, C.z);
        return;
    }
    Real lenOG = O.dist(G);
    assert(sgn(lenOG)>0);
    /// 要把G的坐标变换为(0,0,lenOG)
    Point H(0, 0, -lenOG);
    /// 首先求出旋转轴和旋转角度
    Point axis = cross(O, G, H);
    Real lenAxis = sqrt(axis.norm());
    axis.x /= lenAxis;
    axis.y /= lenAxis;
    axis.z /= lenAxis;
    /// 所有点都要按照这个旋转轴和旋转角做一个旋转，该旋转的四元数为
    Real GH = G.dist(H);
    Real sinangle = 0.5*GH / lenOG;
    Real cosangle = isEq(1.0,sinangle)?0.0:sqrt(1.0-sinangle*sinangle);
    Quat r(cosangle, axis.x*sinangle, axis.y*sinangle, axis.z*sinangle);
    Point na = rotate(A, r);
    Point nb = rotate(B, r);
    Point nc = rotate(C, r);
    output(na.z,nb.z,nc.z);
}

/// 检查是否只有AD有用
bool procAD(int qwe){
    /// 检查一下三角形竖直悬挂，BD和CD是否能够松软
    /// 设BC终点为H，则AH可求出
    Real AH = 0.5 * sqrt(2.0*(AC*AC+AB*AB)-BC*BC);
    /// AH求出可以求得角AHB
    Real BH = 0.5 * BC;
    Real jiaoAHB = myacos((AH*AH+BH*BH-AB*AB)/(2.0*AH*BH));
    /// 然后可以求出此时DB的长度
    Real DH = AD + AH;
    Real xxDB = sqrt(DH*DH+BH*BH-2.0*DH*BH*cos(jiaoAHB));
    if(sgn(xxDB-BD)>0) return false;
    Real xxCD = sqrt(DH*DH+BH*BH+2.0*DH*BH*cos(jiaoAHB));
    if(sgn(xxCD-CD)>0) return false;
    /// 说明BD和CD不起作用
    Real cosBDH = (DH*DH+xxDB*xxDB-BH*BH)/(2.0*(DH*xxDB));
    Real bh = xxDB*cosBDH;
    Real cosCDH = (xxCD*xxCD+DH*DH-BH*BH)/(2.0*(DH*xxCD));
    Real ch = xxCD * cosCDH;

    if(0==qwe){ // 打印ABC
        output(-AD, -bh, -ch);
    }else if(1==qwe){ // 打印BAC
        output(-bh, -AD, -ch);
    }else if(2==qwe){ // 打印CBA
        output(-ch, -bh, -AD);
    }else{
        throw runtime_error("XXXXXX");
    }
    return true;
}

/// 检查是否只有1根绳起作用，只检测AD
bool proc1(){
    if(procAD(0)) return true;

    /// 交换AB
    swap(AD, BD);
    swap(AC, BC);
    if(procAD(1)) return true;
    swap(AD, BD);
    swap(AC, BC);

    /// 交换AC
    swap(AD, CD);
    swap(AB, BC);
    if(procAD(2)) return true;
    swap(AD, CD);
    swap(AB, BC);

    return false;
}

/// 检查2根绳子作用
bool procBDCD(int qwe){
    /// AD最长，BD和CD起作用
    /// 设B的坐标为(0,0),C的坐标为(BC,0)
    /// 可以求出A的坐标
    B.x = B.y = B.z = 0; C.x = BC, C.y = C.z = 0;
    A.x = (AB*AB-AC*AC+C.x*C.x)/(C.x+C.x);
    A.y = sqrt(AB*AB-A.x*A.x);
    A.z = 0;
    /// 再求出D的坐标
    D.x = ((BD*BD-CD*CD)/C.x+C.x)*0.5;
    if(sgn(BD*BD-D.x*D.x)<0) return false;
    D.y = -sqrt(BD*BD-D.x*D.x);
    D.z = 0;
    if(sgn(A.dist(D)-AD)>0) {
        return false;
    }

    /// 设重心为G，求出ABC在DG上的投影长度
    Point G((A.x+B.x+C.x)/3.0,(A.y+B.y+C.y)/3.0,0.0);
    Point vecDG = G - D; // 向量DG
    /// B、C应该分居DG两侧
    Point c1 = cross(D,C,G);
    Point c2 = cross(D,G,B);
    Real tmp = c1.z * c2.z;
    if(sgn(tmp)<0) return false;
    Real lenDG = sqrt(vecDG.norm()); // DG的长度
    Point vecDB = B - D; // 向量DB
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
