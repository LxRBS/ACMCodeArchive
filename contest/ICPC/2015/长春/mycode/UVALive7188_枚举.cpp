/*
  �������飬���Ƿ��ܹ���
  ���ֻ�Ƴ�һ����ʹ��ʣ�µ�������

  ������ɨ��һ�齵��ɨ��һ��
  ����˳��һ�£��򵱳���������ȻҪɾ��һ��
  ������ȷ��ɾ������
  �ڶ���ɨ��ʱҪע�⻹ԭ������ֱ�Ӹ���һ������
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

    //��k��ʼ�ж�
    //��ԭ�õı���
    int ov1 = -1, ovi = -1;
    int op = -1;
    //�Ȱ������ж�һ��
    int cnt = 0;
    bool flag = true;
    for(int i=k+1;i<N;++i){
        if(A[i-1]>A[i]){
            if(1==cnt){
                flag = false;
                break;
            }
            ++cnt;
            if(1==i){//ֻ��ȥ��A[0]
                continue;
            }
            if(A[i]<A[i-2]){//ֻ��ȥ��Ai
                //��¼ԭʼ����
                ovi = A[op=i],ov1 = A[i-1];
                A[i] = A[i-1];
                A[i-1] = A[i-2];
            }else{//ȥ��A[i-1]����
                ovi = A[op=i-1];
                A[i-1] = A[i-2];
            }
        }
    }
    if(flag) return true;
    //��ԭ
    A[op] = ovi;
    if(-1!=ov1) A[op-1] = ov1;
    //�ٰ��ݼ���һ��
    cnt = 0;
    flag = true;
    for(int i=k+1;i<N;++i){
        if(A[i-1]<A[i]){
            if(1==cnt){
                flag = false;
                break;
            }
            ++cnt;
            if(1==i){//ֻ��ȥ��A[0]
                continue;
            }
            if(A[i]>A[i-2]){//ֻ��ȥ��Ai
                A[i] = A[i-1];
                A[i-1] = A[i-2];
            }else{//ȥ��A[i-1]����
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


