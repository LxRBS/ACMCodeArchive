#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;
    int len = s.length();
    
    int ascore = 0;
    int bscore = 0;
    int idx=0;
    bool bytwo = false;
    while(true)
    {
        char p = s[idx++];
        char score = s[idx++];
        (p == 'A' ? ascore : bscore) += (score - '0');
        if(ascore == 10 && bscore == 10)
            bytwo = true;
        if(bytwo)
        {
            if(ascore >= bscore + 2)
            {
                std::cout << 'A' << std::endl;
                return 0;
            }
            else if(bscore >= ascore + 2)
            {
                std::cout << 'B' << std::endl;
                return 0;
            }
        }
        else
        {
            if(ascore >= 11)
            {
                std::cout << 'A' << std::endl;
                return 0;
            }
            else if(bscore >= 11)
            {
                std::cout << 'B' << std::endl;
                return 0;
            }
        }
    }            
}
