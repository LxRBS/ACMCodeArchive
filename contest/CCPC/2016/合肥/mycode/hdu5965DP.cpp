/**
  ���У��ڶ���Ϊһ�����֣�ÿһ�����ֱ�ʾ�ø���Χ�׵�����
  �������з���
  ���ܹ��������ֵİڷ������Ƕ���

  �������ǵ��͵ĵ��Ƽ���
  ��Di��ʾ��i�еķ������������Է���Di��Ȼ��D[i-1]�йأ�
  ���ǻ����i-1�аڷŵ��׵������йأ�����Ҫ�������ϢҲ��¼
  ��Dij��ʾ��i�аڷ��׵�����Ϊj���ķ���������j=0,1,2��
  ��ʱ���ֵ�i���ܹ��ڷŵ��׻���ʣ�������йأ�
  ��DijkΪ��i�аڷ�j���׻�ʣk���׿��԰ڵķ�������(k=0,1,2)

  Di00=D[i-1][A[i]][0]����Ai=0,1,2ʱ������������
  Di10=2*D[i-1][A[i]-1][1]����Ai=1,2,3ʱ������������
  Di20=D[i-1][A[i]-2][2]����Ai=2,3,4ʱ������������

  Di01=D[i-1][A[i]-1][0]����Ai=1,2,3ʱ
  Di11=2*D[i-1][A[i]-2][1]����Ai=2,3,4ʱ
  Di21=D[i-1][A[i]-3][2]����Ai=3,4,5ʱ

  Di02=D[i-1][A[i]-2][0]����Ai=2,3,4ʱ
  Di12=2*D[i-1][A[i]-3][1]����Ai=3,4,5ʱ
  Di22=D[i-1][A[i]-4][2]����Ai=4,5,6ʱ
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const MOD = 100000007;

char A[10010];
int D[10010][3][3];
int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%s",A);

        int n=0;
        bool flag = true;

        //��������Ƿ��д���6�ģ����ܲ���Ҫ
        for(char*p=A;*p;++p,++n){
            if((*p -= '0')>6||*p<0){
                flag = false;
                break;
            }
        }
        if(!flag){
            printf("0\n");
            continue;
        }

        //��ʼ��
        memset(D,-1,sizeof(D));
        switch(A[0]){
            case 0:D[0][0][0] = 1;break;
            case 1:D[0][0][1] = 1;D[0][1][0] = 2;break;
            case 2:D[0][0][2] = 1;D[0][1][1] = 2;D[0][2][0] = 1;break;
            case 3:D[0][1][2] = 2;D[0][2][1] = 1;break;
            case 4:D[0][2][2] = 1;break;
        }

        int tmp;
        for(int i=1;i<n;++i)switch(A[i]){
            case 0:{
                D[i][0][0]=D[i-1][A[i]][0];
            }break;
            case 1:{
                D[i][0][0]=D[i-1][A[i]][0];
                tmp = D[i-1][A[i]-1][1];
                D[i][1][0]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][0][1]=D[i-1][A[i]-1][0];
            }break;
            case 2:{
                D[i][0][0]=D[i-1][A[i]][0];
                tmp = D[i-1][A[i]-1][1];
                D[i][1][0]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][2][0]=D[i-1][A[i]-2][2];
                D[i][0][1]=D[i-1][A[i]-1][0];
                tmp=D[i-1][A[i]-2][1];
                D[i][1][1]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][0][2]=D[i-1][A[i]-2][0];
            }break;
            case 3:{
                tmp = D[i-1][A[i]-1][1];
                D[i][1][0]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][2][0]=D[i-1][A[i]-2][2];
                D[i][0][1]=D[i-1][A[i]-1][0];
                tmp=D[i-1][A[i]-2][1];
                D[i][1][1]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][2][1]=D[i-1][A[i]-3][2];
                D[i][0][2]=D[i-1][A[i]-2][0];
                tmp=D[i-1][A[i]-3][1];
                D[i][1][2]=-1==tmp?-1:(tmp+tmp)%MOD;
            }break;
            case 4:{
                D[i][2][0]=D[i-1][A[i]-2][2];
                tmp=D[i-1][A[i]-2][1];
                D[i][1][1]=-1==tmp?-1:(tmp+tmp)%MOD;
                D[i][2][1]=D[i-1][A[i]-3][2];
                D[i][2][2]=D[i-1][A[i]-4][2];
                D[i][0][2]=D[i-1][A[i]-2][0];
                tmp=D[i-1][A[i]-3][1];
                D[i][1][2]=-1==tmp?-1:(tmp+tmp)%MOD;
            }break;
            case 5:{
                D[i][2][1]=D[i-1][A[i]-3][2];
                D[i][2][2]=D[i-1][A[i]-4][2];
                tmp=D[i-1][A[i]-3][1];
                D[i][1][2]=-1==tmp?-1:(tmp+tmp)%MOD;
            }break;
            case 6:{
                D[i][2][2]=D[i-1][A[i]-4][2];
            }break;
        }

        int ret = 0;
        for(int i=0;i<3;++i){
            if(D[n-1][i][0]>=0){
                ret = (ret + D[n-1][i][0])%MOD;
            }
        }
        printf("%d\n",ret);
    }
    return 0;
}


