#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<n;i++)
#define sz(x) ((x).size())
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int inf = 1 << 29;

char player;
char grid[3][3];

/*** HELPER FUNCTIONS ***/

void printGrid(char grid[3][3]) {
    rep(i,0,3) {
        rep(j,0,3) cout << grid[i][j];
        cout << endl;
    }
    cout << endl;
}

bool isWin(char player, char grid[3][3]) {
    bool diagonal1=true, diagonal2=true;
    rep(i,0,3) {
        bool horizontal=true;
        bool vertical=true;
        rep(j,0,3) {
            if (grid[i][j] != player) horizontal=false;
            if (grid[j][i] != player) vertical=false;
        }
        if (horizontal || vertical) return true;

        if (grid[i][i] != player) diagonal1=false;
        if (grid[i][2-i] != player) diagonal2=false;
    }
    if (diagonal1 || diagonal2) return true;
    return false;
}

bool isDraw(char grid[3][3]) {
    bool full = true;
    rep(i,0,3) rep(j,0,3) if (grid[i][j] == '_') full = false;
    return !isWin('X', grid) && !isWin('O', grid) && full; 
}

char opposite(char player) {
    return (player == 'X') ? 'O' : 'X';
}

int score(char p) {
    return (player == p) ? 1 : -1;
}

/*** ALPHA-BETA PRUNING ***/

int alpha(char player, char grid[3][3], int a, int b);
int beta(char player, char grid[3][3], int a, int b);

int alpha(char player, char grid[3][3], int a, int b) {
    if (isWin(player, grid)) return score(player);
    if (isDraw(grid)) return 0;
    if (isWin(opposite(player), grid)) return score(opposite(player));

    int maxScore = -1;
    rep(i,0,3) rep(j,0,3) {
        if (grid[i][j] == '_') {
            grid[i][j] = player;
            maxScore = max(maxScore, beta(opposite(player), grid, a, b));
            grid[i][j] = '_';

            a = max(a, maxScore);
            if (b <= a) return maxScore;
        }
    }
    return maxScore;
}

int beta(char player, char grid[3][3], int a, int b) {
    if (isWin(player, grid)) return score(player);
    if (isDraw(grid)) return 0;
    if (isWin(opposite(player), grid)) return score(opposite(player));

    int minScore = 1;
    rep(i,0,3) rep(j,0,3) {
        if (grid[i][j] == '_') {
            grid[i][j] = player;
            minScore = min(minScore, alpha(opposite(player), grid, a, b));
            grid[i][j] = '_';

            b = min(b, minScore);
            if (b <= a) return minScore;
        }
    }
    return minScore;
}

ii bestMove(char player, char grid[3][3]) {
    if (isWin('X', grid) || isWin('O', grid) || isDraw(grid)) return ii(-1, -1);
    int maxScore = -1;
    ii bestMove = ii(-1, -1);
    rep(i,0,3) rep(j,0,3) {
        if (grid[i][j] == '_') {
            grid[i][j] = player;
            int opponentScore = beta(opposite(player), grid, -inf, inf);
            if (opponentScore > maxScore) {
                maxScore = opponentScore;
                bestMove = ii(i,j);
            }
            // cout << opponentScore << endl;
            // printGrid(grid);
            grid[i][j] = '_';
        }
    }
    if (bestMove.first != -1) {
        return bestMove;
    }
    rep(i,0,3) rep(j,0,3) 
        if (grid[i][j] == '_') {
            return ii(i,j);
        }
    return ii(-1, -1);
}

/*** MAIN ***/

int main() {
    cin >> player;
    rep(i,0,3) rep(j,0,3) cin >> grid[i][j];

    ii ans = bestMove(player, grid);
    cout << ans.first << " " << ans.second << endl;

    return 0;
}
