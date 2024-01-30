#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Jugs {
    public:
        // Curr capacities
        int a = 0, b = 0;

        // Max capacities
        int m = 3, n = 5;

        Jugs() {
            ;
        }

        Jugs(int p, int q) {
            a = p;
            b = q;
        }

        Jugs(int p, int q, int r, int s) {
            a = p;
            b = q;
            m = r;
            n = s;
        }

        Jugs Jug1_to_Jug2();
        Jugs Jug2_to_Jug1();
        void Move_Gen(queue<Jugs>& Q);

        void Move_Gen(queue<Jugs>& Q, vector<vector<bool>>& visited);

        void Move_Gen(stack<Jugs>& Q);

        void Move_Gen(stack<Jugs>& Q, vector<vector<bool>>& visited);

        bool operator!=(Jugs J) {
            return !((J.a == a) && (J.b == b) && (J.m == m) && (J.n == n));
        }
};

// pair<pair<int, int>, pair<int, int>> false_state = {{0, 0}, {0, 0}};

Jugs false_state(0, 0, 0, 0);

bool can_fill(int curr, int max) {
    if (curr == max) return false;
    return true;
}

bool can_empty(int x) {
    if (x == 0) return false;
    return true;
}

Jugs Jugs::Jug1_to_Jug2() {
    if (a == 0) {
        return false_state;
    }

    int rem = n - b;

    if (a > rem) {
        return Jugs(a-rem, n);
    } else {
        return Jugs(0, a+b);
    }

}

Jugs Jugs::Jug2_to_Jug1() {
    if (b == 0) {
        return false_state;
    }

    int rem = m - a;

    if (b > rem) {
        return Jugs(m, b-rem);
    } else {
        return Jugs(a+b, 0);
    }

}

void Jugs::Move_Gen(queue<Jugs>& Q) {
    // Completely fill Jug B 
    if (can_fill(b, n)) {
        // cout << a << "," << n << " ";
        Q.push(Jugs(a, n));
    }

    // Completely fill Jug A
    if (can_fill(a, m)) {
        // cout << m << "," << b << " ";
        Q.push(Jugs(m, b));
    }

    // Empty Jug B
    if (can_empty(b)) {
        // cout << a << "," << 0 << " ";
        Q.push(Jugs(a, 0));
    }

    // Empty Jug A
    if (can_empty(a)) {
        // cout << 0 << "," << b << " ";
        Q.push(Jugs(0, b));
    }

    // Jug A to Jug B
    auto res1 = Jug1_to_Jug2();
    if (res1 != false_state) {
        // cout << res1.a << "," << res1.b << " ";
        Q.push(res1);
    }

    auto res2 = Jug2_to_Jug1();
    if (res2 != false_state) {
        // cout << res2.a << "," << res2.b << " ";
        Q.push(res2);
    }

    // cout << "\n";
}

void Jugs::Move_Gen(queue<Jugs>& Q, vector<vector<bool>>& visited) {
    // Completely fill Jug B 
    if (can_fill(b, n) && visited[a][n] == false) {
        // cout << a << "," << n << " ";
        Q.push(Jugs(a, n));
    }

    // Completely fill Jug A
    if (can_fill(a, m) && visited[m][b] == false) {
        // cout << m << "," << b << " ";
        Q.push(Jugs(m, b));
    }

    // Empty Jug B
    if (can_empty(b) && visited[a][0] == false) {
        // cout << a << "," << 0 << " ";
        Q.push(Jugs(a, 0));
    }

    // Empty Jug A
    if (can_empty(a) && visited[0][b] == false) {
        // cout << 0 << "," << b << " ";
        Q.push(Jugs(0, b));
    }

    // Jug A to Jug B
    auto res1 = Jug1_to_Jug2();
    if (res1 != false_state && visited[res1.a][res1.b] == false) {
        // cout << res1.a << "," << res1.b << " ";
        Q.push(res1);
    }

    auto res2 = Jug2_to_Jug1();
    if (res2 != false_state && visited[res2.a][res2.b] == false) {
        // cout << res2.a << "," << res2.b << " ";
        Q.push(res2);
    }

    // cout << "\n";
}

