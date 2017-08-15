#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;i++)
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int pacR, pacC;
int foodR, foodC;
int n, m;

int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};

char** grid;

vii explored;
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

    /* Begin DFS */

    vii fringe;
    fringe.push_back(ii(pacR, pacC));
    
    bool isOpen[n][m];
    bool isClosed[n][m];
    memset(isOpen, 0, sizeof isOpen);
    memset(isClosed, 0, sizeof isClosed);
    isOpen[pacR][pacC] = true;

    int pred[n][m];
    pred[pacR][pacC] = -1;

    while (!fringe.empty()) {
        ii pos = fringe.back(); fringe.pop_back();
        isOpen[pos.first][pos.second] = false;
        isClosed[pos.first][pos.second] = true;
        explored.push_back(pos);
        if (pos.first == foodR && pos.second == foodC) {
            break;
        }
        rep(d,0,4) {
            ii next = ii(pos.first + dr[d], pos.second + dc[d]);
            if (inbounds(next) && 
                !isOpen[next.first][next.second] &&
                !isClosed[next.first][next.second] &&
                grid[next.first][next.second] != '%') {
                pred[next.first][next.second] = d;
                isOpen[next.first][next.second] = true;
                fringe.push_back(next);
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

    cout << ((int) explored.size()) << endl;
    rep(i,0,((int) explored.size())) {
        ii pos = explored[i];
        cout << pos.first << " " << pos.second << endl;
    }

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
