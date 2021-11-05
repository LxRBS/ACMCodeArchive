#include <iostream>
#include <set>
#include <bitset>
#include <map>
using namespace std;

int const MAXSIZE = 500;
struct Board_t{
	int row;
	int col;
	unsigned char flag[MAXSIZE];
	bool operator < ( const Board_t & right ) const{
		if ( row != right.row ) return row < right.row;
		if ( col != right.col ) return col < right.col;
		int i,j;
		for(i=0;i<row;i++)for(j=0;j<col;j++)
			if ( flag[i*col+j] != right.flag[i*col+j] )
				return flag[i*col+j] < right.flag[i*col+j];
		return false;	
	}
	unsigned char & operator () (int i, int j) {
		return flag[i*col+j];
	}
}Board;//棋盘
map<Board_t,int> SG;
typedef map<Board_t,int>::iterator ItMapSG;

//计算当前棋盘的SG值
int sg(void){
	ItMapSG it = SG.find(Board);
	if ( it != SG.end() ) return SG[Board];
	int i,j;
	bool flag[MAXSIZE] = {false};
	for(i=0;i<Board.row-1;i++)for(j=0;j<Board.col-1;j++){
		if ( Board(i,j) == 0 && Board(i+1,j) == 0
			&& Board(i,j+1) == 0 && Board(i+1,j+1) == 0 ){
				Board(i,j) = Board(i+1,j) = Board(i,j+1) = Board(i+1,j+1) = 1;
				int k = sg();
				//			cout<<i<<" "<<j<<' '<<k<<endl;
				flag[k] = true;
				Board(i,j) = Board(i+1,j) = Board(i,j+1) = Board(i+1,j+1) = 0;
		}
	}
	for(i=0;;i++)if( !flag[i] )
		return SG[Board] = i; 
}
void dispBoard(){
	int i,j;
	for(i=0;i<Board.row;i++){
		for(j=0;j<Board.col;j++)
			cout<<(int)Board(i,j);
		cout<<endl;
	}
}
int main(){
	int N,n,m;
	int i,j;
	char t;
	while( cin>>N ){
		int out = 0;
		while( N-- ){
			cin>>n>>m;
			Board.row = n;
			Board.col = m ;
			for(i=0;i<Board.row;i++)for(j=0;j<Board.col;j++){
				cin>>t;
				if ( t == '1' ) Board(i,j) = 1;
				else			Board(i,j) = 0;
			}
			out ^= sg();
		}
		cout<<(out?"Yes\n":"No\n");
	}
	return 0;
}
