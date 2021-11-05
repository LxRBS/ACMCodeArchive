#include <cstdio>
#include <algorithm>
using namespace std;

typedef int value_type;
struct matrix_t{
	enum {SIZE=2};
    value_type data[SIZE*SIZE];
    int row;
    int col;

public:
    value_type const& at(int i,int j)const{return data[i*col+j];}
    value_type& at(int i,int j){return data[i*col+j];}
    void identity(int n);//将自己变为单位阵
    void clear(){row=col=0;fill(data,data+SIZE*SIZE,(value_type)0);}

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
    matrix_t& operator %= (int mod);
};

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
//矩阵相乘取模，结果永远为[0,mod)
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
//mat的n次方对mod取模，快速幂
matrix_t powerMod(matrix_t mat,int n,int mod){
    if ( 1 == n ) return mat % mod;
    //创建单位阵
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
int const MOD = 10000;
int A[4] = {1,1,1,0};
int main() {
	matrix_t mat(A,2,2);

	int n;
	while( scanf("%d",&n) && n != -1 ){
        matrix_t r = powerMod(mat,n,MOD);
        printf("%d\n",r.at(0,1));
	}
	return 0;
}
