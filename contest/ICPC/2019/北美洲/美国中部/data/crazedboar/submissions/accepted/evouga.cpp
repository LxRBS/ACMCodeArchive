#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

bool headTree(double x, double y, double r, double b, double d, double &theta1, double &theta2)
{
    double px = y;
    double py = -x;
    double p = std::sqrt(x*x+y*y);
    double dist = (p*p + d*d - (b+r)*(b+r)) / 2.0 / p;
    double perpsq = d*d - dist*dist;
    if(perpsq <= 0)
        return false;
    double perp = std::sqrt(perpsq);
    
    double x1 = dist * x / p + perp * px / p;
    double y1 = dist * y / p + perp * py / p;
    theta1 = std::atan2(y1, x1);
    double x2 = dist * x / p - perp * px / p;
    double y2 = dist * y / p - perp * py / p;
    theta2 = std::atan2(y2, x2);
    return true;
}

bool flankTree(double x, double y, double r, double b, double d, double &theta1, double &theta2)
{
    double l = std::sqrt( x*x + y*y - (r+b)*(r+b) );
    if(l > d)
        return false;
    double p = std::sqrt( x*x + y*y );
    double sint = l/p;
    double cost = (r+b)/p;
    double vx = -x * (r+b) / p;
    double vy = -y * (r+b) / p;
    double w1x = cost * vx - sint * vy;
    double w1y = sint * vx + cost * vy;
    theta1 = std::atan2(y + w1y, x + w1x);
    double w2x = cost * vx + sint * vy;
    double w2y = -sint * vx + cost * vy;
    theta2 = std::atan2(y + w2y, x + w2x);
    return true;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<double> xs(n);
    std::vector<double> ys(n);
    std::vector<double> rs(n);
    for(int i=0; i<n; i++)
        std::cin >> xs[i] >> ys[i] >> rs[i];
    double b, d;
    std::cin >> b >> d;
    
    struct Event
    {
        double theta;
        bool begin;
        
        bool operator<(const Event &other) const
        {
            return theta < other.theta;
        }
    };
    
    int treecnt = 0;
    std::vector<Event> events;
    
    for(int i=0; i<n; i++)
    {
        double theta1, theta2;
        if(headTree(xs[i], ys[i], rs[i], b, d, theta1, theta2) && theta1 != theta2)
        {
            //std::cout << "head " << theta1 << " " << theta2 << std::endl;
            events.push_back({theta1, true});
            events.push_back({theta2, false});
            if(theta2 < theta1)
                treecnt++;
        }
    }
    
    for(int i=0; i<n; i++)
    {
        double theta1, theta2;
        if(flankTree(xs[i], ys[i], rs[i], b, d, theta1, theta2) && theta1 != theta2)
        {
            //std::cout << "flank " << theta1 << " " << theta2 << std::endl;
            events.push_back({theta1, true});
            events.push_back({theta2, false});
            if(theta2 < theta1)
                treecnt++;
        }
    }
    std::sort(events.begin(), events.end());
    double totlen = 0;
    double PI = 3.1415926535898;
    double last = -PI;
    for(auto &it : events)
    {
        if(treecnt == 0)
            totlen += it.theta - last;
        last = it.theta;
        if(it.begin)
            treecnt++;
        else
            treecnt--;
    }
    if(treecnt == 0)
        totlen += (PI - last);
    double prob = totlen / (2.0*PI);
    std::cout << std::setprecision(30) << prob << std::endl;
}
