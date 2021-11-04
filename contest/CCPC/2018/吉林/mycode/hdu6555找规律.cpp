/**
  [x]��ʾС��x���������
  ����n����SIGMA(n/i)����ż��
  nС�ڵ���10��
  ��100���ڵı�����һ�£�����ÿһ��ż�������¹��ɣ�
  �����4��i��i��������4��i+1
  �����1��ż�����Ǵ�4��8����2��ż�����Ǵ�16��24
  ���ԣ��Ը���n�����ż����Ҫ����
  4��i��i��n��4��i��i+4��i
  �������⣬��[(sqrt(1+n)-1)/2,sqrt(n)/2]֮��ǡ��������
*/

#include <stdio.h>
#include <math.h>

char const A[2][100] = {
    "odd",
    "even"
};

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        int t1 = (sqrt(1.0+n)-1)*0.5;
        int t2 = sqrt((double)n)*0.5;
        printf("Case %d: %s\n",kase,A[4*t1*(t1+1)==n||1==t2-t1]);
    }
    return 0;
}
