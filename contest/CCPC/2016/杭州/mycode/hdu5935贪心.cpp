/*
  ������һ��ֱ��������������ʻ
  ��֪����ͨ��������λ�ã�����ͨ����Щλ��ʱ����������ʱ��
  ����Сͨ��ʱ���Ƕ���
  ̰��
  ��Сͨ���������һ�α�Ȼֻ��1s��Ȼ����ǰ��
  double������Ҫע�⾫�ȣ�����ʹ�÷���
*/
#include <stdio.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

double const EPS = 1E-8;
inline bool is0(double x){
    return -EPS <= x && x <= EPS;
}

int N;
int A[100100];

int proc(){
    //���һ��1s��
    int ret = 1;
    double velocity = A[N] - A[N-1];
    for(int i=N-1;i>0;--i){
        double ss = A[i] - A[i-1];
        if(is0(ss-velocity)){//����ٶȺͳ���ǡ����ȣ����øı��ٶȣ�����1s��
            ++ret;
        }else if(velocity>ss){//����ٶȴ��ڳ��ȣ�����1s�����ٶȼ�С
            ++ret;
            velocity = ss;
        }else{//������Ƚϴ������ж��Ƿ�������
            //��һ��ʵ�����������߲����������1�Ĳ���
            int t = (int)((ss-EPS)/velocity)+1;
            ret += t;
            velocity = ss / t;
        }
    }
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        N = getUnsigned();
        for(int i=1;i<=N;++i)A[i] = getUnsigned();

        printf("Case #%d: %d\n",kase,proc());
    }
    return 0;
}
