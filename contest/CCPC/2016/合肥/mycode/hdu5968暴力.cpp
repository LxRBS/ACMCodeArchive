/**
  ����ΪN�����飬����M��x����ÿһ��x��
  Ҫ���ҵ������е����������У�ʹ��������x��ӽ�
  ����ж���𰸣�ȡ���
  N��100���ڣ����Ա���
*/

#include <stdio.h>
using namespace std;

int A[110];
int B[110][110];

inline int abs(int n){
    return n>=0?n:-n;
}

int f(int n, int x){
    int cha = 1000000000;
    int ans = 0;
    for(int len=n;len>0;--len){
        for(int i=0;i<n-len+1;++i){
            int t = abs(x-B[i][i+len-1]);
            if(t<cha) cha=t,ans=len;
        }
    }
    return ans;
}

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,m;
        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%d",A+i);

        //Ԥ����
        for(int i=0;i<n;++i){
            B[i][i] = A[i];
            for(int j=i+1;j<n;++j){
                B[i][j] = B[i][j-1] ^ A[j];
            }
        }

        scanf("%d",&m);
        while(m--){
            int x;
            scanf("%d",&x);
            printf("%d\n",f(n,x));
        }
        printf("\n");
    }
    return 0;
}