/**
   ��һ������ͼ��ÿ��������Ȩֵ
   ��һ��·����ʹ�õ�Ȩ�����
   Ҫ���������
   ��diΪ��i��ʱ�ܹ��õ������Ȩֵ����Ȼ
   di = max(d[from]) + ai
   ʹ������������ȷ��DP˳�򣬲�ʹ��ˢ������
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
     * @param potatoNum int����vector ���α�ʾ���Ϊ1,2,3..�ķ������ж��ٸ�����
     * @param connectRoad int����vector<vector<>> ÿ��һά����[x,y]��ʾ�ӵ�x�ŷ�������y����·
     * @return string�ַ���
     */
    string digSum(vector<int>& potatoNum, vector<vector<int> >& connectRoad) {
        //��ͼ
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

        //���У��Ѷ�Ϊ0��ȫ����ȥ
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

        //ȷ����
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