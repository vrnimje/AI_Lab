#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Graph {
public:
  int n;
  vector<vector<int>> adj_matrix;
  vector<pair<int, int>> coords;

  Graph() { ; }

  Graph(int x) {
    n = x;
    adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
    coords = vector<pair<int, int>>(n, {0, 0});
  }

  void printGraph() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << adj_matrix[i][j] << " ";
      }
      cout << "\n";
    }
  }

  void addNode(int node, pair<int, int> xy) { coords[node] = xy; }

  void addEdge(int n1, int n2, int w) {
    adj_matrix[n1][n2] = w;
    adj_matrix[n2][n1] = w;
  }

  int h(int n1, int n2) {
    auto x = coords[n1], y = coords[n2];
    return abs(x.first - y.first) + abs(x.second - y.second);
  }
};

bool sort_h(pair<int, int> &a, pair<int, int> &b) {
  return a.second > b.second;
}

int find(vector<pair<int, int>> &v, int &val) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i].first == val)
      return i;
  }
  return -1;
}

void Prop_imp(Graph &G, int &node, vector<int> &g, vector<int> &f,
              set<int> &closed, vector<int> &parent) {
  for (int i = 0; i < G.n; i++) {
    if (G.adj_matrix[node][i] != 0) {
      int new_g = g[node] + G.adj_matrix[node][i];
      if (new_g < g[i]) {
        parent[i] = node;
        g[i] = new_g;
        if (closed.find(i) != closed.end()) {
          Prop_imp(G, i, g, f, closed, parent);
        }
      }
    }
  }
}

void Reconst_path(vector<int> &parent, int &start, int &end) {
  vector<int> res;
  int i = end;
  while (i != start) {
    res.push_back(i);
    ;
    i = parent[i];
  }
  res.push_back(i);
  reverse(res.begin(), res.end());
  for (auto x : res) {
    cout << x;
    if (x != end) {
      cout << "->";
    }
  }
  cout << "\n";
}

void A_star(Graph G, int start, int goal) {
  int steps = 0, cost = 0;
  vector<pair<int, int>> Open; // node, f(n)
  set<int> closed;

  Open.push_back({start, G.h(start, goal)});
  vector<int> g(G.n), f(G.n), parent(G.n, start);

  while (!Open.empty()) {
    steps++;
    pair<int, int> res = Open.back();
    Open.pop_back();

    closed.insert(res.first);

    cout << g[res.first] << " ";
    cout << G.h(res.first, goal) << " ";
    Reconst_path(parent, start, res.first);
    if (res.first == goal) {
      cout << "\nPath: \n";
      Reconst_path(parent, start, goal);
      break;
    }

    for (int i = 0; i < G.n; i++) {
      if (G.adj_matrix[res.first][i] != 0) {
        // New node
        if (closed.find(i) == closed.end() && find(Open, i) < 0) {
          parent[i] = res.first;
          g[i] = g[res.first] + G.adj_matrix[res.first][i];
          f[i] = g[i] + G.h(i, goal);
          Open.push_back({i, f[i]});
        } else if (find(Open, i) >= 0) {
          if (g[res.first] + G.adj_matrix[res.first][i] < g[i]) {
            parent[i] = res.first;
            g[i] = g[res.first] + G.adj_matrix[res.first][i];
            f[i] = g[i] + G.h(i, goal);
            Open[find(Open, i)].second = f[i];
          }
        } else if (closed.find(i) != closed.end()) {
          if (g[res.first] + G.adj_matrix[res.first][i] < g[i]) {
            parent[i] = res.first;
            g[i] = g[res.first] + G.adj_matrix[res.first][i];
            f[i] = g[i] + G.h(i, goal);
            Prop_imp(G, i, g, f, closed, parent);
          }
        }
      }
    }
    cost = g[goal];
    sort(Open.begin(), Open.end(), sort_h);
  }
  cout << "Cost: " << cost << "\n";
}

int main() {
  Graph G1(20);
  G1.addNode(0, {3, 0});  // A
  G1.addNode(1, {4, 0});  // B
  G1.addNode(2, {6, 0});  // C
  G1.addNode(3, {1, 1});  // D
  G1.addNode(4, {8, 1});  // E
  G1.addNode(5, {0, 2});  // F
  G1.addNode(6, {8, 6});  // G
  G1.addNode(7, {4, 2});  // H
  G1.addNode(8, {1, 4});  // I
  G1.addNode(9, {3, 3});  // J
  G1.addNode(10, {6, 2}); // K
  G1.addNode(11, {0, 4}); // L
  G1.addNode(12, {3, 4}); // M
  G1.addNode(13, {6, 4}); // N
  G1.addNode(14, {1, 5}); // O
  G1.addNode(15, {4, 5}); // P
  G1.addNode(16, {8, 5}); // Q
  G1.addNode(17, {2, 6}); // R
  G1.addNode(18, {0, 0}); // S
  G1.addNode(19, {6, 6}); // T

  G1.addEdge(18, 3, 25);
  G1.addEdge(3, 0, 32);
  G1.addEdge(3, 5, 24);
  G1.addEdge(3, 8, 26);
  G1.addEdge(5, 11, 27);
  G1.addEdge(11, 8, 21);
  G1.addEdge(11, 14, 26);
  G1.addEdge(14, 17, 27);
  G1.addEdge(17, 19, 52);
  G1.addEdge(19, 6, 32);
  G1.addEdge(6, 13, 42);
  G1.addEdge(13, 16, 32);
  G1.addEdge(13, 10, 27);
  G1.addEdge(13, 7, 44);
  G1.addEdge(10, 7, 28);
  G1.addEdge(10, 16, 62);
  G1.addEdge(10, 1, 42);
  G1.addEdge(10, 4, 32);
  G1.addEdge(7, 0, 36);
  G1.addEdge(7, 9, 22);
  G1.addEdge(9, 12, 20);
  G1.addEdge(12, 15, 23);
  G1.addEdge(12, 8, 32);
  G1.addEdge(1, 2, 24);
  G1.addEdge(2, 4, 40);
  G1.addEdge(0, 1, 11);
  cout << "g  h  Path\n";
  A_star(G1, 18, 6);
  return 0;
}
