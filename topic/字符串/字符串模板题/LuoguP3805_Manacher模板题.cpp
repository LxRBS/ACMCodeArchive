/**
 * 求最长回文子串的长度，模板题
 * 建议用再跑一下CF1326D，洛谷上能过的板子在CF上有的会wa
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
int const SIZE = 1.1E7+10;
#endif

/// 回文字符串
struct Manacher{

using vi = vector<int>;
vi data;
vi r; // 半径数组

/// Manacher算法，输入源数组，以及数组长度
/// 返回<最长回文长度, 第一个开始的地方>, 从0开始编号
template<typename T>
pair<int, int> run(T const src[], int n){
    // 预处理, data根据src生成，隔一个插入一个字母
    this->data.clear();
    this->data.reserve(n+n+3);
    this->data.push_back(-1); // 开头
    this->data.push_back(-2); // 间隔
    for(int i=0;i<n;++i){
        this->data.push_back(src[i]);
        this->data.push_back(-2);
    }
    this->data.push_back(-3); // 结尾，开头结尾间隔必然不能取src中的值

    // 求半径数组
    int total = this->data.size();
    this->r.assign(total, 0);
    this->r[0] = this->r[1] = 1;
    int x = 1, k;
    while(x < total){
        for(k=1;k<r[x];++k){
            if(k+r[x-k] == r[x]) break;
            assert(x + k < total);
            r[x+k] = min(r[x-k], r[x] - k);
        }
        // 半径至少是1或者r[x-k]
        r[x+k] = k == r[x] ? 1 : r[x-k];
        if((x += k) >= total - 1) break; // total-1可以不用求了
        while(this->data[x + r[x]] == this->data[x - r[x]]){
            ++r[x];
        }
    }    

    // 确定返回值
    pair<int, int> ans = {0, 0};
    int & ret = ans.first;
    int & start = ans.second;
    for(int i=0;i<total;++i){
        int tt = r[i] - 1;
        if(ret < tt){
            start = (i - (ret = tt)) >> 1;
        }
    }
    return ans;
}

}Man;

char S[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    scanf("%s", S);
    printf("%d\n", Man.run<char>(S, strlen(S)).first);
    return 0;
}

