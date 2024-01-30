#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <map>

using namespace std;

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

    void Move_Gen(queue<Puzzle_8>& Q, map<vector<vector<int>>, int>& visited);
    void Move_Gen(stack<Puzzle_8>& Q, map<vector<vector<int>>, int>& visited);

};

void Puzzle_8::Move_Gen(queue<Puzzle_8>& Q, map<vector<vector<int>>, int>& visited) {
    // Empty tile goes up
    Puzzle_8 res1 = up();
    auto temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes down
    res1 = down();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes left
    res1 = left();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes right
    res1 = right();
    temp = res1.Grid;
    if (res1.Grid != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }
}

void Puzzle_8::Move_Gen(stack<Puzzle_8>& Q, map<vector<vector<int>>, int>& visited) {
    // Empty tile goes up
    Puzzle_8 res1 = up();
    auto temp = res1.Grid;
    if (temp != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes down
    res1 = down();
    temp = res1.Grid;
    if (temp != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes left
    res1 = left();
    temp = res1.Grid;
    if (temp != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }

    // Empty tile goes right
    res1 = right();
    temp = res1.Grid;
    if (temp != false_state && (visited.find(temp) == visited.end())) {
        Q.push(res1);
    }
}

void Space_Search_BFS(Puzzle_8 S, Puzzle_8 d) {
    int steps = 0;
    queue<Puzzle_8> Open;
    bool solved = false;
    Open.push(S);

    map<vector<vector<int>>, int> Close;

    while (!Open.empty()) {
        steps++;
        auto res = Open.front();
        Open.pop();

        Close.emplace(res.Grid, 1);

        // Goal State
        if (res == d) {
            cout << "No. of nodes encountered in search space: " << steps << "\n";
            solved = true;
            break;
        }

        // Else generate neighbouring states 
        res.Move_Gen(Open, Close);
    }
    if (Open.empty() && !solved) {
        cout << "Given 8 puzzle is not possible to solve" << "\n"; 
        return;
    }

    
}

void Space_Search_DFS(Puzzle_8 S, Puzzle_8 d) {
    int steps = 0;
    stack<Puzzle_8> Open;
    Open.push(S);
    bool solved = false;

    map<vector<vector<int>>, int> Close;

    while (!Open.empty()) {
        steps++;
        auto res = Open.top();
        Open.pop();
        
        // res.printGrid();

        Close.emplace(res.Grid, 1);

        // Goal State
        if (res == d) {
            cout << "No. of nodes encountered in search space: " << steps << "\n";
            solved=true;
            break;
        }

        // Else generate neighbouring states 
        res.Move_Gen(Open, Close);
    }

    if (Open.empty() && !solved) {
        cout << "Given 8 puzzle is not possible to solve" << "\n"; 
        cout << steps << "\n"; 
        return;
    } 

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

    // BFS - 3349 (when goal state is farther to start state)
    Space_Search_BFS(S1, d);

    // DFS - 76551 (when goal state is farther to start state)
    // Space_Search_DFS(S1, d); 

    // BFS - 6 (when goal state is closer to start state)
    // Space_Search_BFS(S2, d);

    // DFS - 848 (when goal state is closer to start state)
    // Space_Search_DFS(S2, d); 

    return 0;
}



