/**
   ����N��Ҫ������һ��Ԫ�ظ�����ͬ������{1,x,...,y,N}��
   ʹ��ÿ������������Ԫ��֮�ͣ������ظ�����
   Ҫ��������̣�N��100����
   ���統N==5ʱ��{1,2,4,5}��һ����
   ���������������һ����������{1,2,3,...,N}��һ�����н⣬
   ������Ҫ����100�㣬�ҿ϶����Ǵ�
   ʹ�õ����������������������������Ȳ�֪����������̬����
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int Limit;
int N,A[110] = {1};

//������x������x��0��ʼ
bool dfs(int x){
    if(x>=Limit){
        if(A[x-1]==N) return true;
        return false;
    }

    //�Ӵ����������������֦
    bool flag[110] = {false};
    for(int i=x-1;i>=0;--i)for(int j=i;j>=0;--j){
        if(A[i]+A[j]<=A[x-1]) break;
        if(A[i]+A[j]<=N&&!flag[A[i]+A[j]]){
            flag[A[x] = A[i]+A[j]] = true;
            if(dfs(x+1)) return true;
            //����Ҫ��ԭ����Ȼ�Ḳ�ǵ�
        }
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(1){
        scanf("%d",&N);
        if(0==N) break;

        if(1==N){
            printf("1\n");continue;
        }else if(2==N){
            printf("1 2\n");continue;
        }

        fill(A,A+N+1,0);
        A[0]= 1;

        for(Limit=3;;++Limit){
            if(dfs(1)){
                printf("1");
                for(int i=1;A[i]!=N;++i)printf(" %d",A[i]);
                printf(" %d\n",N);
                break;
            }
        }

    }
    return 0;
}
