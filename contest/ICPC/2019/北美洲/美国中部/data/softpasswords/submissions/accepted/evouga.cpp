#include <iostream>
#include <string>

std::string reversecase(std::string s)
{
    std::string result = s;
    for(int i=0; i<s.length(); i++)
    {
        if('A' <= s[i] && s[i] <= 'Z')
            result[i] = s[i] - 'A' + 'a';
        else if('a' <= s[i] && s[i] <= 'z')
            result[i] = s[i] - 'a' + 'A';        
    }
    return result;
}

int main()
{
    std::string s;
    std::string p;
    std::cin >> s >> p;
    
    bool ok = false;
    if(s == p)
        ok = true;
    for(int i=0; i<10; i++)
    {
        char digit[2] = {'0'+i, '\0'};
        std::string newp = std::string(digit) + p;
        if(newp == s)
            ok = true;
        newp = p + std::string(digit);
        if(newp == s)
            ok = true;        
    }
    if(reversecase(p) == s)
        ok = true;
    std::cout << (ok ? "Yes" : "No") << std::endl;
}
