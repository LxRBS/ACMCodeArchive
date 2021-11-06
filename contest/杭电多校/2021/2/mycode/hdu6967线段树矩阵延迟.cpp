/**
  两个数组a和b，如下操作
  1：a或者b增加x
  2：a、b分别变成3a+2b，3a-2b
  3：交换a和b
  4：计算a、b的乘积和
  令Lazy是一个矩阵，操作1分别是
  1 0 x 与 1 0 0
  0 1 0    0 1 x
  0 0 1    0 0 1
  操作2是
  3 2  0
  3 -2 0
  0 0  1
  操作3是
  0 1 0
  1 0 0
  0 0 1
  每一次操作用矩阵相乘即可记录Lazy
  线段树记录a和、b和、a方和、b方和、ab和。
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

typedef long long llt;
llt const MOD = 1000000007LL;
inline llt add(llt a,llt b){return (a+b)%MOD;}
inline llt add(llt a,llt b,llt c){return add(a,add(b,c));}
inline llt add(llt a,llt b,llt c,llt d){return add(a,b,add(c,d));}
inline llt add(llt a,llt b,llt c,llt d,llt e){return add(a,b,c,add(d,e));}
inline llt add(llt a,llt b,llt c,llt d,llt e,llt f){return add(a,b,c,d,add(e,f));}
inline llt mul(llt a,llt b){return (a*b)%MOD;}
inline llt mul(llt a,llt b,llt c){return mul(a,mul(b,c));}
inline llt mul(llt a,llt b,llt c,llt d){return mul(a,b,mul(c,d));}
inline llt sqr(llt a){return mul(a,a);}

int const SIZE = 200010;
inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

llt ASum[SIZE<<2];
llt A2Sum[SIZE<<2];
llt BSum[SIZE<<2];
llt B2Sum[SIZE<<2];
llt ABSum[SIZE<<2];
llt Lazy[SIZE<<2][2][3]; // lazy标记
typedef llt lazy_t[2][3];

inline void _pushUp(int t){
    int ls = lson(t), rs = rson(t);
    ASum[t] = add(ASum[ls], ASum[rs]);
    BSum[t] = add(BSum[ls], BSum[rs]);
    A2Sum[t] = add(A2Sum[ls], A2Sum[rs]);
    B2Sum[t] = add(B2Sum[ls], B2Sum[rs]);
    ABSum[t] = add(ABSum[ls], ABSum[rs]);
}

/// 判断是否存在lazy标记
inline bool hasLazy(int t){
    return Lazy[t][0][0] != 1
        || Lazy[t][1][1] != 1
        || 0 != Lazy[t][0][1]
        || 0 != Lazy[t][0][2]
        || 0 != Lazy[t][1][0]
        || 0 != Lazy[t][1][2];
}
/// 根据lazy更新值
inline void _f(int t, int len, const lazy_t&lazy){
    /// 首先将原始的和值记录下来
    llt oa2 = A2Sum[t];
    llt ob2 = B2Sum[t];
    llt oab = ABSum[t];
    llt oa = ASum[t];
    llt ob = BSum[t];

    llt L00 = lazy[0][0];
    llt L01 = lazy[0][1];
    llt L02 = lazy[0][2];

    llt L10 = lazy[1][0];
    llt L11 = lazy[1][1];
    llt L12 = lazy[1][2];

    /// 平方和
    A2Sum[t] = add(
        mul(sqr(L00),oa2),
        mul(sqr(L01),ob2),
        mul(len, sqr(L02)),
        mul(2LL,L00,L01,oab),
        mul(2LL,L00,L02,oa),
        mul(2LL,L01,L02,ob)
    );

    B2Sum[t] = add(
        mul(sqr(L10),oa2),
        mul(sqr(L11),ob2),
        mul(len, sqr(L12)),
        mul(2LL,L10,L11,oab),
        mul(2LL,L10,L12,oa),
        mul(2LL,L11,L12,ob)
    );

    /// 积和
    ABSum[t] = add(
        mul(L00,L10,oa2),
        mul(oab,add(mul(L01,L10),mul(L00,L11))),
        mul(L01,L11,ob2),
        mul(oa,add(mul(L00,L12),mul(L02,L10))),
        mul(ob,add(mul(L02,L11),mul(L01,L12))),
        mul(len,L02,L12)
    );

    /// 和
    ASum[t] = add(
        mul(L00, oa),
        mul(L01, ob),
        mul(len, L02)
    );

    BSum[t] = add(
        mul(L10, oa),
        mul(L11, ob),
        mul(len, L12)
    );
}
/// 根据父节点的lazy更新子节点的lazy
inline void _updateLazy(lazy_t&lazy, const lazy_t&parent){
    llt a00 = lazy[0][0];
    llt a01 = lazy[0][1];
    llt a02 = lazy[0][2];

    llt a10 = lazy[1][0];
    llt a11 = lazy[1][1];
    llt a12 = lazy[1][2];

    lazy[0][0] = add(mul(parent[0][0],a00),mul(parent[0][1],a10));
    lazy[0][1] = add(mul(parent[0][0],a01),mul(parent[0][1],a11));
    lazy[0][2] = add(mul(parent[0][0],a02),mul(parent[0][1],a12),parent[0][2]);

    lazy[1][0] = add(mul(parent[1][0],a00),mul(parent[1][1],a10));
    lazy[1][1] = add(mul(parent[1][0],a01),mul(parent[1][1],a11));
    lazy[1][2] = add(mul(parent[1][0],a02),mul(parent[1][1],a12),parent[1][2]);

}

inline void _pushDown(int t,int s,int e){
    if(!hasLazy(t)) return;

    int mid = (s + e) >> 1;
    int llen = mid - s + 1;
    int rlen = e - mid;
    int ls = lson(t), rs = rson(t);

    /// 根据lazy更新值
    _f(ls,llen,Lazy[t]);
    _f(rs,rlen,Lazy[t]);

    /// 确定儿子的lazy
    _updateLazy(Lazy[ls], Lazy[t]);
    _updateLazy(Lazy[rs], Lazy[t]);

    memset(Lazy[t], 0, sizeof(lazy_t));
    Lazy[t][0][0] = Lazy[t][1][1] = 1;
}

/// type取0123
/// 0表示增加A，1表示增加B，2表示2操作，3表示3操作
void modify(int t,int s,int e,int a,int b,int type,llt delta=0LL){
    if(a<=s&&e<=b){
        if(0==type){ // 增加A操作
            lazy_t lazy = {
                {1,0,delta},
                {0,1,0}
            };
            _f(t,e-s+1,lazy);
            _updateLazy(Lazy[t],lazy);
        }else if(1==type){ // 增加B操作
            lazy_t lazy = {
                {1,0,0},
                {0,1,delta}
            };
            _f(t,e-s+1,lazy);
            _updateLazy(Lazy[t],lazy);
        }else if(2==type){
            lazy_t lazy = {
                {3,2,0},
                {3,-2,0}
            };
            _f(t,e-s+1,lazy);
            _updateLazy(Lazy[t],lazy);
        }else if(3==type){
            lazy_t lazy = {
                {0,1,0},
                {1,0,0}
            };
            _f(t,e-s+1,lazy);
            _updateLazy(Lazy[t],lazy);
        }else{
            throw runtime_error("XXXX");
        }
        return;
    }
    _pushDown(t,s,e);
    int mid = (s+e) >> 1;
    if(a<=mid) modify(lson(t),s,mid,a,b,type,delta);
    if(mid<b) modify(rson(t),mid+1,e,a,b,type,delta);
    _pushUp(t);
}

llt query(int t,int s,int e,int a,int b){
    if(a<=s&&e<=b){
        return ABSum[t];
    }
    _pushDown(t,s,e);
    int mid = (s+e)>>1;

    llt ans = 0LL;
    if(a<=mid){
        ans = add(ans, query(lson(t),s,mid,a,b));
    }
    if(mid<b){
        ans = add(ans, query(rson(t),mid+1,e,a,b));
    }
    /// 可能有负数，因为矩阵中有负数
    return ans>=0?ans:ans+MOD;
}
void build(int t,int s,int e){
    Lazy[t][0][0] = Lazy[t][1][1] = 1;

    if(s==e){
        A2Sum[t] = sqr(ASum[t] = getUnsigned());
        B2Sum[t] = sqr(BSum[t] = getUnsigned());
        ABSum[t] = mul(ASum[t], BSum[t]);
        return;
    }

    int mid = (s+e)>>1;
    build(lson(t),s,mid);
    build(rson(t),mid+1,e);
    _pushUp(t);
}

void disp(int t,int s, int e){
    printf("%d:[%d, %d]\n",t,s,e);
    printf("A=%lld, A2=%lld, B=%lld, B2=%lld, AB=%lld\n",ASum[t],A2Sum[t],BSum[t],B2Sum[t],ABSum[t]);
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            printf("%lld ", Lazy[t][i][j]);
        }
        printf("\n");
    }
    if(s==e) return;

    int m=(s+e)>>1;
    disp(lson(t),s,m);
    disp(rson(t),m+1,e);
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int n = getUnsigned();
    build(1,1,n);

    int q = getUnsigned();
    for(int cmd,tag,a,b,iq=1;iq<=q;++iq){
        switch(cmd=getUnsigned()){
        case 1:{
            tag = getUnsigned();
            a = getUnsigned();
            b = getUnsigned();
            modify(1,1,n,a,b,tag,getUnsigned());
        }break;
        case 2:{
            a = getUnsigned();
            b = getUnsigned();
            modify(1,1,n,a,b,2);
        }break;
        case 3:{
            a = getUnsigned();
            b = getUnsigned();
            modify(1,1,n,a,b,3);
        }break;
        case 4:{
            a = getUnsigned();
            b = getUnsigned();
            printf("%lld\n",query(1,1,n,a,b));
        }break;
        default:throw runtime_error("wrong cmd");
        }
        //printf("XX:\n");
        //disp(1,1,n);
    }
    return 0;
}
