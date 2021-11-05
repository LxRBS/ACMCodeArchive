#include <cstdio>
#include <algorithm>
using namespace std;

//P����ָʾ����ʾָ������ʱ������ܵ�����
bool P[10][7] = {
	{true, true,true, true, true, true, false},
	{false,true, true,false,false,false,false},
	{true, true,false,true, true, false,true},
	{true, true,true, true, false,false,true},
	{false,true,true, false,false,true, true},
	{true, false,true, true,false,true, true},
	{true, false,true, true,true, true, true},
	{true, true,true, false,false,false,false},
	{true, true,true, true, true, true, true},
	{true, true,true, true, false,true, true}
};
bool B[10][10] = {
	//  0     1     2     3     4     5     6     7     8    9
	true, false,false,false,false,false,false,false,true,false,
	true, true, false,true, true, false,false,true, true,true,
	false,false,true, false,false,false,false,false,true,false,
	false,false,false,true, false,false,false,false,true,true,
	false,false,false,false,true, false,false,false,true,true,
	false,false,false,false,false,true, true, false,true,true,
	false,false,false,false,false,false,true, false,true,false,
	true, false,false,true, false,false,false,true, true,true,
	false,false,false,false,false,false,false,false,true,false,
	false,false,false,false,false,false,false,false,true,true
};

int N;
int Hour[51],Minu[51];
int A[28];//��־λ
//t1��ʾ��ʾ��t2��ʾʵ��ֵ
inline bool comp(int t1,int t2,int a[]){
	if ( !B[t1][t2] ) return false;//��ʾ��ʾֵ�����ܶ�Ӧʵ��ֵ

    for(int i=0;i<7;++i){
		if (P[t1][i]){//t1����t2��Ȼ������������
			if ( 0 == a[i] || 1 == a[i] ) a[i] = 1;//1������������
			else return false;
		}else if(P[t2][i]){//t1��t2����������
			if ( 0 == a[i] || 2 == a[i] ) a[i] = 2;//2������
			else return false;
		}//t1��t2���𣬴���δ֪		
	}
	return true;
}
inline int addHour(int h){return 24 == ++h ? 0 : h;}
inline int addMinu(int m){return 60 == ++m ? 0 : m;}
inline bool isRight(int hour,int minu,int idx){
	//����ʱ��ʮλ
	if ( !comp(Hour[idx]/10,hour/10,A) ) return false;
	//����ʱ�Ӹ�λ
	if ( !comp(Hour[idx]%10,hour%10,A+7) )return false;
	if ( !comp(Minu[idx]/10,minu/10,A+14) ) return false;
	if ( !comp(Minu[idx]%10,minu%10,A+21) ) return false;
	return true;
}
bool isRight(int hour,int minu){
	fill(A,A+28,0);
	for(int i=0;i<N;++i){
		if ( !isRight(hour,minu,i) )
			return false;
	
		minu = addMinu(minu);
		if ( 0 == minu ) hour = addHour(hour);
	}
	return true;
}
int main(){
	while( EOF != scanf("%d",&N) ){
        for(int i=0;i<N;++i)scanf("%d:%d",Hour+i,Minu+i);
		
		bool flag = false;
		for(int h=0;h<24;++h)for(int m=0;m<60;++m){
			if ( !isRight(h,m) ) continue;
			if ( flag ) printf(" ");
			printf("%02d:%02d",h,m);
			flag = true;
		}
		if ( !flag ) printf("none");
		printf("\n");
	}
	return 0;
}