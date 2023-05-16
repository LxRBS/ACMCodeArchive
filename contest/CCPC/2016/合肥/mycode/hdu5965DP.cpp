/**
  三行，第二行为一串数字，每一个数字表示该格周围雷的数量
  其他两行放雷
  问能够满足数字的摆放总数是多少

  基本上是典型的递推计数
  用Di表示第i列的方案总数，可以发现Di当然与D[i-1]有关，
  但是还与第i-1列摆放的雷的数量有关，所以要把这个信息也记录
  用Dij表示第i列摆放雷的数量为j个的方案总数（j=0,1,2）
  此时发现第i列能够摆放的雷还与剩余数量有关，
  令Dijk为第i列摆放j个雷还剩k个雷可以摆的方案总数(k=0,1,2)

  Di00=D[i-1][A[i]][0]，当Ai=0,1,2时，其他不存在
  Di10=2*D[i-1][A[i]-1][1]，当Ai=1,2,3时，其他不存在
  Di20=D[i-1][A[i]-2][2]，当Ai=2,3,4时，其他不存在

  Di01=D[i-1][A[i]-1][0]，当Ai=1,2,3时
  Di11=2*D[i-1][A[i]-2][1]，当Ai=2,3,4时
  Di21=D[i-1][A[i]-3][2]，当Ai=3,4,5时

  Di02=D[i-1][A[i]-2][0]，当Ai=2,3,4时
  Di12=2*D[i-1][A[i]-3][1]，当Ai=3,4,5时
  Di22=D[i-1][A[i]-4][2]，当Ai=4,5,6时
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

        //检查数字是否有大于6的，可能不需要
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

        //初始化
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


