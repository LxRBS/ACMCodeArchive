#include <cstdio>
#include <cctype>

double W[128];
inline void init(){  //这是一个函数，函数是一个功能模块
    W['C'] = 12.01;  //分模块设计，有助于思考与编码
    W['H'] = 1.008;  //字符就是整数，因此利用数组可以直接索引字符
    W['O'] = 16.00;
    W['N'] = 14.01;
}

char A[100];
int main(){
    //freopen("1.txt","r",stdin);

    init();
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",A);

        double ret = 0.0;
        char *p = A;
        while(*p){
            char ch = *p++; //取当前字母，然后把p加加
            int k = 0;
            //isdigit就是判断字符是否为数字字符，即'0'到'9'
            while( *p && isdigit(*p) ) k = k * 10 + ( *p - '0' ),++p;//典型的把分离的数字粘合成一个整数
            if ( 0 == k ) k = 1;
            ret += k * W[ch];
        }
        printf("%.3f\n",ret);
    }
    return 0;
}
