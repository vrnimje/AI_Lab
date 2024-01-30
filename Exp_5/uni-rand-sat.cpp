#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int m = 0, n = 0;
  cout << "Number of clauses: ";
  cin >> m;

  cout << "Number of variables: ";
  cin >> n;

  srand(time(0));

  vector<vector<int>> clauses(m, vector<int>(3, 0)), negations(m, vector<int>(3, 0));

  vector<string> problem;
  for (int i = 0; i < m; i++) {
    set<int> rep;
    string clause;
    for (int j = 0; j < 3; j++) {
      int x = rand() % (n);
      while (rep.find(x) != rep.end()) {
        x = rand() % (n);
      }
      rep.insert(x);
      clauses[i][j] = x;
      int sign = rand() % 2;
      if (sign) {
        clause += "~";
      } else {
        clause += " ";
      }
      negations[i][j] = sign;
      clause += to_string(x);
      if (j != 2) {
        clause += "v";
      }
    }
    problem.push_back(clause);
  }

  for (int i = 0; i < m; i++) {
    cout << '(' << problem[i] << ')';
    if (i != m - 1)
      cout << '^';
  }
  for (int i=0; i<m; i++) {
    for (int j=0; j<3; j++) {
      cout << clauses[i][j] << " ";
    }
    cout << "\n";
  }

  cout << '\n';

  for (int i=0; i<m; i++) {
    for (int j=0; j<3; j++) {
      cout << negations[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
  return 0;
}
