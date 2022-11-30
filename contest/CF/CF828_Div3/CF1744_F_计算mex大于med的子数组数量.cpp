/**
 * 给定一个排列，问其中存在多少个子段满足mex>med
 * 其中mex就是mex，med是中位数
 * 假设子段长度为偶数L，则0到L/2-1必须存在，此时mex>=L/2，中位数是L/2-1，满足条件
 * 假设长度为奇数L，同理，0到(L+1)/2-1必须存在，此时mex>=(L+1)/2，中位数是(L+1)/2-1
 * 综合就是2mex>=L
 * 因此需要在数组中找到2倍mex大于等于长度的子数组的数量
 * 考虑枚举每一个i作为mex，很容易得到其核心段[si, ei]
 * 其中si = min(Pos[所有小于i的数]), ei=max(Pos[所有小于i的数])
 * 如果Pos[i]落在了[si, ei]中，则以i为mex的满足条件数量为0
 * 再从核心段往左右扩展到最大可能边界[ai, bi]
 * 其中ai = min(0, si, Pos[i]), bi = max(N-1, ei, Pos[i])
 * 现在的问题变为了包含核心段且不能超出左右边界且总长度小于等于2倍i的区间有多少个
 * 再变化一下变为左边富余长度left、有边富余长度right、核心长度self，目标长度total
 * 不超过total且包含核心长度的区间有多少个
 * 显然总数为(left+1)*(right+1)，再剔除超长的即可 
 */
#include <assert.h>
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+13;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using si = set<int>;
using mii = map<int, int>;

int N;
vi A;
vi Pos;

// 长度为self，左边长度为left，右边长度为right，目标长度为total
// 问包含self长度且不超过total的选取方法有多少种
// 其中left总是小于等于right
llt proc(int self, int left, int right, int total){
    // 不考虑total，
	llt ans = (left + 1LL) * (right + 1LL);
	// 然后剔除超长的即可
	int r = total - self - right;
	if(r >= left) return ans;
	// 从长度r+1到left，都有可能产生超长
	// 分别产生1,2,...,left-r个
	ans -= (1LL + left - r) * (left - r) / 2;
	return ans;
}

llt proc(int mex, int s, int e){
	int limit = mex + mex;
	if(e - s + 1 > limit) return 0;

	int anchor = Pos[mex];
	int a = -1, b = -1;
	if(anchor < s){
        a = anchor + 1;
		b = N - 1;
	}else if(e < anchor){
		a = 0;
		b = anchor - 1;
	}else{
		return 0;
	}
	int self = e - s + 1;
	int left = min(limit - self, min(s - a, b - e));
	int right = min(limit - self, max(s - a, b - e));
	return proc(self, left, right, limit);
}

llt proc(){
   llt ans = 1;
   int s = Pos[0], e = Pos[0];
   for(int i=1;i<N;++i){
	//    printf("%d: %lld\n", i, proc(i, s, e));
       ans += proc(i, s, e);	  
	   s = min(s, Pos[i]);
	   e = max(e, Pos[i]);  
   }
   return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif   

    int nofkase = getInt();
	while(nofkase--){
        A.assign(N = getInt(), 0);
		Pos.assign(N, 0);
		for(int i=0;i<N;++i){
			Pos[A[i] = getInt()] = i;
		}
		printf("%lld\n", proc());
	}
    return 0;
}