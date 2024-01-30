#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <map>

using namespace std;

class Puzzle_8;
class Compare;

vector<vector<int>> false_state = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

class Puzzle_8 { 
    public:

    vector<vector<int>> Grid = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

    Puzzle_8() {
        ;
    }

    Puzzle_8(vector<vector<int>> x) {
        Grid = x;
    } 

    pair<int, int> empty_index() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (Grid[i][j] == -1) return {i, j};
            }
        }
        return {-1, -1};
    }

    Puzzle_8 up() {
        auto empty = empty_index();
        if (empty.first == 0) return Puzzle_8();

        vector<vector<int>> temp(Grid);

        swap(temp[empty.first][empty.second], temp[empty.first-1][empty.second]);

        return Puzzle_8(temp);
    }

    Puzzle_8 down() {
        auto empty = empty_index();
        if (empty.first == 2) return Puzzle_8();

        vector<vector<int>> temp(Grid);

        swap(temp[empty.first][empty.second], temp[empty.first+1][empty.second]);

        return Puzzle_8(temp);
    }

    Puzzle_8 left() {
        auto empty = empty_index();
        if (empty.second == 0) return Puzzle_8();

        vector<vector<int>> temp(Grid);

        swap(temp[empty.first][empty.second], temp[empty.first][empty.second-1]);

        return Puzzle_8(temp);
    }

    Puzzle_8 right() {
        auto empty = empty_index();
        if (empty.second == 2) return Puzzle_8();

        vector<vector<int>> temp(Grid);

        swap(temp[empty.first][empty.second], temp[empty.first][empty.second+1]);

        return Puzzle_8(temp);
    }

    void printGrid() {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                cout << Grid[i][j] << " ";
            }
        }
        cout << "\n";
    }

    bool operator==(Puzzle_8 x) {
        return (this->Grid == x.Grid);
    }

    int h1();
    int h2();

    void Move_Gen(priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare>& Q, map<vector<vector<int>>, int>& visited);
    void Move_Gen2(priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare>& Q, map<vector<vector<int>>, int>& visited);
};

class Compare {
    public:
        bool operator() (const pair<Puzzle_8, int>& a, const pair<Puzzle_8, int>& b) {
            return (a.second > b.second);
        }
};

void Puzzle_8::Move_Gen(priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare>& Q, map<vector<vector<int>>, int>& visited) {
    // Empty tile goes up
    Puzzle_8 res1 = up();
    auto temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h1()});
    }

    // Empty tile goes down
    res1 = down();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h1()});
    }

    // Empty tile goes left
    res1 = left();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h1()});
    }

    // Empty tile goes right
    res1 = right();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h1()});
    }
}

void Puzzle_8::Move_Gen2(priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare>& Q, map<vector<vector<int>>, int>& visited) {
    // Empty tile goes up
    Puzzle_8 res1 = up();
    auto temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h2()});
    }

    // Empty tile goes down
    res1 = down();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h2()});
    }

    // Empty tile goes left
    res1 = left();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h2()});
    }

    // Empty tile goes right
    res1 = right();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push({res1, res1.h2()});
    }
}

int Puzzle_8::h1() {
    int res = 0;
    res += (Grid[0][0] == 1) ? 0 : 1;
    res += (Grid[0][1] == 2) ? 0 : 1;
    res += (Grid[0][2] == 3) ? 0 : 1;
    res += (Grid[1][2] == 4) ? 0 : 1;
    res += (Grid[2][2] == 5) ? 0 : 1;
    res += (Grid[2][1] == 6) ? 0 : 1;
    res += (Grid[2][0] == 7) ? 0 : 1;
    res += (Grid[1][0] == 8) ? 0 : 1;
    return res;
}

int Puzzle_8::h2() {
    int res = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            switch (Grid[i][j]) {
            case 1:
                res += i + j; 
                break;
            case 2:
                res += abs(i) + abs(j-1); 
                break;
            case 3:
                res += abs(i) + abs(j-2); 
                break;
            case 4:
                res += abs(i-1) + abs(j-2); 
                break;
            case 5:
                res += abs(i-2) + abs(j-2); 
                break;
            case 6:
                res += abs(i-2) + abs(j-1); 
                break;
            case 7:
                res += abs(i-2) + abs(j); 
                break;
            case 8:
                res += abs(i-1) + abs(j); 
                break;
            case -1:
                res += abs(i-1) + abs(j-1); 
                break;
            default:
                break;
            }
        }
    }
    return res;
}

void Space_Search_h1(Puzzle_8 S, Puzzle_8 d) {
    int steps = 0;
    priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare> Open;
    bool solved = false;
    Open.push({S, S.h1()});

    map<vector<vector<int>>, int> Close;

    while (!Open.empty()) {
        steps++;
        auto res = Open.top();
        Open.pop();
        
        // res.printGrid();

        Close.emplace(res.first.Grid, 1);

        // Goal State
        if (res.first == d) {
            break;
        }

        // Else generate neighbouring states 
        res.first.Move_Gen(Open, Close);
    }

    if (Open.empty() && !solved) {
        cout << "Given 8 puzzle is not possible to solve" << "\n"; 
        return;
    } 

    cout << "No. of nodes encountered in search space: " << steps << "\n";
}

void Space_Search_h2(Puzzle_8 S, Puzzle_8 d) {
    int steps = 0;
    priority_queue<pair<Puzzle_8, int>, vector<pair<Puzzle_8, int>>, Compare> Open;
    bool solved = false;
    Open.push({S, S.h2()});

    map<vector<vector<int>>, int> Close;

    while (!Open.empty()) {
        steps++;
        auto res = Open.top();
        Open.pop();
        
        // res.printGrid();

        Close.emplace(res.first.Grid, 1);

        // Goal State
        if (res.first == d) {
            break;
        }

        // Else generate neighbouring states 
        res.first.Move_Gen2(Open, Close);
    }

    if (Open.empty() && !solved) {
        cout << "Given 8 puzzle is not possible to solve" << "\n"; 
        return;
    } 

    cout << "No. of nodes encountered in search space: " << steps << "\n";
}

int main() {
    Puzzle_8 S1({{6, -1, 2}, 
                {1, 8, 4}, 
                {7, 3, 5}});

    Puzzle_8 S2({{1, 2, 3}, 
                {8, 6, 4}, 
                {-1, 7, 5}});

    Puzzle_8 d({{1, 2, 3}, 
                {8, -1, 4}, 
                {7, 6, 5}});

    // Space_Search_h1(S1, d); // 1) 343 states encountered 2) 3 states 
    Space_Search_h2(S1, d); // 2) 186 states encountered 2) 3 states
    return 0;
}