#include <cstdio>

char A[100];
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",A);//读入字符串，以A开头，没有空格可以使用scanf %s

        int ret = 0;
        char *p = A;//p是一个指针，专门用在字符串循环中，运行效率比较高
        while(*p){  //这也是一个专用于字符串的循环结束条件，实际上等价于 *p != '\0'， 记住C语言的字符串都是以'\0'结尾的
            int k = 0;
            while( 'O' == *p ) ++p, ++k;//当前字母是O，就加k，++p的意思就是取下一个字母
            ret += k * ( k + 1 ) / 2;   //每一个O的得分就是从1加到k

            while( *p && 'X' == *p ) ++p;
        }

        printf("%d\n",ret);
    }
    return 0;
}
