/**
   n��m����������k�����ӣ�������k�����ӵĳ�ʼλ�á�
   Ȼ��ÿ�������ٸ���һ��Ŀ��λ�á�����λ�ÿ����ظ�
   ÿһ�β�������������ͳһ�ƶ�һ�������򣬳��Ƕ����ˣ�
   Ŀ����ÿ�����Ӿ��������Ŀ��λ�ã���2nm������֮�ڡ�
   �������Ƚ��������Ӷ��ƶ���(1, 1)�����ֻҪn+m-2������
   Ȼ��һ��һ���ƶ����ɣ������Ҫnm-1������Ȼ������2nm�������Ŀ��
*/
#include <bits/stdc++.h>
using namespace std;
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

char A[110000];
vector<int> V[210];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    int k = getInt();
    int right=0,bottom=0;
    for(int i=0;i<k;++i){
        int x = getInt();
        int y = getInt();
        right = max(right,y);
        bottom = max(bottom,x);
    }
    --right;--bottom;
    fill(A,A+right,'L');
    fill(A+right,A+right+bottom,'U');
    int tt = right+bottom;
    bottom = 0;
    for(int i=0;i<k;++i){
        int x = getInt();
        int y = getInt();
        V[x].push_back(y);
        bottom = max(bottom,x);
    }
    k = bottom;
    sort(V[k].begin(),V[k].end());
    for(int i=0,nn=k&1?k-1:k-2;i<nn;i+=2){
        fill(A+tt,A+tt+m-1,'R');
        A[tt+=m-1] = 'D';
        ++tt;
        fill(A+tt,A+tt+m-1,'L');
        A[tt+=m-1] = 'D';
        ++tt;
    }
    if(k&1){
        fill(A+tt,A+tt+V[k].back()-1,'R');
        tt += V[k].back()-1;
    }else{
        fill(A+tt,A+tt+m-1,'R');
        A[tt+=m-1] = 'D';
        ++tt;
        fill(A+tt,A+tt+m-*V[k].begin(),'L');
        tt += m-*V[k].begin();
    }
    printf("%d\n",tt);
    puts(A);
    return 0;
}
