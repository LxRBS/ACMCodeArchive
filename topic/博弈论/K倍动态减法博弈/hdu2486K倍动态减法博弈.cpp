/**
    K����̬��������
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
//K����̬���ĵıذܵ�
//����a��Ž��������b����
//n�Ǽ�������޼�a[i]<=n��k�Ǳ���
//����a������
int KNim(llt n,llt k,llt a[],llt b[]){
    a[0] = b[0] = 1;
    int cnt = 1;
    int t = 0;
    while(a[cnt-1]<n){
        a[cnt]=b[cnt-1]+1;
        //�ҵ���һ��tʹ��at*k<a[cnt]
        while(a[t+1]*k<a[cnt]) ++t;
        if(a[t]*k<a[cnt]) b[cnt] = b[t] + a[cnt];
        else b[cnt] = a[cnt];
        ++cnt;
    }
    return cnt;
}

llt A[1000010],B[1000010];
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n,k;
        scanf("%lld%lld",&n,&k);
        int cnt = KNim(n,k,A,B);

        printf("Case %d: ",kase);
        if(A[cnt-1]==n){
            printf("lose\n");
            continue;
        }

        //��ͣ�ļ�ȥA�е��������ʣ�µļ���
        int ans = 0;
        for(int i=cnt-1;n;--i){
            if(A[i]<=n) n -= A[i], ans = i;
        }
        printf("%lld\n",A[ans]);
    }
    return 0;
}
