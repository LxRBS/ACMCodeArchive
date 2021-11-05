//�󷽰�����������������Ӳ����������UVA674��ȫһ��
//��Ҫ������������Ҫ����Ӳ������
//ʹ�ö�Ԫ���ɺ���,x^i*y^j��ʾ���Ϊi��Ӳ������Ϊj
//1�ֵ����ɺ���ΪSIGMA{ x^i * y^i }
//5�ֵ����ɺ���ΪSIGMA{ x^(5i) * y^i }
//...

//�������ݽ�С����ʵ���Ա���

#include <cstdio>
#include <cstring>
#include <numeric>
#include <algorithm>
using namespace std;

int A[251][101];//Aij��ʾx^i*y^j��ϵ��
int B[251][101];//��ʱ����
int S[251];
void init(){
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));

    //������1�ֵ�ϵ��
    for(int i=0;i<101;++i) A[i][i] = 1;

    //������5/10/25/50
    int c[] = {5,10,25,50};
    for(int i=0;i<4;++i){
        //x��ϵ��
        for(int j=0;j<251;++j){
            //y��ϵ��
            for(int k=0;k<101;++k){
                //��һ�����ɺ�����ÿһ��
                for(int w=0;j+w*c[i]<251&&w+k<101;++w){
                    B[j+w*c[i]][k+w] += A[j][k];
                }
            }
        }

        //����
        memcpy(A,B,sizeof(B));
        memset(B,0,sizeof(B));
    }

    //Ԥ�������
    for(int i=0;i<251;++i) S[i] = accumulate(A[i],A[i]+101,0);
}
int main(){
    init();

    int n;
    while( EOF != scanf("%d",&n) ){
        printf("%d\n",S[n]);
    }
    return 0;
}
