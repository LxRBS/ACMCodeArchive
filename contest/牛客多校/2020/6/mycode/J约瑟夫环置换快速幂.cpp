/**
    ԭʼ����1~N�������ɴα任
    ÿһ�α任����k-Լɪ����x��
    ����������
    ������һ��k-Լɪ�򻷣�
    ������״���������n����logƽ��ʱ�������һ��k-Լɪ�򻷵��û�
    Ȼ�����û��Ŀ����ݣ�������nlogmʱ����ɣ�m���ݴ�
    ������û�����
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE = 100010;

//��״����
int C[SIZE];
inline int lowbit(int x){return x&(-x);}
int query(int idx){
    int ans = 0;
    for(;idx>0;idx-=lowbit(idx))ans+=C[idx];
    return ans;
}
//idxλ�ü�1
void modify(int idx,int delta,int n){
    for(;idx<=n;idx+=lowbit(idx))C[idx]+=delta;
}

//��һ��KԼɪ�򻷵��û�����Ҫ�õ���״����
//n����������k��Լɪ�������c����״���飬ans�Ǵ�
void k_Josephus(int n,int k,int c[],int ans[]){
    //��ʼ�����1~n����һ��
    fill(C,C+n+1,0);
    for(int i=1;i<=n;++i)modify(i,1,n);
    int lastpos = 1;  //�ϴ�ȡ������λ�ã���ʼΪ1
    for(int i=1,cnt=n;cnt>0;++i,--cnt){//cnt�ǵ�ǰ��ʣ�µ�����
        //ÿ��ȡ������Ӧ���� (lastpos-1+k-1)%cnt+1
        //�����������ҵ���һ�����Ϊtarget�ĵط�
        int target = (lastpos-1+k-1)%cnt + 1;
        int mid, left = 1, right = n;
        do{
            mid = (left + right) >> 1;
            if(query(mid)>=target) right = mid - 1;
            else left = mid + 1;
        }while(left<=right);
        //left���Ǵ�
        lastpos = target;
        modify(ans[i] = left,-1,n);
    }
}

void disp(int const a[],int n){
    for(int i=1;i<=n;++i)cout<<a[i]<<" ";
    cout<<endl;
}

//���û��Ŀ�����
//a��ԭʼ�û���n�����г���
//m���ݴΣ�ret�ǽ��,tmp����ʱ����
//a��ret��tmp������ͬ���������Ժ�a�ᷢ���ı�
void power(int a[],int n,int m,int ret[],int tmp[]){
    for(int i=1;i<=n;++i)ret[i]=i;
    while(m){
        if(m&1){
            for(int i=1;i<=n;++i)tmp[i] = a[ret[i]];
            copy(tmp,tmp+n+1,ret);
        }
        m>>=1;
        for(int i=1;i<=n;++i)tmp[i] = a[a[i]];
        copy(tmp,tmp+n+1,a);
    }
    return;
}

int Zhi[SIZE],Tmp[SIZE],Ans[SIZE];
int Total[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;++i)Total[i] = i;

    while(m--){
        int k,x;
        scanf("%d%d",&k,&x);
        //KԼɪ�򻷵��û�
        k_Josephus(n,k,C,Zhi);
        //������û�����
        power(Zhi,n,x,Ans,Tmp);
        //Ans���ݴ��Ժ���û�
        for(int i=1;i<=n;++i){
            Tmp[i] = Total[Ans[i]];
        }
        copy(Tmp,Tmp+n+1,Total);
    }
    for(int i=1;i<=n;++i)printf("%d ",Total[i]);
    printf("\n");
    return 0;
}
