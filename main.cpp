#include<bits/stdc++.h>
using namespace std;

#define F first
#define S second

//we are representing this problem in the form of an implicit graph (matrix) where the nodes are the cells of the matrix,
//and its neighbours are its adjacent four cells,(x-1,y) , (x,y-1),(x+1,y),(x,y+1)
//cost of moving from one cell to its neighbour is zero , as this is an unweighted graph.


int n,m;
vector<string> arr;   //used to store our map

using state = pair<int,int>;  //used to store (x,y)

int dx[] = {0,1,0,-1};   //we move in the four cardinal directions .... we make small movements
int dy[] = {1,0,-1,0};  //from (x,y) we go to (x + dx[i] , y + dy[i]) .we use these two arrays to make code less messy.

int dist[1010][1010];  //this measures the min distance of point (x,y) from the point where we are starting bfs
state back[1010][1010]; //this stores from where we are coming ..like state[x][y] suppose stores (x-1,y).this means we travelled from
//(x-1,y) to (x,y)

bool check(int x,int y){
    if(x<0||x>=n||y<0||y>=m||arr[x][y]=='#')return 0;
    return 1;
}
//this function checks whether we are going out of grid or reaching a building/barrier/checks validity of ur move

void bfs(vector<state> allst){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dist[i][j] = 100;
        }    ///we are initialising all distances to be 100
    }
    queue<state> q;  //boilerplate bfs code queue
    for(auto st:allst){
        dist[st.F][st.S] = 0;   //consider hospitals here . push all the hospitals into the queue.
        back[st.F][st.S] = {-1,-1};   //since we are already at the hospitals , we dont need prev location . just make it (-1,-1)
        q.push(st);  //pushing in queue
    }
    while(!q.empty()){
        state cur = q.front(); q.pop();
        int dcur = dist[cur.F][cur.S];   //where we are currently standing (x,y)
        //
        for(int k=0;k<4;k++){
            state v = { cur.F+dx[k] , cur.S+dy[k] };  //we iterate over this nodes neighbours in the 4 directions , and check
            //which of the moves are valid
            if(check(v.F,v.S) && dist[v.F][v.S]>dcur+1){  //if going to this cell is valid and following the current path from this cell
                // relax the v neighbour          //gives us a lesser distance , we have found a smaller distance path, so we update distance
                dist[v.F][v.S] = dcur+1;          //we have gotten a smaller distance so we update it
                back[v.F][v.S] = cur;          //update from where we are coming now . this is a smaller path
                q.push(v);           //push again
            }
        }
    }
}



void solve(){
    cin>>n>>m;
    arr.resize(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int k;cin>>k;   //number of hospitals
    vector<state> st(k); //  list of all hospital locations
    for(int i=0;i<k;i++)cin>>st[i].F>>st[i].S;//
    bfs(st);        //run bfs from all of the hospitals.

    //in normal bfs , we run bfs from one single point.
    //here , we are running bfs from all of the services(eg hospitals) points simultaneously

    //list of all markets  another vector.....vector<state>st1(k)
    //list of all third service
    //barriers/buildings are represented by #
    //we are doing a multisource bfs , wherein we are pushing all (say hospitals here) into the queue , and run a bfs and find the shortest path
    //from any of the hospitals to where we are standing
    //this works coz edges are bidirectional . we can move through the edges in both directions
    //total time complexity of this is O(gridlength * gridbreadth)



    state en;                          //where we live , from where we have to go to the service
    cin>>en.F>>en.S;
    cout<<dist[en.F][en.S]<<endl;         //gives how far the hospital/other service is

    vector<state> path;
    while(en!=make_pair(-1,-1)){
        path.push_back(en);
        en = back[en.F][en.S];
    }
    // reverse(path.begin(),path.end());  //not rqd
    for(auto v:path){
        cout<<v.F<<" "<<v.S<<endl;   //print out the path
    }

}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //int _t;cin>>_t;while(_t--)
    solve();
}
