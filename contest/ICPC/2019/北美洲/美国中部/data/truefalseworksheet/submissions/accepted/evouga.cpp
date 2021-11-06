#include <iostream>
#include <string>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> sameprev(n);
    std::vector<int> diffprev(n);
    for(int i=0; i<n; i++)
    {
        sameprev[i] = n;
        diffprev[i] = -1;
    }
        
    for(int i=0; i<m; i++)
    {
        int l, r;
        std::string s;
        std::cin >> l >> r >> s;
        if(s == "same")
        {
            sameprev[r-1] = std::min(sameprev[r-1], l-1);            
        }
        else
        {
            diffprev[r-1] = std::max(diffprev[r-1], l-1);
        }
    }
    
    int64_t p = 1000000007;
    
    std::vector<int64_t> endtrue(n+1); // satisfies all constraints before position i and ends in T
    endtrue[0] = 1;
    for(int i=1; i<=n; i++)
    {
        // count ways to pad an existing answer with Ts
//        std::cout << "position " << i << " " << sameprev[i-1] << " " << diffprev[i-1] << std::endl;
        int upperbound = sameprev[i-1];
        int lowerbound = diffprev[i-1]+1;
        for(int j=i-1; j>=0; j--)
        {
            if(j >= lowerbound && j <= upperbound)
                endtrue[i] = (endtrue[i] + endtrue[j]) % p;
            if(j > 0)
            {
                upperbound = std::min(upperbound, sameprev[j-1]);
                lowerbound = std::max(lowerbound, diffprev[j-1]+1);
            }   
            
            
        }
    }
    
    int64_t answer = endtrue[n];
    answer = (answer * 2LL) % p;
    
    std::cout << answer << std::endl;
}
