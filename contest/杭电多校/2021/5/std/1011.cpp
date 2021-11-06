#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],t,n,x,y,cnt,sum;
int main(){
    scanf("%d",&t);
    while(t--){
        cnt=sum=0; 
        scanf("%d%d%d",&n,&x,&y);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]>=min(x,y)) cnt++;
        }
        if(x==y){
            for(int i=1;i<=n;i++){
                sum^=a[i]/(2*x)*x+a[i]%x;
            }
        }
        else if(!cnt){
            for(int i=1;i<=n;i++){
                sum^=a[i];
            }
        }
        else if(x<y&&cnt>=2){
            sum=0;
        }
        else if(x<y&&cnt==1){
            for(int i=1;i<=n;i++){
                if(a[i]<x) sum^=a[i];
            }
            int mx=*max_element(a+1,a+n+1);
            if(mx>sum&&sum<x&&mx-sum!=x) sum=1;
            else sum=0;
        }
        else if(x>y){
            sum=1;
        }
        if(sum) printf("Jslj\n");
        else printf("yygqPenguin\n");
    } 
}
 