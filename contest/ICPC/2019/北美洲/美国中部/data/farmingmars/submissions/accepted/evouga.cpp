#include <iostream>
#include <vector>
#include <map>

struct SegTree
{
    int l,r;
    int bitcounts[24];
    std::map<int, int> counts;
    SegTree *left, *right;
    
    SegTree(const std::vector<int> &pHs, int l, int r) : l(l), r(r)
    {
        if(r-l > 0)
        {
            int mid = (r+l)/2;
            left = new SegTree(pHs, l, mid);
            right = new SegTree(pHs, mid+1, r);
            for(int i=0; i<24; i++)
            {
                bitcounts[i] = left->bitcounts[i] + right->bitcounts[i];
            }
            for(auto it : left->counts)
                counts[it.first] += it.second;
            for(auto it : right->counts)
                counts[it.first] += it.second;            
        }
        else
        {
            left = NULL;
            right = NULL;
            int val = pHs[l];
            counts[val] = 1;
            for(int i=0; i<24; i++)
            {
                bitcounts[i] = ((val & (1<<i)) ? 1 : 0);
            }
        }
    }
    
    void totBits(int ql, int qr, std::vector<int> &bits)
    {    
        if(ql <= l && r <= qr)
        {
            for(int i=0; i<24; i++)
                bits[i] += bitcounts[i];
        }
        else if(ql > r || qr < l)
        {
            return;
        }
        else
        {
            if(left) left->totBits(ql, qr, bits);
            if(right) right->totBits(ql, qr, bits);
        }
    }
    
    int totCount(int ql, int qr, int val)
    {
        if(ql <= l && r <= qr)
        {
            auto it = counts.find(val);
            if(it != counts.end())
                return it->second;
            return 0;
        }
        else if(ql > r || qr < l)
            return 0;
        int tot = 0;
        if(left) tot += left->totCount(ql, qr, val);
        if(right) tot += right->totCount(ql, qr, val);
        return tot;
    }
    
    ~SegTree()
    {
        if(left) delete left;
        if(right) delete right;
    }
};

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> ph(n);
    for(int i=0; i<n; i++)
    {
        int head;
        char period;
        int tail;
        std::cin >> head >> period >> tail;
        ph[i] = head*1000000 + tail;
    }
    SegTree *root = new SegTree(ph, 0, n-1);
    
    for(int i=0; i<m; i++)
    {
        int l, r;
        std::cin >> l >> r;
        l--; r--;
        std::vector<int> bits(24);
        root->totBits(l, r, bits);
        int val = 0;
        int maj = (r-l+1)/2 + 1;
        for(int j=0; j<24; j++)
        {
            if(bits[j] >= maj)
                val |= (1<<j);
        }
        if(root->totCount(l, r, val) >= maj)
            std::cout << "usable" << std::endl;
        else
            std::cout << "unusable" << std::endl;
    }
}