void Jugs::Move_Gen(stack<Jugs>& Q) {
    // Jug A to Jug B
    auto res1 = Jug1_to_Jug2();
    if (res1 != false_state) {
        // cout << res1.a << "," << res1.b << " ";
        Q.push(res1);
    }

    auto res2 = Jug2_to_Jug1();
    if (res2 != false_state) {
        // cout << res2.a << "," << res2.b << " ";
        Q.push(res2);
    }

    // Completely fill Jug B 
    if (can_fill(b, n)) {
        // cout << a << "," << n << " ";
        Q.push(Jugs(a, n));
    }

    // Completely fill Jug A
    if (can_fill(a, m)) {
        // cout << m << "," << b << " ";
        Q.push(Jugs(m, b));
    }

    // Empty Jug B
    if (can_empty(b)) {
        // cout << a << "," << 0 << " ";
        Q.push(Jugs(a, 0));
    }

    // Empty Jug A
    if (can_empty(a)) {
        // cout << 0 << "," << b << " ";
        Q.push(Jugs(0, b));
    }

    // cout << "\n";
}

void Jugs::Move_Gen(stack<Jugs>& Q, vector<vector<bool>>& visited) {
    // Completely fill Jug B 
    if (can_fill(b, n) && visited[a][n] == false) {
        // cout << a << "," << n << " ";
        Q.push(Jugs(a, n));
    }

    // Completely fill Jug A
    if (can_fill(a, m) && visited[m][b] == false) {
        // cout << m << "," << b << " ";
        Q.push(Jugs(m, b));
    }

    // Empty Jug B
    if (can_empty(b) && visited[a][0] == false) {
        // cout << a << "," << 0 << " ";
        Q.push(Jugs(a, 0));
    }

    // Empty Jug A
    if (can_empty(a) && visited[0][b] == false) {
        // cout << 0 << "," << b << " ";
        Q.push(Jugs(0, b));
    }

    // Jug A to Jug B
    auto res1 = Jug1_to_Jug2();
    if (res1 != false_state && visited[res1.a][res1.b] == false) {
        // cout << res1.a << "," << res1.b << " ";
        Q.push(res1);
    }

    auto res2 = Jug2_to_Jug1();
    if (res2 != false_state && visited[res2.a][res2.b] == false) {
        // cout << res2.a << "," << res2.b << " ";
        Q.push(res2);
    }

    // cout << "\n";
}

void Space_Search2_BFS(Jugs S, int d) {
    int steps = 0;
    queue<Jugs> Open;
    Open.push(S);
    
    vector<vector<bool>> Close(S.m + 1, vector<bool>(S.n + 1, false));

    while (!Open.empty()) {
        steps++;
        auto res = Open.front();
        Open.pop();
        cout << res.a << "," << res.b << endl;

        Close[res.a][res.b] = true;

        // Goal State
        if (res.a == d || res.b == d) {
            break;
        }

        // Else generate neighbouring states 
        res.Move_Gen(Open, Close);
    }

    cout << "No. of nodes encountered in search space: " << steps << "\n";
}

void Space_Search2_DFS(Jugs S, int d) {
    int steps = 0;
    stack<Jugs> Open;
    Open.push(S);
    
    vector<vector<bool>> Close(S.m + 1, vector<bool>(S.n + 1, false));

    while (!Open.empty()) {
        steps++;
        auto res = Open.top();
        Open.pop();
        cout << res.a << "," << res.b << endl;

        Close[res.a][res.b] = true;

        // Goal State
        if (res.a == d || res.b == d) {
            break;
        }

        // Else generate neighbouring states 
        res.Move_Gen(Open, Close);
    }

    cout << "No. of nodes encountered in search space: " << steps << "\n";
}

int main() {
    Jugs S;
    int d = 1;

    // No. of nodes encountered = 11
    Space_Search2_BFS(S, d);

    // No. of nodes encountered = 5
    // Space_Search2_DFS(S, d);
    
    return 0;
}
