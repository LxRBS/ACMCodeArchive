/**
   �����Σ�N����
   ÿ��ѡһ�������Բ����չ��ֱ��Բ����֮ǰ��Բ���߽߱�
   �����ʣ�µĿռ������Ƕ���
   N������6
*/
#include <bits/stdc++.h>
using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-8;
int sgn(double x){if(fabs(x)<EPS)return 0;return x>0?1:-1;}

int const FAC[] = {1,1,2,6,24,120,720};
double X[11],Y[11];
int A[] = {0,1,2,3,4,5};
int N;
int Left,Bottom,Top,Right;

double R[11];
//�����Ե�ǰ˳��õ������
double f(){
    double ans = (Right-Left)*(Top-Bottom);
    for(int i=0;i<N;++i){
        int ai = A[i];
        //�����i����ĺϷ��뾶
        //���ȼ�����������ܵİ뾶
        double r = X[ai]-Left;
        r = min(r,Right-X[ai]);
        r = min(r,Top-Y[ai]);
        r = min(r,Y[ai]-Bottom);
        //������֮ǰ��Բ�Ӵ��İ뾶
        for(int j=0;j<i;++j){
            int aj = A[j];
            double x = X[ai]-X[aj], y = Y[ai]-Y[aj];
            double tmp = sqrt(x*x+y*y) - R[aj];
            r = min(r,tmp);
            if(sgn(r)<=0){
                r = 0;
                break;
            }
        }
        R[ai] = r;
        ans -= PI*r*r;
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d%d%d",&N,&Left,&Bottom,&Right,&Top);
    for(int i=0;i<N;++i)scanf("%lf%lf",X+i,Y+i);
    if(Left>Right)swap(Left,Right);
    if(Bottom>Top)swap(Bottom,Top);

    double ans = (Right-Left)*(Top-Bottom);
    for(int i=0,n=FAC[N];i<n;++i){
        ans = min(ans,f());
        next_permutation(A,A+N);
    }
    printf("%.0f\n",ans);
    return 0;
}
