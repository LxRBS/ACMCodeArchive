#include <iostream>
#include <vector>
#include <string>

using namespace std;

int Char_To_Int(char c){
  if(c >= 'A' && c <= 'Z')
    return c - 'A';
  else if(c >= '0' && c <= '9')
    return c - '0' + 26;
  else if(c == ' ')
    return 36;
  else
    cout << "ERROR: Illegal character " << c << endl;
}

char Int_To_Char(int n){
  if(n >= 0 && n < 26)
    return 'A' + n;
  else if(n >= 26 && n < 36)
    return '0' + n-26;
  else if(n == 36)
    return ' ';
  else
    cout << "ERROR: Illegal int " << n << endl;
}

void Convert(const vector<int>& line, const vector<vector<int> >& matrix, vector<char>& ciphertext){
  for(int i = 0; i < line.size(); i++){
    int total = 0;
    for(int j = 0; j < line.size(); j++){
      total = total + matrix[i][j]*line[j];
    }
    total = total % 37;
    ciphertext[i] = Int_To_Char(total);
  }
}

int main(){
  int n;
  cin >> n;
  vector<vector<int> >matrix(n);
  for(int i = 0; i < n; i++){
    matrix[i].resize(n);
    for(int j = 0; j < n; j++)
      cin >> matrix [i][j];
  }

  cin.get();
  string plaintext;
  getline(cin, plaintext);
  while(plaintext.size() % n != 0)
    plaintext = plaintext + ' ';
  for(int pos = 0; pos < plaintext.size(); pos = pos + n){
    string line = plaintext.substr(pos, n);
    vector<int> line_ints(n);
    for(int i = 0; i < n; i++){
      line_ints[i] = Char_To_Int(plaintext[pos+i]);
    }
    vector<char> ciphertext(n);
    Convert(line_ints, matrix, ciphertext);
    for(int i = 0; i < ciphertext.size(); i++)
      cout << ciphertext[i];
  }
  cout << endl;
  return 0;
}

  
