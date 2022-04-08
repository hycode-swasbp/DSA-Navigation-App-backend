#include<bits/stdc++.h>
using namespace std;

#define F first
#define S second

int n,m;
vector<string> arr;

using state = pair<int,int>;

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

int dist[1010][1010];
state back[1010][1010];
int dist1[1010][1010];
state back1[1010][1010];
state start;
int d;

bool check1(int x,int y,state start , int d){         //hospital path validity
    if(x<0||x>=n||y<0||y>=m||arr[x][y]=='#'|| arr[x][y] == 'M')return 0;
    if(x  >start.F + d  || x  < start.F - d || y  > start.S + d || y  < start.S - d )return 0;
    return 1;
}

bool check2(int x,int y,state start , int d)
{
    if(x<0||x>=n||y<0||y>=m||arr[x][y]=='#'|| arr[x][y] == 'H')return 0;
    if(x  >start.F + d  || x  < start.F - d || y  > start.S + d || y  < start.S - d )return 0;
    return 1;
}




void bfs1(state st){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dist[i][j] = 100;
        }
    }
    queue<state> q;

    dist[st.F][st.S] = 0;
    back[st.F][st.S] = {-1,-1};
    q.push(st);

    while(!q.empty()){
        state cur = q.front(); q.pop();
        int dcur = dist[cur.F][cur.S];
        //
        for(int k=0;k<4;k++){
            state v = { cur.F+dx[k] , cur.S+dy[k] };

            if(check1(v.F,v.S,start,d) && dist[v.F][v.S]>dcur+1){

                dist[v.F][v.S] = dcur+1;
                back[v.F][v.S] = cur;
                q.push(v);
            }
        }
    }
}

void bfs2(state st)
{
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dist1[i][j] = 100;
        }
    }
    queue<state> q;

    dist1[st.F][st.S] = 0;
    back1[st.F][st.S] = {-1,-1};
    q.push(st);

    while(!q.empty()){
        state cur = q.front(); q.pop();
        int dcur = dist1[cur.F][cur.S];
        //
        for(int k=0;k<4;k++){
            state v = { cur.F+dx[k] , cur.S+dy[k] };

            if(check2(v.F,v.S,start,d) && dist1[v.F][v.S]>dcur+1){

                dist1[v.F][v.S] = dcur+1;
                back1[v.F][v.S] = cur;
                q.push(v);
            }
        }
    }

}

void solve()
{
    cin>>n>>m;
    arr.resize(n);
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
    }

   cin>>d;
    for(int i = 0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(arr[i][j] == 'S')
            {
                start = make_pair(i,j);
            }
        }
    }




    vector<state>hosp;
    vector<state>market;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(arr[i][j] == 'H')
            {
                hosp.push_back({i,j});
            }
        }
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(arr[i][j] == 'M')
            {
                market.push_back({i,j});
            }
        }
    }

    memset(dist,100,sizeof(dist));
    memset(dist1,100,sizeof(dist));

    state start;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(arr[i][j] == 'S')
            {
                start = make_pair(i,j);
            }
        }
    }
    bfs1(start);
    bfs2(start);
    int mn = 1e9;
    for(int i = 0;i<hosp.size();i++)
    {
        state en = hosp[i];
        mn = min(mn , dist[en.F][en.S]);
    }
    int mn1 = 1e9;
    for(int i = 0;i<market.size();i++)
    {
        state en = market[i];
        mn1 = min(mn1 , dist1[en.F][en.S]);
    }


    state end;




    if(mn == 100 || hosp.size() == 0)
    {
       cout<<"NO HOSPITALS IN VICINITY"<<endl;
       goto label;
    }
    cout<<"HOSPITAL PATHS"<<endl;

    for(int i = 0;i<hosp.size();i++)
    {
        end = hosp[i];
        vector<state>path;
        if(dist[end.F][end.S] != mn)continue;
        cout<<dist[end.F][end.S]<<endl;
        while(end != make_pair(-1,-1))
        {
            path.push_back(end);
            end = back[end.F][end.S];
        }
        reverse(path.begin(),path.end());
        for(auto v : path)
        {
            cout<<v.F<<" "<<v.S<<endl;
        }
        if(i!=hosp.size() - 1)cout<<"NEXT SHORTEST PATH TO HOSPITAL"<<endl;
    }

    label:{};
    if(mn1 == 100 || market.size() == 0)
    {
        cout<<"NO MARKETS IN VICINITY"<<endl;
        goto label1;
    }
    cout<<"MARKET PATHS"<<endl;
    for(int i = 0;i<market.size();i++)
    {
        end = market[i];
        vector<state>path;
        if(dist1[end.F][end.S] != mn1)continue;
        cout<<dist1[end.F][end.S]<<endl;
        while(end != make_pair(-1,-1))
        {
            path.push_back(end);
            end = back1[end.F][end.S];
        }
        reverse(path.begin(),path.end());
        for(auto v : path)
        {
            cout<<v.F<<" "<<v.S<<endl;
        }
       // if(i!=market.size() - 1)cout<<"NEXT SHORTEST PATH TO MARKET"<<endl;
    }

    label1:{};

}


signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //int _t;cin>>_t;while(_t--)
    solve();
}
