/**
   给一个有向图，每个点有正权值
   求一条路径，使得点权和最大
   要求输出方案
   令di为到i点时能够拿到的最大权值，显然
   di = max(d[from]) + ai
   使用拓扑排序来确定DP顺序，并使用刷表法即可
*/
class Solution {
public:
    vector<vector<int> > g;
    int degree[300];
    int pre[300];
    int d[300];

    string int2string(int n){
        stringstream ss;
        ss<<n;
        return ss.str();
    }

    /**
     *
     * @param potatoNum int整型vector 依次表示序号为1,2,3..的番薯洞各有多少个番薯
     * @param connectRoad int整型vector<vector<>> 每个一维数组[x,y]表示从第x号番薯洞到第y号有路
     * @return string字符串
     */
    string digSum(vector<int>& potatoNum, vector<vector<int> >& connectRoad) {
        //建图
        int n = potatoNum.size();
        g.assign(n+1, vector<int>());
        fill(degree,degree+n+1,0);
        fill(d,d+n+1,0);
        fill(pre,pre+1,0);

        for(vector<vector<int> >::const_iterator it=connectRoad.begin();it!=connectRoad.end();++it){
            vector<int>const& v = *it;
            g[v[0]].push_back(v[1]);
            ++degree[v[1]];
        }

        //队列，把度为0的全塞进去
        queue<int> q;
        for(int i=1;i<=n;++i)if(!degree[i]){
            q.push(i);
            d[i] = potatoNum[i-1];
        }

        int tmp,ansi = 0;
        while(!q.empty()){
            int h = q.front();
            q.pop();

            if(d[ansi] < d[h]) ansi = h;

            vector<int>const&v = g[h];
            for(vector<int>::const_iterator it=v.begin();it!=v.end();++it){
                if(d[tmp=*it] < d[h]){
                    d[tmp] = d[h];
                    pre[tmp] = h;
                }
                if(0 == --degree[tmp]){
                    d[tmp] += potatoNum[tmp-1];
                    q.push(tmp);
                }
            }
        }

        //确定答案
        int cnt = 0;
        d[cnt++] = ansi;
        while(pre[ansi]){
            d[cnt++] = ansi = pre[ansi];
        }
        string s;
        while(--cnt>=0){
            s.append(int2string(d[cnt]));
            s.append("-");
        }
        s.erase(--s.end());
        return s;
    }
};