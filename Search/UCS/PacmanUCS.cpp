#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;i++)
typedef pair<int,int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;

int pacR, pacC;
int foodR, foodC;
int n, m;

int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

char** grid;

vii path;

bool inbounds(ii pos) {
    return 0 <= pos.first && pos.first < n && 0 <= pos.second && pos.second < m;
}

int main() {
    cin >> pacR >> pacC >> foodR >> foodC >> n >> m;
    grid = new char*[n];
    rep(i,0,n) {
        grid[i] = new char[m];
        rep(j,0,m) cin >> grid[i][j];
    }

    /* Begin UCS
     *
     * Note: works the same as BFS on unweighted graph...
     */

    priority_queue< iii, viii, greater<iii> > fringe;
    fringe.push(iii(0, ii(pacR, pacC)));
    
    int dist[n][m];
    memset(dist, -1, sizeof dist);
    dist[pacR][pacC] = 0;

    int pred[n][m];
    pred[pacR][pacC] = -1;

    while (!fringe.empty()) {
        iii state = fringe.top(); fringe.pop();
        ii pos = state.second;
        if (state.first > dist[pos.first][pos.second]) continue;
        if (pos.first == foodR && pos.second == foodC) {
            break;
        }
        rep(d,0,4) {
            ii next = ii(pos.first + dr[d], pos.second + dc[d]);
            int priority = state.first + 1;
            if (inbounds(next) && 
                (dist[next.first][next.second] > priority || dist[next.first][next.second] == -1) &&
                grid[next.first][next.second] != '%') {
                pred[next.first][next.second] = d;
                dist[next.first][next.second] = priority;
                fringe.push(iii(priority, next));
            }
        }
    }

    ii current = ii(foodR, foodC);
    while (pred[current.first][current.second] != -1) {
        path.push_back(current);
        int d = pred[current.first][current.second];
        ii next = ii(current.first - dr[d], current.second - dc[d]);
        current = next;
    }
    path.push_back(current);
    reverse(path.begin(), path.end());

    /* End DFS */

    cout << ((int) path.size()) - 1 << endl;
    rep(i,0,((int) path.size())) {
        ii pos = path[i];
        cout << pos.first << " " << pos.second << endl;
    }

    /*
    rep(i,0,((int) path.size())) {
        ii pos = path[i];
        if (pos.first == pacR && pos.second == pacC) continue;
        if (pos.first == foodR && pos.second == foodC) continue;
        grid[pos.first][pos.second] = '*';
    }
    rep(i,0,n) {
        rep(j,0,m) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    */

    return 0;
}
