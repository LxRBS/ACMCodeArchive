#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
vector<int> Vec[100010];
vector<int> Left;
bool Flag[100010];
void f(int n){
    fill(Flag,Flag+n+1,false);
    Left.clear();

    for(int i=1;i<=n;++i){
        bool tt = false;
        vector<int>&v = Vec[i];
        for(vector<int>::iterator it=v.begin();it!=v.end();++it){
            if(!Flag[*it]){
                Flag[*it] = tt = true;
                break;
            }
        }
        if(!tt){//到Flag里找第一个不为真的
            Left.push_back(i);
        }
    }
    //在Left里面处理
    if(!Left.empty()){
        int t = Left[0];
        for(int i=1;i<=n;++i){
            if(!Flag[i]){
                printf("IMPROVE\n%d %d\n",t,i);
                return;
            }
        }
    }
    printf("OPTIMAL\n");
    return;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int n = getUnsigned();
        for(int i=1;i<=n;++i){
            vector<int>&v=Vec[i];
            int k = getUnsigned();
            v.clear();
            if(k!=0){
                v.resize(k);
                for(int j=0;j<k;++j)v[j]=getUnsigned();
            }
        }
        f(n);
    }
    return 0;
}