#include <iostream>
#include <random>
#include <queue>
#include <vector>
#include <map>

typedef std::vector<std::vector<std::pair<int, int64_t> > > graph;

int64_t doSearch(const graph &g, const std::vector<std::vector<int> > &balls)
{
    struct Visit
    {
        int dest;
        int state;
        int64_t cost;
        bool operator<(const Visit &other) const
        {
            return cost > other.cost;
        }
    };
    
    int n = g.size();
    
    std::vector<std::vector<int64_t> > visited(127);
    for(int i=0; i<127; i++)
    {
        for(int j=0; j<n; j++)
            visited[i].push_back(std::numeric_limits<int64_t>::max());
    }
    
    
    std::priority_queue<Visit> pq;
    pq.push({0, 0, 0});
    while(!pq.empty())
    {
        Visit v = pq.top();
        pq.pop();
        if(visited[v.state][v.dest] < v.cost)
            continue;
            
        visited[v.state][v.dest] = v.cost;
        
        for(auto it : balls[v.dest])
        {
            v.state |= (1<<it);            
        }
        
        if(v.state == 127)
        {
            return v.cost;
        }
        
        for(auto &nb : g[v.dest])
        {
            int64_t newcost = v.cost + nb.second;
            if(newcost < visited[v.state][nb.first])
            {
                visited[v.state][nb.first] = newcost;
                pq.push({nb.first, v.state, newcost});
            }
        }
    }
    
    return -1;
}

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;
    graph g(n);
    for(int i=0; i<m; i++)
    {
        int a, b;
        int64_t t;
        std::cin >> a >> b >> t;
        g[a-1].push_back({b-1, t});
        g[b-1].push_back({a-1, t});
    }       
    std::vector<std::vector<int> > dballs(n);
    for(int i=0; i<k; i++)
    {
        int c, d;
        std::cin >> c >> d;
        dballs[c-1].push_back(d-1);
    }
    
    int tries = 1000;
    bool found = false;
    int64_t best = std::numeric_limits<int64_t>::max();
    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> balldist(0,6);
    
    for(int t=0; t<tries; t++)
    {
        std::vector<int> ballmap(n);
        for(int i=0; i<n; i++)
        {
            ballmap[i] = balldist(rng);
        }
        
        std::vector<std::vector<int> > mappedballs(n);
        for(int i=0; i<n; i++)
        {
            for(auto it : dballs[i])
            {
                mappedballs[i].push_back(ballmap[it]);
            }
        }
        
        int64_t cost = doSearch(g, mappedballs);
        if(cost != -1)
        {
            found = true;
            best = std::min(best, cost);
        }
    }
    
    if(!found)
        std::cout << "-1" << std::endl;
    else
        std::cout << best << std::endl;
}
