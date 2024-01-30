#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

void suck(float *x) { *x = 0; }

void traverse(vector<vector<float>> &floor, pair<int, int> &curr_loc,
              pair<int, int> &next_loc, float &power) {
  if (curr_loc == next_loc) {
    return;
  }

  // Get to the same row
  if (curr_loc.first > next_loc.first &&
      floor[curr_loc.first - 1][curr_loc.second] != 2) {
    curr_loc.first--;
    power++;
    traverse(floor, curr_loc, next_loc, power);
  }
  if (curr_loc.first < next_loc.first &&
      floor[curr_loc.first + 1][curr_loc.second] != 2) {
    curr_loc.first++;
    power++;
    traverse(floor, curr_loc, next_loc, power);
  }

  // Get to the same column
  if (curr_loc.second > next_loc.second &&
      floor[curr_loc.first][curr_loc.second - 1] != 2) {
    curr_loc.second--;
    power++;
    traverse(floor, curr_loc, next_loc, power);
  }
  if (curr_loc.second < next_loc.second &&
      floor[curr_loc.first][curr_loc.second + 1] != 2) {
    curr_loc.second++;
    power++;
    traverse(floor, curr_loc, next_loc, power);
  }
}

void dfs(vector<vector<float>> &floor, int s) {
  int n = floor.size();
  vector<vector<bool>> visited(n, vector<bool>(n, false));
  stack<int> S;
  float power = 0;
  
  //Current location: {s, s}
  pair<int, int> loc = {s, s};
  S.push(s);

  while (!S.empty()) {
    int vertex = S.top();
    S.pop();

    for (int i = 0; i < n; i++) {
      pair<int, int> target_loc = {vertex, i};
      traverse(floor, loc, target_loc, power);
      if ((floor[vertex][i] > 0 && floor[vertex][i] < 1) &&
          (!visited[vertex][i])) {

        visited[vertex][i] = true;
        // Debug
        cout << vertex << "," << i << "\n";
        power += floor[vertex][i];
        suck(&floor[vertex][i]);
        S.push(i);
      }
    }
  }

  cout << "Power used: " << power << " units\n";
}

void bfs(vector<vector<float>> &floor, int s) {
  int n = floor.size();
  vector<vector<bool>> visited(n, vector<bool>(n, false));
  queue<int> Q;
  float power = 0;

  // Current location: (s, s);
  Q.push(s);
  pair<int, int> loc = {s, s};

  while (!Q.empty()) {
    int vertex = Q.front();
    Q.pop();

    for (int i = 0; i < n; i++) {
      pair<int, int> target_loc = {vertex, i};
      traverse(floor, loc, target_loc, power);
      if ((floor[vertex][i] > 0 && floor[vertex][i] < 1) &&
          (!visited[vertex][i])) {

        visited[vertex][i] = true;
        // Debug
        cout << vertex << "," << i << "\n";
        power += floor[vertex][i];
        suck(&floor[vertex][i]);
        Q.push(i);
      }
    }
  }
  cout << "Power used: " << power << " units\n";
}

void vacuum_bot_start(vector<vector<float>> &floor) {
  // bfs(floor, 0);  // 198.8334045 power (6x6) & 1671.4533691 power (12x12) &
                     // 1446.4764404 (with extra obstacles, 12x12)

  dfs(floor, 0); // 193.833740 power (6x6) & 1649.4533691 power (12x12) &
                 // 1424.4764404 (with extra obstacles, 12x12)
}

void print_floor(vector<vector<float>> &floor) {
  int n = floor.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << floor[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
  int n = 6;
  vector<vector<float>> floor(n, vector<float>(n, 0));
  cout << fixed << setprecision(7);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      floor[i][j] = (rand() % 2 == 0) ? (float)rand() / (RAND_MAX) : (float)0;
    }
  }

  for (int i = 0; i < n - 1; i++) {
    floor[3][i] = (float)2;
  }

  for (int i = 4; i < n - 5; i++) {
    floor[i][5] = (float)2;
  }

  print_floor(floor);
  vacuum_bot_start(floor);

  cout << "After cleaning: "
       << "\n";
  print_floor(floor);
}