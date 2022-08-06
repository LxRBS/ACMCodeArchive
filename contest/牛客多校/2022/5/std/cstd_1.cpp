#include<bits/stdc++.h>
using namespace std;
int a[100050];
int cnt[100050];
int n;
int main(){
    int n;
    cin>>n;
    memset(a,0,sizeof(a));
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<3*n;i++){
        int x;
        string s;
        cin>>x>>s;
        cnt[x]++;
        if(s[0]=='Y') a[x]+=1;
        else a[x]-=1;
    }
    int ok=1;
    int changeflag=0;
    for(int i=0;i<n;i++){
        if(a[i]!=cnt[i]) {changeflag=1;break;}
    }
    int cntflag=0;
    int conflag=0;
    for(int i=0;i<n;i++){
        //if conflicts occur
        if(a[i]==0){
            conflag=1;
            ok=-1;
            break;
        }
        //if some for some digits no queries
        if(cnt[i]<1){
            cntflag=1;
            ok=-1;
            break;
        }
    }
    // if no conflict & no digits no queries, 
    //but more than one digits which only has one query
	int onecheck=0;
	if(conflag==0&&cntflag==0) {
        for(int i=0;i<n;i++){
            if(cnt[i]==1) {onecheck+=1;}
        }
    } 
    //if there are conflicts but only one digit has one query
    if(changeflag==1&&onecheck>=1) ok=1; 
	else if(onecheck>=1) ok=-1;
    
    if(ok==-1) cout<<"-1"<<endl;
    if(ok==1){
        for(int i=0; i<n;i++){
            if(a[i]>0) cout<<1;
            else cout<<0;
        }
        cout<<endl;
    }
    return 0;
}