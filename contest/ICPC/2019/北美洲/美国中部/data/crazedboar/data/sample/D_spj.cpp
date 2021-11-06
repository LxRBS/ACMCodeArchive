#include <bits/stdc++.h>
using namespace std;

#define __LX_OLD__
#undef __LX_OLD__ //如果是老OJ就注释掉这一行，如果是新OJ就保留这一行

#define __LX_LOCAL__
//#undef __LX_LOCAL__ //如果是用在OJ上就保留这一行，如果是本地测试就注释这一行

int const AC = 0;//accepted

//新老OJ的常量有所不同
#ifdef __LX_OLD__
int const WA = 2;//wrong answer
int const PE = 4;//presentation error
#else
int const WA = 1;//wrong answer
int const PE = 2;//presentation error
#endif // __LX_OLD__

FILE *f_in;   //标准输入文件
FILE *f_out;  //标准输出文件
FILE *f_user; //用户的答案文件

char const ERR_MSG[][110] = {//全局错误消息
    "",
    "There needs an integer, but not.",
    "There needs a double, but not.",
    "There should be sth. to read, but not.",
    "The number of digits after decimal point is wrong.",
    "Wrong answer.",
    "There should be nothing, but sth."
};
int ERR_NO = 0;//全局变量，错误编号

//根据参数打开文件
//新OJ需要依次提供标准输入、标准输出和用户答案
//老OJ需要依次提供标准输入和用户答案
//返回1表示成功，0表示失败
int myopen(char *args[]){
    f_in = fopen(args[1],"r");
    if(!f_in){
#ifdef __LX_LOCAL__
        fprintf(stderr,"stdin file not exists!\n");
#endif // __LX_LOCAL__
        return 0;
    }
#ifdef __LX_OLD__
    f_user = fopen(args[2],"r");
    if(!f_user){
#ifdef __LX_LOCAL__
        fprintf(stderr,"user out file not exists!\n");
#endif // __LX_LOCAL__
        return 0;
    }
#else
    f_out = fopen(args[2],"r");
    if(!f_out){
#ifdef __LX_LOCAL__
        fprintf(stderr,"stdout file not exists!\n");
#endif
        return 0;
    }
    f_user = fopen(args[3],"r");
    if(!f_user){
#ifdef __LX_LOCAL__
        fprintf(stderr,"user out file not exists!\n");
#endif // __LX_LOCAL__
        return 0;
    }
#endif // __LX_OLD__
    return 1;
}

void myclose(){
    if(f_in) fclose(f_in);
    if(f_user) fclose(f_user);
#ifndef __LX_OLD__
    if(f_out) fclose(f_out);
#endif // __LX_OLD__
}

/**
   判断字符串a是否为int格式
   a必须是十进制整数格式
   返回0表示失败，1表示成功
*/
int isIntFormat(char const a[]){
    char const *p = a;
    if(*p=='+'||*p=='-') ++p;

    for(;*p;++p){
        if('0'<=*p&&*p<='9'){
            ;//do nothing
        }else{
            return 0;
        }
    }
    return 1;
}

/**
   判断字符串a是否为double格式
   a可以是整数或者定点数格式
   返回0表示失败，1表示成功
*/
int isDoubleFormat(char const a[]){
    char const *p = a;
    if(*p=='+'||*p=='-') ++p;

    int c = 0;
    for(;*p;++p){
        if('0'<=*p&&*p<='9'){
            ;//do nothing
        }else if('.'==*p){
            ++c;
            if(c>=2) return 0;
        }else{
            return 0;
        }
    }
    return 1;
}

/**
  从字符串得到指定精度的double，double是整数或者定点数格式
  a: 字符串
  pre: 小数点后应该有的数量，非正数表示不限制位数
  ans: 输出参数，结果
  如果不是double格式或者小数点位数不对均会返回失败
  返回0表示失败，1表示成功
*/
int readDouble(char const a[], int pre, double&ans){
    //检查格式
    if(!isDoubleFormat(a)){
        ERR_NO = 2;//需要一个double，但是没有
        return 0;
    }

    //检查精度
    if(pre>0){
        int pn = 0, n = strlen(a);
        while(pn<n&&a[pn]!='.') ++pn;
        if(pn==n){//如果没有小数点又要求了小数位数显然错误
            ERR_NO = 4;
            return 0;
        }
        //检查小数点后的位数
        if(pn+pre+1!=n){
            ERR_NO = 4;//小数点后位数不对
            return 0;
        }
    }

    ///读取数据
    sscanf(a, "%lf", &ans);
    return 1;
}

/**
   从文件读入一行
   fp: 文件
   length: 长度
   ans: 输出参数
   返回0表示失败，1表示成功
*/
int read1Line(FILE* fp, int length, char ans[]){
    //读入一行，如果没有返回false
    if(!fgets(ans,1001,fp)){
        ERR_NO = 3;//应该有内容但没有
        return 0;
    }

    //将字符串后面的回车与换行符去掉，如果光了返回false
    int n = strlen(ans);
    while(n>0&&(ans[n-1]=='\n'||ans[n-1]=='\r')) ans[n-1]='\0',--n;
    if(0==n){
        ERR_NO = 3;//应该有内容但没有
        return 0;
    }

    return 1;
}

/**
   测试文件是否已经到了结尾
*/
int isNthLeft(FILE*fp){
    char b[1010];
    if(fgets(b,1001,fp)){
        return 0;
    }
    return 1;
}

//测试，返回AC、WA或者PE
int test(){
    char a[1010];
    if(!read1Line(f_user, 1010, a)){
        return WA;
    }
    double x;
    if(!readDouble(a, -1, x)){
        return WA;
    }
    //从标准答案读取
    double y;
    fscanf(f_out, "%lf", &y);
    //检查精度
    double eps = fabs(x-y);
    if(eps<=1.1E-6){
        if(isNthLeft(f_user)){
            return AC;
        }else{
            ERR_NO = 6;
            return WA;
        }
    }

    ERR_NO = 5;//就是数不对
    return WA;
}

int main(int argc,char *argv[]){
    if(!myopen(argv)){
        myclose();
        return 1000;
    }
    int ret = test();
    myclose();
#ifdef __LX_LOCAL__
    fprintf(stdout, "%s\n", ERR_MSG[ERR_NO]);
    if(WA==ret) fprintf(stdout,"WA\n");
	else if(PE==ret) fprintf(stdout,"PE\n");
	else fprintf(stdout,"AC\n");
#endif // __LX_LOCAL__
    return ret;
}
