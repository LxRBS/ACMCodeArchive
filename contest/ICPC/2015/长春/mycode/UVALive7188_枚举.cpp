/*
  给定数组，问是否能够：
  最多只移除一个数使得剩下的数有序

  按增序扫描一遍降序扫描一遍
  假设顺序不一致，则当场两个数必然要删掉一个
  很容易确定删除条件
  第二遍扫描时要注意还原，或者直接复制一遍数组
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int A[100010];
int N;

bool proc(){
    if(N<=3) return true;

    int k = 0;
    while(k<N-1&&A[k]==A[k+1]) ++k;

    if(k>=N-3) return true;

    //从k开始判断
    //还原用的变量
    int ov1 = -1, ovi = -1;
    int op = -1;
    //先按递增判断一遍
    int cnt = 0;
    bool flag = true;
    for(int i=k+1;i<N;++i){
        if(A[i-1]>A[i]){
            if(1==cnt){
                flag = false;
                break;
            }
            ++cnt;
            if(1==i){//只能去掉A[0]
                continue;
            }
            if(A[i]<A[i-2]){//只能去掉Ai
                //记录原始数据
                ovi = A[op=i],ov1 = A[i-1];
                A[i] = A[i-1];
                A[i-1] = A[i-2];
            }else{//去掉A[i-1]即可
                ovi = A[op=i-1];
                A[i-1] = A[i-2];
            }
        }
    }
    if(flag) return true;
    //还原
    A[op] = ovi;
    if(-1!=ov1) A[op-1] = ov1;
    //再按递减来一遍
    cnt = 0;
    flag = true;
    for(int i=k+1;i<N;++i){
        if(A[i-1]<A[i]){
            if(1==cnt){
                flag = false;
                break;
            }
            ++cnt;
            if(1==i){//只能去掉A[0]
                continue;
            }
            if(A[i]>A[i-2]){//只能去掉Ai
                A[i] = A[i-1];
                A[i-1] = A[i-2];
            }else{//去掉A[i-1]即可
                A[i-1] = A[i-2];
            }
        }
    }
    return flag;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        for(int i=0;i<N;++i)A[i]=getUnsigned();

        printf(proc()?"YES\n":"NO\n");
    }
    return 0;
}


