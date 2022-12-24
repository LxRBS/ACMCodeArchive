/**
 * 给定字符串s，找到最长的字符串t，满足
 * 1 t的长度不超过s
 * 2 t是一个回文串
 * 3 t可以发分解为ab，其中a是s的前缀，b是s的后缀
 * 首先将s两端首尾相等的字符串剔除。例如s如果是: abxyzba，
 * 则将ab...ba这一段拿出来，这一段肯定包含在答案里，
 * 接下来只要处理xyz即可
 * 在剩下的字符串中只需寻找最长的前缀或者最长的后缀为回文的即可。
 * 求出Manacher数组，然后搜索两遍，取最大的那个即可。
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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
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

int f(int n){
    int ans = 2;
    n = n + n + 2;
    for(int i=n-1;i>=2;--i)if(i == Man.r[i]){ans = i; break;}
    return ans - 1;
}

int g(int n){
    int ans = n + n + 1;
    for(int i=1;i<=n+n+1;++i)if(n+n+2==i+Man.r[i]){ans = i; break;}
    return Man.r[ans] - 1;
}
void proc(){
    int n = strlen(S);
    int k = 0;
    while(k<n/2&&S[k]==S[n-k-1])++k;
    if(k==n/2){ // 说明S本身就是回文
        return (void)printf("%s\n",S);
    }    
    int m = n - k - k;
    Man.run<char>(S+k, m);
    int a = f(m);
    int b = g(m);
    if(a >= b){
        S[k + a] = '\0';
        return (void)printf("%s%s\n", S, S+n-k);
    }
    S[k] = '\0';
    printf("%s%s\n", S, S+n-k-b);
    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%s", S);
        proc();
    }
    return 0;
}

