/**
 * 给定一个矩阵，里面含有若干个0，0所在的位置可以改写为任意整数
 * 可以任意交换两行或者两列，问能否通过这些操作使得整个矩阵元素有序，即
 * A11 <= A12 <= A1M <= A21 <= A22 <= ... <= ANM
 * 对行列根据已知情况（即不考虑0）进行排序，如果没有出现矛盾，即可
 * 首先对列进行排序，一共有3种情况，因此通过throw来表示第3种情况
 * 其次对行排序，因为行还有更强的条件
 * 如果不throw异常说明可以满足条件
 * 时间为O(HWlogH+HWlogW)
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 1E6+13;
#endif

struct CmpExcept : public exception{};

using vi = vector<int>;
using vvi = vector<vi>;

bool cmp(const vi & a, const vi & b) noexcept(false) {
    int flag = 0;
    int n = a.size();
    for(int i=0;i<n;++i){
        if(0 == a[i] || 0 == b[i]) continue;
        if(a[i] < b[i]) flag |= 1;
        if(b[i] < a[i]) flag |= 2;
        if(3 == flag) throw CmpExcept();
    }
    return 1 == flag;
}

bool cmp2(const vi & a, const vi & b) noexcept(false) {
    int flag = 0;
    int n = a.size();
    int mina = 1E9, maxa = -1;
    int minb = 1E9, maxb = -1;
    for(int i=0;i<n;++i){
        if(a[i]) mina = min(mina, a[i]), maxa = max(maxa, a[i]);
        if(b[i]) minb = min(minb, b[i]), maxb = max(maxb, b[i]);
        if(0 == a[i] || 0 == b[i]) continue;
        if(a[i] < b[i]) flag |= 1;
        if(b[i] < a[i]) flag |= 2;
        if(3 == flag) throw CmpExcept();
    }
    if(!(maxa <= minb) && !(maxb <= mina)){
        throw CmpExcept();
    }
    if(1 == flag){ // a在前
        if(minb < maxa){
            throw CmpExcept();
        }
        return true;
    }
    if(2 == flag){
        if(mina < maxb){
            throw CmpExcept();
        }            
    }
    return false;
}

int H, W;
vvi A, B;

bool check(vvi & a, bool (*cmp)(const vi &a, const vi &b)noexcept(false)){
    try{
        sort(a.begin(), a.end(), cmp);
        return true;
    }catch(CmpExcept e){
        return false;
    }    
}

bool proc(){  
    B.assign(W, vi(H, 0));
    for(int i=0;i<H;++i)for(int j=0;j<W;++j) B[j][i] = A[i][j];
    if(!check(B, cmp)) return false;
    
    for(int i=0;i<H;++i)for(int j=0;j<W;++j) A[i][j] = B[j][i];
    return check(A, cmp2);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    H = getInt(); W = getInt();
    A.assign(H, vi(W, 0));
    for(auto & v : A)for(auto & i : v){
        i = getInt();
    }
    puts(proc()?"Yes":"No");
    return 0;
}
