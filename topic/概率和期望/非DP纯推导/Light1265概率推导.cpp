/*
    ��t���ϻ���d��¹���ټ����㡣
    ÿ�����ѡ2��������
    ������ϻ����㣬�����ˡ�
    ������ϻ���¹��¹���ˡ�
    ������ϻ����ϣ������ˡ�
    �����¹��¹��nothing happens
    ��������¹������Ը�������������������������Ƿ�ɱ��¹
    �ʣ��������ĸ����Ƕ��١�

    ʵ�����������ֻ���ϻ��������йأ��������ϻ��϶��군��ż�����ϻ�����һ���������棬���漸�ʾ����ϻ�����ĸ���

*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int t,d;
        scanf("%d%d",&t,&d);
        if ( t & 1 ){
            printf("Case %d: 0\n",kase);
            continue;
        }

        double ans = 1.0;
        for(int i=t;i;i-=2){
            ans *= (double)(i-1) / ( i + 1 );
        }
        printf("Case %d: %.10f\n",kase,ans);
    }
    return 0;
}

