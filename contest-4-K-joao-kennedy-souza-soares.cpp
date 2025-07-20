#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

struct Ring {
    double x, y, r;
};

int dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    int count = 1;
    for (int v : adj[u]) {
        if (!visited[v]) {
            count += dfs(v, adj, visited);
        }
    }
    return count;
}

void solve(int n) {
    if (n == 0) {
        cout << "The largest component contains 0 rings." << endl;
        return;
    }

    vector<Ring> rings(n);
    for (int i = 0; i < n; ++i) {
        cin >> rings[i].x >> rings[i].y >> rings[i].r;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dx = rings[i].x - rings[j].x;
            double dy = rings[i].y - rings[j].y;
            double dist_sq = dx * dx + dy * dy;

            double r_sum = rings[i].r + rings[j].r;
            double r_sum_sq = r_sum * r_sum;

            double r_diff = abs(rings[i].r - rings[j].r);
            double r_diff_sq = r_diff * r_diff;

            if (dist_sq < r_sum_sq && dist_sq > r_diff_sq) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    int max_size = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int current_size = dfs(i, adj, visited);
            if (current_size > max_size) {
                max_size = current_size;
            }
        }
    }

    if (n > 0 && max_size == 0) {
        max_size = 1;
    }
    
    cout << "The largest component contains " << max_size << " ring";
    if (max_size != 1) {
        cout << "s";
    }
    cout << "." << endl;
}

int main() {
    int n;
    while (cin >> n && n != -1) {
        solve(n);
    }

    return 0;
}