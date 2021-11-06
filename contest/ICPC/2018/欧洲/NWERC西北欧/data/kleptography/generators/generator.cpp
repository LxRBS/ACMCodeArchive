// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

constexpr char A = 'a';
constexpr char Z = 'z';

bool check_char(char c){
    return c >= A && c <= Z;
}

ofstream inputfile, ansfile;

int gen_from_key_and_plain(string key, string plain){
    for(auto c: key)check_char(c);
    for(auto c: plain)check_char(c);
    ansfile << plain << endl;
    inputfile << key.size() << " " << plain.size() << endl;
    inputfile << plain.substr(plain.size() - key.size()) << endl;
    string both = key + plain;
    for(int i = key.size(); i < both.size(); i++){
        int v = (both[i] - A) + (both[i-key.size()] - A);
        v %= 26;
        inputfile << (char) (v + A);
    }
    inputfile << endl;
}

int gen_from_last_part_and_encrypted_text(string last_part, string encrypted){
    for(auto c: last_part)check_char(c);
    for(auto c: encrypted)check_char(c);
    int M = encrypted.size(), N = last_part.size();
    string plain;
    inputfile << N << " "<< M << endl<< last_part << endl <<  encrypted << endl;
    plain = encrypted;
    for(int i = 0; i < N; i++)
        plain[M-N+i] = last_part[i];
    for(int i = M-N-1; i >= 0; i--)plain[i] = (((encrypted[i+N] - A) - (plain[i+N] - A) + 26) % 26) + A;
    ansfile << plain << endl;
}

string randString(int L){
    ostringstream os;
    for(int i = 0; i < L; i++){
        os << (char)(A + (rand() % 26));
    }
    return os.str();
}

int main(){
    int gentype, seed;
    string fileprefix;
    cin >> gentype >> seed >> fileprefix;
    srand(seed);
    {
        string inputfilename = fileprefix + ".in";
        string ansfilename = fileprefix + ".ans";
        inputfile = ofstream(inputfilename.c_str());
        ansfile = ofstream(ansfilename.c_str());
    }
    if(gentype == 0){
        string key, plain;
        cin >> key >> plain;
        gen_from_key_and_plain(key,plain);
    } else if(gentype == 1){
        string last_part, encrypted;
        cin >> last_part >> encrypted;
        gen_from_last_part_and_encrypted_text(last_part, encrypted);
    } else if(gentype == 2){
        int A,B;
        cin >> A >> B;
        gen_from_key_and_plain(randString(A), randString(B));
    }

    {
        inputfile.close();
        ansfile.close();
    }
    return 0;
}
