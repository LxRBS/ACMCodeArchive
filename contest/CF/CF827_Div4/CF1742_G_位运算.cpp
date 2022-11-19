/**
 * 给定一个长度为N的数组A，令Di=A1 | A2 | ... | Ai
 * 即D是A的前缀或数组
 * 现在允许任意调换A的次序，使得D字典序最大，求这个最大的D
 * 最多只有31位，首先把用Bi记录第i位有1的所有的A的元素
 * 用Left记录所有出现过的位的编号，然后循环
 * 每次从Left中选出最大的数，记作i，然后去Bi中找“最大的”Aj
 * Aj就是本次选出的数，然后从Left中把所有Aj有的位删掉
 * 如果Left用完了，A还没有用完，则剩下的Ai可以随意排
 * 时间复杂度不会感觉不超过O(32N)
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

char getChar(){
    char ch = __hv007();
    while(!islower(ch) && ch != '\n') ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 14;
#else
int const SIZE = 2E5+12;
#endif

using vi = vector<int>;
using vvi = vector<vi>;

int N;
int A[SIZE];
vvi B;
int Ans[SIZE];
bool Flag[SIZE];
int Bit[32] = {0};

void proc(){
    if(1 == N){
        return (void)printf("%d\n", A[1]);
    }

    B.assign(32, vi());
    set<int> left; // 保存所有出现过的位的数量级
    for(int i=1;i<=N;++i){
        for(int j=0;j<32;++j){
            if(A[i] & Bit[j]){
                left.insert(j);
                B[j].push_back(i);
            }
        }
    }

    auto f = [&](int pos){ // 把A[pos]对应的位从left中删去
        for(int i=0;i<32;++i){
            if(A[pos] & Bit[i]){
                left.erase(i);
            }
        }
    };

    auto cmp = [&](int a, int b)->bool{ // 判断A[a]是否比A[b]占更多的位
        for(auto it=left.rbegin();it!=left.rend();++it){
            int bit = Bit[*it];
            int ia = (A[a] & bit) ? 1 : 0;
            int ib = (A[b] & bit) ? 1 : 0;
            if(ia != ib) return ia > ib;
        }
        return false;
    };

    fill(Flag, Flag+N+1, false);
    /// 最大值肯定排在第一个
    int pos = max_element(A+1, A+N+1) - A;
    Flag[Ans[0] = pos] = true;
    f(pos);
    
    int cur = 1;
    while(1){
        if(left.empty()) break;

        int now = *--left.end();
        left.erase(--left.end());

        int k = -1;
        for(auto i : B[now]){
            if(Flag[i]) continue;
            if(-1 == k || cmp(i, k)){
                k = i;
            }
        }

        assert(-1 != k);
        Flag[Ans[cur++] = k] = true;
        f(k);

        if(cur == N) break;
    }

    int k = 1;
    if(cur < N)while(1){
        while(Flag[k]) ++k;
        Flag[Ans[cur++] = k] = true;
        if(cur == N) break;
    }
    for(int i=0;i<N;++i)printf("%d ", A[Ans[i]]);
    printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    for(int i=0;i<32;++i) Bit[i] = (1 << i);

    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        proc();
    }
    return 0;
}

