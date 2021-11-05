/**
    ����һ������Σ�ָ��һ��Ŀ��㣬�����¹����н���
    1. �ӵ�ǰ�㣬��Ŀ��㷽��ֱ���ߣ�ֱ��ײǽ
    2. ײǽ�Ժ��������Ŀ���ķ�����ǽ�ߣ�ֱ���뿪���ǽ���߸պô�ֱ
    3. �����ֱ��������ǽ���߲�������ʧ��
    �ʣ��ڶ�������Ƿ����ҵ�һ��Ŀ��㣬ʹ�����е㶼�ܹ�����
    1000����
    ���������͹����α�ȻOK
    ��μ���ֻ��֤����εĽ��㼴�ɣ�û��֤����
    ��ÿ���������֤����ÿ���ߣ�
    �������ԣ�˵��Ҫ�뿪�����ߣ����ù�
    ����Ǳ��ԣ�˵��Ҫ�ر��ߡ���������ڱ��ϣ���ʧ��
    �����Ȼ�ߵ�����һ�����㣬��֤�����Ƿ�Ϊ���Ǽ���
*/
#include<bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct point_t{
    int x,y;
    point_t(int a=0,int b=0):x(a),y(b){}
}P[1010], NormVec[1010];

int cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}
int dot(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}
int N;
bool read(){
    while(1!=scanf("%d",&N)) return false;
    for(int i=0;i<N;++i){
        P[i].x = getUnsigned();
        P[i].y = getUnsigned();
    }
    P[N] = P[0];
    return true;
}

//�ж��Ƿ�Ϊ͹��
bool isConvex(point_t const p[],int n){
    int status = 0;

    for(int tmp,i=1;i<n;++i){
        tmp = cross(p[i-1],p[i],p[i+1]);
        if(tmp<0) status |= 2;
        else if(tmp>0) status |= 1;
        if(status==3) return false;
    }
    //��Ŀ��֤��˳ʱ�뷽��
    if(status==1) throw runtime_error("XXXXX");
    return true;
}

//����idx�������Ƿ�����ΪĿ��
bool check(int idx){
    //��ÿ�����ж����Ƿ���Ի��Ǳ���
    //������ԵĻ����ж��䴹���Ƿ�ǡ�����߶���
    //������㲻���߶��ϣ��ж��������ŵ����ĸ�����
    int cnt[1010] = {0};
    for(int i=0;i<N;++i)if(i!=idx&&i+1!=idx){
        //���ȼ�����
        int tmp = cross(P[i],P[i+1],P[idx]);
        if(tmp<0){//��ԣ���ʱ���뿪�����ߣ��������ж�
            continue;
        }
        //��ʱ�����ű��ߣ���Ҫ���
        int d1 = dot(P[i],P[i+1],P[idx]);
        int d2 = dot(P[i+1],P[i],P[idx]);
        if(d1>0&&d2>0){//��ʱ˵�������ڱ��м䣬����
            return false;
        }
        //�ж���ŵ�
        if(d1<=0){//��ŵ���Pi
            if(++cnt[i]>1){//�����߶�����Pi������һ������
                return false;
            }
        }else if(d2<=0){
            if(++cnt[i+1]>1){
                return false;
            }
        }else{
            throw runtime_error("XXXX");
        }
    }
    return true;
}

bool proc(){
    //�����͹����Σ��϶�OK
    if(isConvex(P,N)) return true;

    //����ÿ���ߵķ�������˳ʱ�룬������ʼ��ָ���ұ�
    /*
    for(int i=0;i<N;++i){
        NormVec[i].x = P[i+1].y-P[i].y;
        NormVec[i].y = P[i].x-P[i+1].x;
    }//*/

    //��ÿ�����������ΪĿ��㣬������֤
    for(int i=0;i<N;++i){
        if(check(i)) {
            //printf("%d: (%d, %d)\n",i, P[i].x, P[i].y);
            return true;
        }
    }
    return false;
}
int main(){
    //freopen("1.txt","r",stdin);

    char a[][20] = {"DANGER","SAFETY"};
    while(read()){
        puts(a[proc()?1:0]);
    }
    return 0;
}

