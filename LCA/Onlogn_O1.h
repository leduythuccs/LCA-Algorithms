/*
    Using time DFS & RMQ to query faster

    space: O(nlogn)
    prepare: O(nlogn)
    query:     O(1)
    note: graph must be zero-based
    state: tested (https://judge.yosupo.jp/problem/lca)
    how to use: 
        - create & init: LCA_nlogn_1 LCA(edges, root)
                + "edges" is a vector contants all edges of the tree
                edge can be directed or undirected
                struct Edge is defined in "edge.h"
                + "root" (optional, default is 0) is root of the tree
        - query: LCA.LCA(u, v)
                return LCA of node u and v
*/
struct LCA_nlogn_1 {
    std::vector<std::vector<int> > adj, table;
    std::vector<int> time_in, path;
    std::vector<std::vector<int> > rmq;
    int current_time = 0;
    void DFS(int u, int p = -1) {
        time_in[u] = current_time++;
        for (int v : adj[u]) if (v != p) {
            path.push_back(u);
            DFS(v, u);
        }
    }
    inline int min_by_time(int a, int b) {
        if (time_in[a] < time_in[b]) return a;
        return b;
    }
    LCA_nlogn_1(const std::vector<Edge> &edges, int root = 0) {
        int n = edges.size() + 1;
        adj.resize(n);
        time_in.resize(n);
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        DFS(root);
        int m = path.size();
        rmq.resize((int) log2(m) + 1, std::vector<int> (m));
        rmq[0] = path;
        for (int j = 1; (1 << j) <= m; ++j)
            for (int i = 0; i + (1 << j) - 1 < m; ++i) {
                rmq[j][i] = min_by_time(
                    rmq[j - 1][i], 
                    rmq[j - 1][i + (1 << (j - 1))]
                );
            }
    }
    int LCA(int l, int r) {
        if (l == r) return l;
        std::tie(l, r) = std::minmax(time_in[l], time_in[r]);
        int k = log2(r - l);
        return min_by_time(rmq[k][l], rmq[k][r - (1 << k)]);
    }
};