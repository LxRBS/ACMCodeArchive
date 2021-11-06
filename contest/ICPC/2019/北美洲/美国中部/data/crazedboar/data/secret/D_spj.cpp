#include <bits/stdc++.h>
using namespace std;

#define __LX_OLD__
#undef __LX_OLD__ //�������OJ��ע�͵���һ�У��������OJ�ͱ�����һ��

#define __LX_LOCAL__
//#undef __LX_LOCAL__ //���������OJ�Ͼͱ�����һ�У�����Ǳ��ز��Ծ�ע����һ��

int const AC = 0;//accepted

//����OJ�ĳ���������ͬ
#ifdef __LX_OLD__
int const WA = 2;//wrong answer
int const PE = 4;//presentation error
#else
int const WA = 1;//wrong answer
int const PE = 2;//presentation error
#endif // __LX_OLD__

FILE *f_in;   //��׼�����ļ�
FILE *f_out;  //��׼����ļ�
FILE *f_user; //�û��Ĵ��ļ�

char const ERR_MSG[][110] = {//ȫ�ִ�����Ϣ
    "",
    "There needs an integer, but not.",
    "There needs a double, but not.",
    "There should be sth. to read, but not.",
    "The number of digits after decimal point is wrong.",
    "Wrong answer.",
    "There should be nothing, but sth."
};
int ERR_NO = 0;//ȫ�ֱ�����������

//���ݲ������ļ�
//��OJ��Ҫ�����ṩ��׼���롢��׼������û���
//��OJ��Ҫ�����ṩ��׼������û���
//����1��ʾ�ɹ���0��ʾʧ��
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
   �ж��ַ���a�Ƿ�Ϊint��ʽ
   a������ʮ����������ʽ
   ����0��ʾʧ�ܣ�1��ʾ�ɹ�
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
   �ж��ַ���a�Ƿ�Ϊdouble��ʽ
   a�������������߶�������ʽ
   ����0��ʾʧ�ܣ�1��ʾ�ɹ�
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
  ���ַ����õ�ָ�����ȵ�double��double���������߶�������ʽ
  a: �ַ���
  pre: С�����Ӧ���е���������������ʾ������λ��
  ans: ������������
  �������double��ʽ����С����λ�����Ծ��᷵��ʧ��
  ����0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int readDouble(char const a[], int pre, double&ans){
    //����ʽ
    if(!isDoubleFormat(a)){
        ERR_NO = 2;//��Ҫһ��double������û��
        return 0;
    }

    //��龫��
    if(pre>0){
        int pn = 0, n = strlen(a);
        while(pn<n&&a[pn]!='.') ++pn;
        if(pn==n){//���û��С������Ҫ����С��λ����Ȼ����
            ERR_NO = 4;
            return 0;
        }
        //���С������λ��
        if(pn+pre+1!=n){
            ERR_NO = 4;//С�����λ������
            return 0;
        }
    }

    ///��ȡ����
    sscanf(a, "%lf", &ans);
    return 1;
}

/**
   ���ļ�����һ��
   fp: �ļ�
   length: ����
   ans: �������
   ����0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int read1Line(FILE* fp, int length, char ans[]){
    //����һ�У����û�з���false
    if(!fgets(ans,1001,fp)){
        ERR_NO = 3;//Ӧ�������ݵ�û��
        return 0;
    }

    //���ַ�������Ļس��뻻�з�ȥ����������˷���false
    int n = strlen(ans);
    while(n>0&&(ans[n-1]=='\n'||ans[n-1]=='\r')) ans[n-1]='\0',--n;
    if(0==n){
        ERR_NO = 3;//Ӧ�������ݵ�û��
        return 0;
    }

    return 1;
}

/**
   �����ļ��Ƿ��Ѿ����˽�β
*/
int isNthLeft(FILE*fp){
    char b[1010];
    if(fgets(b,1001,fp)){
        return 0;
    }
    return 1;
}

//���ԣ�����AC��WA����PE
int test(){
    char a[1010];
    if(!read1Line(f_user, 1010, a)){
        return WA;
    }
    double x;
    if(!readDouble(a, -1, x)){
        return WA;
    }
    //�ӱ�׼�𰸶�ȡ
    double y;
    fscanf(f_out, "%lf", &y);
    //��龫��
    double eps = fabs(x-y);
    if(eps<=1.1E-6){
        if(isNthLeft(f_user)){
            return AC;
        }else{
            ERR_NO = 6;
            return WA;
        }
    }

    ERR_NO = 5;//����������
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
