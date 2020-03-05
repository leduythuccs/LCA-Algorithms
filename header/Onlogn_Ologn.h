/*
    the most known algorithm about find LCA
    using squarse table
    space: O(nlogn)
    prepare: O(nlogn)
    query:     O(logn)
    note: graph must be zero-based
    state: tested (https://judge.yosupo.jp/problem/lca)
    how to use: 
        - create & init: LCA_nlog_logn LCA(edges, root)
                + "edges" is a vector contants all edges of the tree
                edge can be directed or undirected
                struct Edge is defined in "edge.h"
                + "root" (optional, default is 0) is root of the tree
        - query: LCA.LCA(u, v)
                return LCA of node u and v
*/
struct LCA_nlogn_logn {
    std::vector<std::vector<int> > adj, table;
    std::vector<int> level;
    LCA_nlogn_logn(const std::vector<Edge> &edges, int root = 0) {
        int n = edges.size() + 1;
        adj.resize(n);
        level.resize(n);
        table.resize((int)log2(n) + 1, std::vector<int> (n, -1));
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        DFS(root);
    }
    void DFS(int u, int p = -1) {
        for (int v : adj[u]) if (v != p) {
            level[v] = level[u] + 1;
            table[0][v] = u;
            for (int i = 1; (1 << i) <= level[v]; ++i)
                table[i][v] = table[i - 1][table[i - 1][v]];
            DFS(v, u);
        }
    }
    int LCA(int u, int v) {
        if (level[u] > level[v]) std::swap(u, v);
        int dist = level[v] - level[u];
        for (int i = 0; dist; ++i) 
            if (dist >> i & 1)
                v = table[i][v], dist ^= (1 << i);
        if (u == v) return u;
        for (int i = log2(level[u]); i >= 0; --i)
            if (table[i][u] ^ table[i][v]) // <=> table[i][u] != table[i][v]
                u = table[i][u], v = table[i][v];
        return table[0][u];
    }
};