#include <iostream>
#include <vector>
#include <algorithm>

bool canDrive(const std::vector<int> &speeds, int n, int k, int64_t target)
{
    int64_t left = n;
    for(int i=0; i<std::min(k, n); i++)
    {
        int64_t numtrips = target / speeds[i];
        numtrips = (numtrips+1)/2;
        left -= 4*numtrips;
        if(numtrips > 0)
            left--;
    }
    return left <= 0;
}

int main()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> speeds(n);
    for(int i=0; i<n; i++)
        std::cin >> speeds[i];
        
    std::sort(speeds.begin(), speeds.end());
    
    int64_t low = 0;
    int64_t high = 20000LL*1000000LL;
    while(high - low > 1)
    {
        int64_t mid = low + (high-low)/2;
        if(canDrive(speeds, n, k, mid))
            high = mid;
        else
            low = mid;
    }
    
    std::cout << high << std::endl;
}
