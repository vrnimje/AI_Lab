#include <iostream>
#include <vector>

using namespace std;

class Tic_Tac_Toe {
  // MAX - X (1) and MIN - O (2)
public:
  vector<vector<int>> grid = vector<vector<int>>(3, vector<int>(3, 0));
  Tic_Tac_Toe() { ; }

  bool row_same() {
    for (int i = 0; i < 3; i++) {
      if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] &&
          grid[i][0] != 0) {
        return true;
      }
    }
    return false;
  }

  bool column_same() {
    for (int i = 0; i < 3; i++) {
      if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] &&
          grid[0][i] != 0) {
        return true;
      }
    }
    return false;
  }

  bool diagnol_same() {
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] &&
        grid[0][0] != 0) {
      return true;
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] &&
        grid[0][2] != 0) {
      return true;
    }
    return false;
  }

  bool is_full() {
    int c = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (grid[i][j] > 0)
          c++;
      }
    }
    if (c == 9)
      return true;
    return false;
  }

  bool game_over() { return (row_same() || column_same() || diagnol_same()); }

  void print_grid() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cout << grid[i][j] << " ";
      }
      cout << "\n";
    }
    cout << "\n";
  }
};

int MiniMax(Tic_Tac_Toe S, int k, int player, int &Max) {
  int score = 0, best_score = 0;
  if (S.game_over()) {
    if (player == Max) {
      return 1;
    } else {
      return -1;
    }
  } else if (S.is_full()) {
    return 0;
  } else {
    if (k < 9) {
      if (player == Max) {
        best_score = -999;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (S.grid[i][j] == 0) {
              S.grid[i][j] = player;
              score = MiniMax(S, k + 1, player, Max);
              best_score = max(best_score, score);
            }
          }
        }
        return best_score;
      } else {
        best_score = 999;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (S.grid[i][j] == 0) {
              S.grid[i][j] = player;
              score = MiniMax(S, k + 1, player, Max);
              best_score = min(best_score, score);
            }
          }
        }
        return best_score;
      }
    } else {
      return 0;
    }
  }
}

pair<int, int> BestMove(Tic_Tac_Toe S, int move_index, int player, int &Max) {
  int x = -1, y = -1;
  int score = 0, best_score = 0;
  if (player == Max) {
    best_score = -999;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (S.grid[i][j] == 0) {
          S.grid[i][j] = player;
          score = MiniMax(S, move_index + 1, player, Max);
          S.grid[i][j] = 0;
          if (score > best_score) {
            best_score = score;
            x = i;
            y = j;
          }
        }
      }
    }
  } else {
    best_score = 999;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (S.grid[i][j] == 0) {
          S.grid[i][j] = player;
          score = MiniMax(S, move_index + 1, player, Max);
          S.grid[i][j] = 0;
          if (score <= best_score) {
            best_score = score;
            x = i;
            y = j;
          }
        }
      }
    }
  }
  cout << best_score << "\n";
  return {x, y};
}

void GamePlay(int Max, int Min) {
  int whoseturn = Max;
  pair<int, int> move = {0, 0};
  int move_index = 0;
  Tic_Tac_Toe S;
  while (!S.game_over() && !S.is_full()) {
    if (whoseturn == Max) {
      move = BestMove(S, move_index, whoseturn, Max);
      S.grid[move.first][move.second] = Max;
      cout << "Max played at: (" << move.first << ", " << move.second << ")\n";
      S.print_grid();
      whoseturn = Min;
    } else if (whoseturn == Min) {
      cout << "Enter move: "
           << "\n";
      cin >> move.first;
      cin >> move.second;
      S.grid[move.first][move.second] = Min;
      whoseturn = Max;
    } else {
      cout << "Invalid!\n";
      break;
    }
  }
  if (!S.game_over()) {
    cout << "Game is a draw\n";
  } else {
    if (whoseturn == Max) {
      cout << "Min won!!\n";
    } else {
      cout << "Max won!!\n";
    }
  }
}

int main() { GamePlay(1, 2); }