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

//Manacher算法
//src是源字符串，tmp是临时字符串，r是半径数组，n是源字符串的长度
//tmp和r长度至少是2n
//start为最长回文开始的地方
//返回值为源中的最长回文子串的长度
int Manacher(char const src[],char t[],int r[],int const n){
    //预处理，s中加入特殊字符，头前加入不一样的字符确保判断不会越界
    t[0] = -1;
    t[1] = -2;
    int total = 2;
    for(int i=0;i<n;++i) t[total++] = src[i], t[total++] = -2;
    t[total] = 0;//结尾

    //初始化
    r[0] = r[1] = 1;

    //x用来记录已求出的r的下标界限
    int x = 1,k;
    while( x < total ){
        for(k=1;k<r[x];++k){
            if ( k + r[x-k] == r[x] ) break;
            r[x+k] = min(r[x-k],r[x]-k);
        }

        //半径至少是1或者r[x-k]
        r[x+k] = k == r[x] ? 1 : r[x-k];
        //将下标移到x+k
        x += k;
        //原始方法求半径，注意此时x可能已经超出范围，将数组开大一点初始化为0即可
        while( t[x+r[x]] == t[x-r[x]] ) ++r[x];
    }

    return 0;
}

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 1000010;
#endif

char A[SIZE],Tmp[SIZE<<1];
int R[SIZE<<1];

//从前往后数的最长回文
int f(int n){
    //找一个最大的数满足i-ri==0
    int ans = 2;
    n = n + n + 2;
    for(int i=n-1;i>=2;--i)if(i==R[i]){ans=i;break;}
    return ans - 1;
}

int g(int n){
    //满足2n+2==i+ri
    int ans = n+n+1;
    for(int i=1;i<=n+n+1;++i)if(n+n+2==i+R[i]){ans=i;break;}
    return R[ans]-1;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int kase;
    scanf("%d",&kase);
    while(kase--){
        scanf("%s",A);
        int n = strlen(A);
        int k = 0;
        while(k<n/2&&A[k]==A[n-k-1])++k;
        if(k==n/2){
            printf("%s\n",A);
            continue;
        }
        int m = n - k - k;
        Manacher(A+k,Tmp,R,m);
        int a = f(m);
        int b = g(m);
        if(a>=b){
            A[k+a]='\0';
            printf("%s%s\n",A,A+n-k);
        }else{
            A[k] = '\0';
            printf("%s%s\n",A,A+n-k-b);
        }
    }
    return 0;
}
