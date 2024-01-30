#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

class Compare;

// (!2 v 3 v !4)^(!0 v !1 v !4)^( 1 v 0 v 4)^( 3 v !0 v 1)

class SAT {

public:
  int m, n;
  vector<bool> vars;
  vector<vector<int>> clauses, negations;

  SAT() { ; }

  SAT(int a, int b) {
    m = a;
    n = b;
    srand(time(0));
    vars = vector<bool>(n, false);
    clauses = vector<vector<int>>(m, vector<int>(3, 0));
    negations = vector<vector<int>>(m, vector<int>(3, 0));

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
    cout << "SAT: ";
    for (int i = 0; i < m; i++) {
      cout << '(' << problem[i] << ')';
      if (i != m - 1)
        cout << '^';
    }
    cout << "\n";
  }

  bool is_soln() {
    vector<bool> C(m, false);
    for (int i=0; i<m; i++) {
      for (int j=0; j<3; j++) {
        if (negations[i][j]) {
          C[i] = C[i] || !vars[clauses[i][j]];
        }
        else {
          C[i] = C[i] || vars[clauses[i][j]];
        }
      }
    }
    bool res = true;
    for (bool x: C) {
      res = res && x;
    }
    return res;
  }

  int h() {
    vector<bool> C(m, false);
    for (int i=0; i<m; i++) {
      for (int j=0; j<3; j++) {
        if (negations[i][j]) {
          C[i] = C[i] | !vars[clauses[i][j]];
        }
        else {
          C[i] = C[i] | vars[clauses[i][j]];
        }
      }
    }

    int c = 0;
    for (bool x: C) {
      if (x) c++;
    }
    return c;
  }

  void print_bits() {
    for (int i = 0; i < n; i++) {
      cout << vars[i];
    }
    cout << "\n";
  }

  bool operator==(SAT& rhs) {
    return (vars == rhs.vars);
  }

  void
  MoveGen(priority_queue<pair<SAT, int>, vector<pair<SAT, int>>, Compare> &Q,
          map<vector<bool>, int> &visited, float den);
};

bool find(vector<SAT>& V, SAT x) {
  for (SAT It: V) {
    if (It == x) return true;
  }
  return false;
}

template <class T, class S, class C> void clearpq(priority_queue<T, S, C> &q) {
  q = priority_queue<T, S, C>();
}

class Compare {
public:
  bool operator()(const pair<SAT, int> &a, const pair<SAT, int> &b) {
    return (a.second < b.second);
  }
};

void SAT::MoveGen(
    priority_queue<pair<SAT, int>, vector<pair<SAT, int>>, Compare> &Q,
    map<vector<bool>, int> &visited, float den) {
  if (den == 1) {
    for (int i=0; i<n; i++) {
      SAT x;
      x.m = m;
      x.n = n;
      x.clauses = clauses;
      x.negations = negations;
      x.vars = vars;
      x.vars[i] = !vars[i];
      if (visited.find(x.vars) == visited.end()) {
        Q.push({x, x.h()});
      }
    }
  }
  if (den == 2) {
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        SAT x;
        x.m = m;
        x.n = n;
        x.clauses = clauses;
        x.negations = negations;
        x.vars = vars;
        x.vars[i] = !vars[i];
        x.vars[j] = !vars[j];

        if (visited.find(x.vars) == visited.end()) {
          Q.push({x, x.h()});
        }
      }
    }
  }
  if (den == 3) {
    for (int k=0; k < n-2; k++) {
      for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
          SAT x;
          x.m = m;
          x.n = n;
          x.clauses = clauses;
          x.negations = negations;
          x.vars = vars;
          x.vars[i] = !vars[i];
          x.vars[j] = !vars[j];
          x.vars[k] = !vars[k];

          if (visited.find(x.vars) == visited.end()) {
            Q.push({x, x.h()});
          }
        }
      }
    }
  }
}

SAT Hill_Climb(SAT node, float density, bool& soln, int &steps) {
  priority_queue<pair<SAT, int>, vector<pair<SAT, int>>, Compare> Open;
  map<vector<bool>, int> Close;

  Open.push({node, node.h()});
  int prev = node.h();
  SAT final;

  cout << "Density: " << density << "\n"; 

  while (!Open.empty()) {
    steps++;
    auto res = Open.top();
    Open.pop();

    cout << res.second << " ";
    res.first.print_bits();

    Close.emplace(res.first.vars, 1);

    if (res.first.is_soln()) {
      final = res.first;
      soln = true;
      break;
    }

    if (res.second < prev) {
      break;
    }

    // Burn the bridges
    clearpq(Open);

    // Add neighbouring states
    res.first.MoveGen(Open, Close, density);

    prev = res.second;
    final = res.first;
  }

  return final;
}

void VND(SAT S) {
  vector<float> densities = {1, 2, 3};
  bool soln = false;
  int steps = 0;

  for (float d : densities) {
    // S.print_bits();
    if (S.is_soln()) {
      soln = true;
      break;
    }
    S = Hill_Climb(S, d, soln, steps);
  }
  cout << "No. of steps: " << steps << "\n";
  if (!soln) {
    cout << "No solutions found"
         << "\n";
    return;
  } 
}

int main() {

  int m = 0, n = 0;
  cout << "Number of clauses: ";
  cin >> m;

  cout << "Number of variables: ";
  cin >> n;

  SAT S(m, n);

  VND(S);

  return 0;
}