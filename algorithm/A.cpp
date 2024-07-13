#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

int n, m;
vector<vector<int>> grid;
vector<pair<int, int>> friends;
vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int bfs(pair<int, int> start) {
    queue<tuple<int, int, int>> q; // (x, y, time)
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    q.push({start.first, start.second, 0});

    while (!q.empty)
    {
        visited
    }
    

    return fruits;
}

int main() {
    // 입력 받기
    cin >> n >> m;
    grid.resize(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    friends.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> friends[i].first >> friends[i].second;
        friends[i].first -= 1;  // 1-based 인덱스를 0-based 인덱스로 변환
        friends[i].second -= 1;
    }

    int max_fruits = 0;
    for (const auto& friend_pos : friends) {
        max_fruits += bfs(friend_pos);
    }

    cout << max_fruits << endl;

    return 0;
}
// 4 2
// 20 26 185 80
// 100 20 25 80
// 20 20 88 99
// 15 32 44 50
// 1 2
// 2 3