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

bool isEnd(char grid[3][3]) {
    return isWin('X', grid) || isWin('O', grid) || isDraw(grid);
}

char opposite(char player) {
    return (player == 'X') ? 'O' : 'X';
}

int score(char p) {
    return (player == p) ? 1 : -1;
}

ii indexToPosition(int index) {
    index--;
    return ii(index / 3, index % 3);
}

int positionToIndex(ii move) {
    return (move.first * 3 + move.second) + 1;
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
    cout << "Who do you want to play as? (X or O)" << endl;
    char human; cin >> human;
    cout << endl;

    if (human == 'o' || human == '0') human = 'O';
    if (human != 'O') human = 'X';

    cout << "You are playing as " << human << "." << endl;
    cout << "Here are the position numbers on the board:" << endl;
    cout << "123" << endl << "456" << endl << "789" << endl;
    cout << endl;

    cout << "Good luck!" << endl;

    player = 'X';
    rep(i,0,3) rep(j,0,3) grid[i][j] = '_';

    while (!isEnd(grid)) {
        printGrid(grid);
        if (human == player) {
            cout << "Where do you want to move?" << endl;
            int playerIndex; cin >> playerIndex;
            cout << endl;
            while (playerIndex < 1 || playerIndex > 9 || grid[indexToPosition(playerIndex).first][indexToPosition(playerIndex).second] != '_') {
                cout << "Invalid move. Where do you want to move?" << endl;
                cin >> playerIndex;
                cout << endl;
            }
            ii playerMove = indexToPosition(playerIndex);
            grid[playerMove.first][playerMove.second] = player;
        } else {
            ii computerMove = bestMove(player, grid);
            grid[computerMove.first][computerMove.second] = player;

            cout << "The AI bot moved at " << positionToIndex(computerMove) << "." << endl;
            cout << endl;
        }
        player = opposite(player);
    }

    printGrid(grid);
    if (isWin(human, grid)) {
        cout << "Congratulations you won!" << endl;
    } else if (isWin(opposite(human), grid)) {
        cout << "Sorry, you lost to the AI. Better luck next time!" << endl;
    } else {
        cout << "It was a draw!" << endl;
    }

    return 0;
}
