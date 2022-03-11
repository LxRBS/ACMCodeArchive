/**
 * ����һ�а׸�D��������N��Ϳ�ڣ������ڸ�֮��İ׸���������Сֵ��������
 * �ر�ģ���һ���ڸ�ǰ��İ׸�����ҲҪ����Ƚϡ�
 * ���������ƶ�һ���ڸ��λ�ã�����ԭλ�ñ��������һ���׸���
 * ���ƶ�����������Ƕ��٣�N��2E5��D��1E9
 * ��Ȼ���Զ��֣��Ը���x�����Ƿ񾭹�һ�β��������඼���ڵ���x
 * ���ȼ��һ��������࣬����ϸ��ֱ�ӷ�����
 * ����м��С��x������������2���϶��Ͳ�����
 * ���С��x�ļ������Ϊ2�������Ƿֿ��ģ���Ҳ����
 * ���С��x�ļ������Ϊ2����������һ������뽫�м��Ǹ����ߣ����Ƿ�����
 * ���С��x�ļ��ֻ��һ����������ƶ����Ҳ�����ұߣ���һ�����㼴��
 * �����ܷ��ҵ��µ�λ�÷��£��������һ�¼��ɣ�����м����ڵ���2x+2���Ϳ��Է�
 * ͷβ��������һ�¡�NlogD
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 37;
#else
int const SIZE = 2E5+10;
#endif

typedef pair<int, int> pii;
int N, D;
int A[SIZE] = {0};

bool isOK(int gap, int idx){
    if(0 == idx) return false;	
	if(A[idx+1] - A[idx-1] < gap + 1) return false;    
	if(A[idx+1] - A[idx-1] >= gap + gap + 2) return true;		
    /// ֱ�ӷ������һ������
	if(idx != N && D - A[N] >= gap + 1) return true;
	if(idx == N && D - A[N-1] >= gap + 1) return true;

    for(int i=0;i<idx;++i){
		if(A[i+1] - A[i] >= gap + gap + 2){
			return true;
		}
	}
	for(int i=idx+1;i<N;++i){
		if(A[i+1] - A[i] >= gap + gap + 2){
			return true;
		}
	}
	return false;
}

bool check(int gap){	
	vector<pii> vec;
    for(int i=1;i<=N;++i){
        if(A[i] - A[i-1] < gap + 1){
			vec.emplace_back(i-1, i);
		}
	}
	if(vec.empty()) return true;
	if(vec.size() > 2) return false;
	if(2 == vec.size()){
		if(vec.front().second != vec.back().first){
			return false;
		}
		if(isOK(gap, vec.front().second)){
			return true;
		}
		return false;
	}
    if(isOK(gap, vec.front().first)){
		return true;
	}	
	if(isOK(gap, vec.front().second)){
		return true;
	}
	return false;
}

int proc(){
    int left = 0, right = D, mid;
	do{
		int mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
		else right = mid - 1;
	}while(left <= right);
	return right;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	for(int kase=1;kase<=nofkase;++kase){
	    N = getInt(); D = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
		A[N+1] = D + 1;
        printf("%d\n", proc());
	}
    return 0;
}
