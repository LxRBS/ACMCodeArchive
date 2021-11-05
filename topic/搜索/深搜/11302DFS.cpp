#include <cstdio>
#include <algorithm>
using namespace std;

struct _t{
    int cnt;//每个箱子可能做底的数量
	int size[3][2];//可能的尺寸
}Box[10];

int Ans;     //答案
bool Flag[10];//标志位
bool isHalt;//是否提前终止

void input(int n){
	for(int i=0;i<n;++i){
		int a[3];
		scanf("%d%d%d",a,a+1,a+2);
        sort(a,a+3);

		//只有一种尺寸
		if ( a[0] == a[2] ){
			Box[i].cnt = 1;
			Box[i].size[0][0] = Box[i].size[0][1] = a[0];
			continue;
		}

		//两种尺寸
		if ( a[0] == a[1] || a[1] == a[2] ){
			Box[i].cnt = 2;
			Box[i].size[0][0] = a[0];
			Box[i].size[0][1] = a[1];
			Box[i].size[1][0] = a[1];
			Box[i].size[1][1] = a[2];
			continue;
		}

		//三种尺寸
		Box[i].cnt = 3;
		Box[i].size[0][0] = a[0];
		Box[i].size[0][1] = a[1];
		Box[i].size[1][0] = a[0];
		Box[i].size[1][1] = a[2];
		Box[i].size[2][0] = a[1];
		Box[i].size[2][1] = a[2];
	}
    return;
}

//deep为已经放置的箱子数，n为最大深度，s1,s2为当前尺寸
void dfs(int deep,int n,int s1,int s2){
	if ( deep == n ) {
		Ans = n;
        isHalt = true;
		return;
	}

	bool isAva = false;//判断这一次递归中是否摆了箱子
	for(int i=0;i<n;++i){
		//如果该箱已经使用，则略过
		if ( Flag[i] ) continue;

		for(int j=0;j<Box[i].cnt;++j){
			//如果箱子的尺寸不合适，则略过
            if ( s1 < Box[i].size[j][0] || s2 < Box[i].size[j][1] )
				continue;

			//摆箱子
			Flag[i] = true;
			isAva = true;
			dfs(deep+1,n,Box[i].size[j][0],Box[i].size[j][1]);
			if ( isHalt ) return;
			Flag[i] = false;
		}
	}

	//如果这一次递归中没有摆过任何箱子，则可以记录中间结果
	if ( !isAva && deep > Ans ) Ans = deep;
}

int main(){
	int n,kase = 0;
	while( scanf("%d",&n) && n ){
        input(n);

		Ans = 0;
		fill(Flag,Flag+n,false);
		isHalt = false;

		for(int i=0;i<n;++i){
			Flag[i] = true;
			for(int j=0;j<Box[i].cnt;++j){
			    //以第i个箱子的第j面为底
			    int s1 = Box[i].size[j][0];
			    int s2 = Box[i].size[j][1];

			    dfs(1,n,s1,s2);
			}
			Flag[i] = false;
		}

		++kase;
		printf("Case %d: %d\n",kase,Ans);
	}
	return 0;
}