#include <cstdio>
#include <cctype>

double W[128];
inline void init(){  //����һ��������������һ������ģ��
    W['C'] = 12.01;  //��ģ����ƣ�������˼�������
    W['H'] = 1.008;  //�ַ�������������������������ֱ�������ַ�
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
            char ch = *p++; //ȡ��ǰ��ĸ��Ȼ���p�Ӽ�
            int k = 0;
            //isdigit�����ж��ַ��Ƿ�Ϊ�����ַ�����'0'��'9'
            while( *p && isdigit(*p) ) k = k * 10 + ( *p - '0' ),++p;//���͵İѷ��������ճ�ϳ�һ������
            if ( 0 == k ) k = 1;
            ret += k * W[ch];
        }
        printf("%.3f\n",ret);
    }
    return 0;
}
