/**
  1��N��N�������������õ����ٸ�ʹ��ʣ�µ������ܹ���������
  N��20���ڣ������ô��������
  �ҹ��ɷ������µĶ���Fib��
*/

#include <stdio.h>
using namespace std;

int B[21] = {
    0,0,0,0,1,1,2,3,3,
    4,5,6,7,7,8,9,10,11,12,13,14
};
int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        printf("Case #%d: %d\n",kase,B[n]);
    }
    return 0;
}
