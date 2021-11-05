/**
 * 给定一个数组，两种操作
 * 1 pos newValue: 将pos位置设置成newValue
 * 2 s e: 问[s, e]区间内一共有多少个连续的不降子序列
 * 考虑一个连续的不降子序列，长度为n，则一共可以贡献n(n+1)/2个连续不降子序列
 * 因此只要维护数组中的不降子序列段数即可
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

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 200010;
#endif

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int N, Q;
llt ST[SIZE<<2]; // 答案
int L[SIZE<<2], R[SIZE<<2]; // 左右边界
int LLen[SIZE<<2], RLen[SIZE<<2]; // 左右边界段数的长度

inline void _pushUp(int t, int s, int e){
    int ls = lson(t), rs = rson(t);
    if(R[ls] > L[rs]){ // 中间的两段不能接上
        ST[t] = ST[ls] + ST[rs];
        L[t] = L[ls];
        R[t] = R[rs];
        LLen[t] = LLen[ls];
        RLen[t] = RLen[rs];   
        return;      
    }

    if(RLen[ls]+LLen[rs]==e-s+1){ // 直接是一整段
        llt n = e - s + 1;
        ST[t] = n * (n+1) >> 1;
        L[t] = L[ls];
        R[t] = R[rs];
        LLen[t] = RLen[t] = n; 
        return;   
    }

    llt n = LLen[rs];
    ST[t] = ST[ls] + ST[rs];
    ST[t] -= n * (n + 1) >> 1;

    n = RLen[ls];
    ST[t] -= n * (n + 1) >> 1;

    n = LLen[rs] + RLen[ls];
    ST[t] += n * (n + 1) >> 1;

    L[t] = L[ls];
    R[t] = R[rs];

    LLen[t] = LLen[ls];
    RLen[t] = RLen[rs];

    int mid = (s+e) >> 1;
    int ln = mid - s + 1;
    int rn = e - mid;

    if(LLen[ls] == ln){ // 如果左边是一整段
        LLen[t] += LLen[rs];
    }else if(RLen[rs] == rn){
        RLen[t] += RLen[ls];
    }

}

void modify(int t, int s, int e, int pos, int newValue){
    if(s==e){
        ST[t] = LLen[t] = RLen[t] = 1;
        L[t] = R[t] = newValue;
        return;
    }

    int m = (s+e) >> 1;
    if(pos<=m) modify(lson(t),s,m,pos,newValue);
    else modify(rson(t),m+1,e,pos,newValue);
    _pushUp(t,s,e);
}

struct _t{
    llt ans;
    int l, r;
    int llen, rlen;
    int len;
    _t(llt a=-1,int b=0,int c=0,int d=0,int e=0,int f=0):ans(a),l(b),r(c),llen(d),rlen(e),len(f){}
};

const _t operator + (const _t&a, const _t&b){
    if(a.r > b.l){ // 两段不能接上
        return _t(a.ans+b.ans, a.l, b.r, a.llen, b.rlen,a.len+b.len);
    }

    if(a.rlen+b.llen == a.len+b.len){ // 一整段
        llt n = a.len + b.len;
        return _t(n*(n+1)>>1, a.l, b.r, n, n, n);
    }

    llt ans = a.ans + b.ans;
    llt n = a.rlen;
    ans -= n * (n+1)>>1;
    n = b.llen;
    ans -= n * (n+1)>>1;
    n = a.rlen + b.llen;
    ans += n * (n+1) >> 1;

    int llen = a.llen, rlen = b.rlen;
    if(a.llen == a.len){
        llen += b.llen;
    }else if(b.rlen == b.len){
        rlen += a.rlen;
    }

    return _t(ans, a.l, b.r, llen, rlen, a.len+b.len);
}

_t query(int t, int s, int e, int a, int b){
    if(a<=s&&e<=b){
        return _t(ST[t], L[t], R[t], LLen[t], RLen[t], e-s+1);
    }
    int mid = (s+e) >> 1;
    _t ansl, ansr;
    int ls = lson(t), rs = rson(t);
    if(a<=mid) ansl = query(ls,s,mid,a,b);
    if(mid<b) ansr = query(rs,mid+1,e,a,b);
    assert(ansl.ans!=-1 || ansr.ans !=-1);
    if(ansl.ans == -1) return ansr;
    if(ansr.ans == -1) return ansl;

    /// 合并答案
    return ansl + ansr;
}

void build(int t, int s, int e){
    if(s==e){
        ST[t] = LLen[t] = RLen[t] = 1;
        L[t] = R[t] = getUnsigned();
        return;
    }

    int mid = (s+e) >> 1;
    build(lson(t), s, mid);
    build(rson(t), mid+1, e);
    _pushUp(t, s, e);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getUnsigned();
    Q = getUnsigned();
    build(1, 1, N);
    for(int cmd,x,iq=1;iq<=Q;++iq){
        // cout<<iq<<endl;
        if(1==(cmd=getUnsigned())){
            x = getUnsigned();
            modify(1, 1, N, x, getUnsigned());
        }else{
            x = getUnsigned();
            printf("%lld\n", query(1, 1, N, x, getUnsigned()).ans);
        }
    }
    return 0;
}
