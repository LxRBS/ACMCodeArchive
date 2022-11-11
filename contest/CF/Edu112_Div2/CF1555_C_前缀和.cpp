/**
 * ��һ��2��M�ľ���ÿһ���зǸ�����
 * Alice���ߣ��������ϵ������£�ֻ�����һ������£�����;�����ӵ��������ߣ��������Ժ�Ͳ�������
 * Bob���ߣ�����һ����
 * Aliceϣ��Bob���ߵ�������ԽСԽ�ã�Bob��ϣ��Խ��Խ��
 * ��˫�����ŵ�����£�Bob�����õ�����
 * Alice�õ�������Ȼ�ǵ�һ�е�ǰ��κ͵ڶ��еĺ��Ρ�
 * Bob�õ���Ҫô�ǵ�һ�еĺ��Σ�Ҫô�ǵڶ��е�ǰ��Ρ�
 * ��ǰ׺����һ����С���ֵ���ɡ�O(N)��
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE =100010;
#endif

typedef int llt;

llt M;
llt A[2][SIZE];
llt B[2][SIZE];

llt proc(){
    B[0][0] = A[0][0];
    B[1][0] = A[1][0];
    for(int j=1;j<M;++j){
        B[0][j] = B[0][j-1] + A[0][j];
        B[1][j] = B[1][j-1] + A[1][j];
    }

    llt ans = min(B[0][M-1]-A[0][0], B[1][M-2]);
    for(int i=1;i<M-1;++i){
        ans = min(ans, max(B[0][M-1]-B[0][i], B[1][i-1]));
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &M);
        for(int i=0;i<2;++i)for(int j=0;j<M;++j){
            scanf("%d", A[i]+j);
        }
        printf("%d\n", proc());
    }
    return 0;
}