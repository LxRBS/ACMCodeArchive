//��֪����A����S=A+A^2+...+A^k
//�����ֿ����
//X = | A I |
//    | 0 I |
//��  X^n = | A^n I+A+...+A^(n-1) |
//         | 0   I               |
//ֻ�����X^(n+1)�������Ͻ��Ӿ����ټ�ȥ��λ�󼴴�
#include <cstdio>
#include <algorithm>
using namespace std;

typedef int value_type;
struct matrix_t{
	enum {SIZE=120};
    value_type data[SIZE*SIZE];
    int row;
    int col;

public:
    value_type const& at(int i,int j)const{return data[i*col+j];}
    value_type& at(int i,int j){return data[i*col+j];}
    void identity(int n);//���Լ���Ϊ��λ��
    void clear(){row=col=0;fill(data,data+SIZE*SIZE,(value_type)0);}
    void disp(FILE*fp)const;
    //����������
    void fillMat(value_type const a[],int startr,int startc,int rows,int cols);
    //�Ӿ���
    matrix_t sub(int startr,int startc,int rows,int cols)const;

    //default constructor
    matrix_t(int r=0,int c=0):row(r),col(c){fill(data,data+SIZE*SIZE,(value_type)0);}
    //copy constructor
    matrix_t(matrix_t const& rhs):row(rhs.row),col(rhs.col){
    	copy(rhs.data,rhs.data+row*col,data);
    }
    //constructor with 1d array
    matrix_t(value_type const a[],int r,int c):row(r),col(c){
    	copy(a,a+row*col,data);
    }

    //assignment operator
    matrix_t& operator = (matrix_t const& rhs);
    //compound assignment operator
    matrix_t& operator += (matrix_t const& rhs);
    matrix_t& operator -= (matrix_t const& rhs);
    matrix_t& operator %= (int mod);
};

void matrix_t::disp(FILE*fp)const{
	for(int i=0;i<row;++i){
		for(int j=0;j<col-1;++j)fprintf(fp,"%d ",at(i,j));
		fprintf(fp,"%d\n",at(i,col-1));
	}
}

void matrix_t::identity(int n){
	this->clear();
	row = col = n;
	for(int i=0;i<row;++i)at(i,i) = 1;
}

matrix_t& matrix_t::operator = (matrix_t const&rhs){
	row = rhs.row;col = rhs.col;
	copy(rhs.data,rhs.data+row*col,data);
    return *this;
}

matrix_t& matrix_t::operator += (matrix_t const&rhs){
	for(int i=0;i<row;++i)for(int j=0;j<col;++j)at(i,j) += rhs.at(i,j);
    return *this;
}

matrix_t& matrix_t::operator -= (matrix_t const&rhs){
	for(int i=0;i<row;++i)for(int j=0;j<col;++j)at(i,j) -= rhs.at(i,j);
    return *this;
}

matrix_t& matrix_t::operator %= (int mod){
	for(int i=0;i<row;++i)for(int j=0;j<col;++j){
        at(i,j) %= mod;
        if ( at(i,j) < 0 ) at(i,j) += mod;
	}
    return *this;
}

matrix_t operator + (matrix_t const&lhs,matrix_t const&rhs){
	matrix_t ret(lhs);
	return ret += rhs;
}

matrix_t operator - (matrix_t const&lhs,matrix_t const&rhs){
	matrix_t ret(lhs);
	return ret -= rhs;
}

matrix_t operator % (matrix_t const&lhs,int mod){
	matrix_t ret(lhs);
	return ret %= mod;
}

matrix_t operator * (matrix_t const&lhs,matrix_t const&rhs){
	matrix_t ret(lhs.row,rhs.col);
	for(int i=0;i<ret.row;++i)for(int k=0;k<lhs.col;++k){
        if ( lhs.at(i,k) ) for(int j=0;j<ret.col;++j)
        	ret.at(i,j) += lhs.at(i,k) * rhs.at(k,j);
	}
	return ret;
}

void matrix_t::fillMat(value_type const a[],int startr,int startc,int rows,int cols){
    int k = -1;
	for(int i=startr;i<startr+rows;++i)for(int j=startc;j<startc+cols;++j)
		at(i,j) = a[++k];
}

matrix_t matrix_t::sub(int startr,int startc,int rows,int cols)const{
    matrix_t ret(rows,cols);
    for(int i=0;i<ret.row;++i)for(int j=0;j<ret.col;++j)
    	ret.at(i,j) = this->at(i+startr,j+startc);
    return ret;
}

//�������ȡģ�������ԶΪ[0,mod)
matrix_t mulMod(matrix_t const&lhs,matrix_t const&rhs,int const mod){
	matrix_t ret(lhs.row,rhs.col);
	for(int i=0;i<ret.row;++i)for(int k=0;k<lhs.col;++k){
        if ( lhs.at(i,k) ) for(int j=0;j<ret.col;++j){
        	ret.at(i,j) += lhs.at(i,k) * rhs.at(k,j);
			ret.at(i,j) %= mod;
			if ( ret.at(i,j) < 0 ) ret.at(i,j) += mod;
        }
	}
	return ret;
}
//mat��n�η���modȡģ��������
matrix_t powerMod(matrix_t mat,int n,int mod){
    if ( 1 == n ) return mat % mod;
    //������λ��
    matrix_t ret;
    ret.identity(mat.row);
    if ( 0 == n ) return ret;

    while( n ){
    	if ( n & 1 ) ret = mulMod(ret,mat,mod);
    	mat = mulMod(mat,mat,mod);
    	n >>= 1;
    }
    return ret;
}
int A[900];
int main(){
	int n,k,mod;
	scanf("%d%d%d",&n,&k,&mod);
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)scanf("%d",A+i*n+j);
	//��λ��
	matrix_t unit;
	unit.identity(n);
	//���������
	matrix_t mat(n+n,n+n);
	mat.fillMat(A,0,0,n,n);
    mat.fillMat(unit.data,0,n,n,n);
    mat.fillMat(unit.data,n,n,n,n);
    //����
    matrix_t a = powerMod(mat,k+1,mod);
    //ȡ�Ӿ���
    matrix_t b = a.sub(0,n,n,n);
    //��ȥ��λ��
    b -= unit;
    //ȡģ
    b %= mod;
    //���
    b.disp(stdout);
}
