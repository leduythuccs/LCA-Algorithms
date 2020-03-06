/*
    Farach-Colton and Bender Algorithm

    space: O(n)
    prepare: O(n)
    query:     O(1)
    note: graph must be zero-based
    state: tested (https://judge.yosupo.jp/problem/lca)
    how to use: 
        - create & init: LCA_n_1 LCA(edges, root)
                + "edges" is a vector contants all edges of the tree
                edge can be directed or undirected
                struct Edge is defined in "edge.h"
                + "root" (optional, default is 0) is root of the tree
        - query: LCA.LCA(u, v)
                return LCA of node u and v
*/
struct LCA_n_1 {
    std::vector<std::vector<int> > adj;
    std::vector<int> level, time_in, euler_tour;
    int block_size, n_blocks;
    std::vector<std::vector<std::vector<int> > > small_rmq;
    std::vector<int> masks;
    std::vector<std::vector<int> > big_rmq;
    void DFS(int u, int p = -1) {
        time_in[u] = euler_tour.size();
        euler_tour.push_back(u);
        for (int v : adj[u]) if (v != p) {
            level[v] = level[u] + 1;
            DFS(v, u);
            euler_tour.push_back(u);
        }
    }
    inline int min_by_level(int a, int b) {
        if (level[euler_tour[a]] < level[euler_tour[b]]) return a;
        return b;
    }
    LCA_n_1(const std::vector<Edge> &edges, int root = 0) {
        int n = edges.size() + 1;
        adj.resize(n);
        time_in.resize(n);
        level.resize(n);
        int tour_length = 2 * n - 1;
        euler_tour.reserve(tour_length);
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        DFS(root);

        block_size = std::max(1, log2(tour_length) / 2);
        n_blocks = (tour_length - 1) / block_size + 1; //ceil(tour_length / block_size)
        small_rmq.resize(1 << (block_size - 1));
        masks.resize(n_blocks);
        //precompute mask, min for each block
        big_rmq.resize((int) log2(n_blocks) + 1, std::vector<int> (n_blocks, -1));
        for (int i = 0, pointer = 0, id_block = 0; i < tour_length; ++i, ++pointer) {
            if (pointer == block_size) 
                pointer = 0, ++id_block;

            if (big_rmq[0][id_block] == -1 || 
                min_by_level(big_rmq[0][id_block], i) == i)
                big_rmq[0][id_block] = i;
            //calc mask
            if (pointer > 0 && min_by_level(i - 1, i) == i - 1)
                masks[id_block] |= 1 << (pointer - 1);
        }
        //build sparse table 
        for (int j = 1; (1 << j) <= n_blocks; ++j)
            for (int i = 0; i + (1 << j) - 1 < n_blocks; ++i)
                big_rmq[j][i] = min_by_level(
                    big_rmq[j - 1][i],
                    big_rmq[j - 1][i + (1 << (j - 1))]
                );
        
        //build rmq table for each unique block
        for (int id_block = 0; id_block < n_blocks; ++id_block) {
            int mask = masks[id_block];
            if (!small_rmq[mask].empty()) 
                continue;
            int offset = id_block * block_size;
            int len = std::min(block_size, tour_length - offset);
            small_rmq[mask].resize(len, std::vector<int> (len));
            for (int i = 0; i < len; ++i) {
                small_rmq[mask][i][i] = i;
                for (int j = i + 1; j < len; ++j)
                    small_rmq[mask][i][j] = min_by_level(
                        small_rmq[mask][i][j - 1] + offset,
                        j + offset
                    ) - offset;
            }
        }
    }
    inline int small_rmq_query(int id_block, int l, int r) {
        return small_rmq[masks[id_block]][l][r] + id_block * block_size;
    }
    inline int big_rmq_query(int l, int r) {
        int k = log2(r - l + 1);
        return min_by_level(big_rmq[k][l], big_rmq[k][r - (1 << k) + 1]);
    }
    inline int LCA(int l, int r) {
        if (l == r) return l;
        std::tie(l, r) = std::minmax(time_in[l], time_in[r]);
        int left_block = l / block_size;
        int right_block = r / block_size;
        if (left_block == right_block)
            return euler_tour[small_rmq_query(left_block, l % block_size, r % block_size)];
        int lca = min_by_level(
            small_rmq_query(left_block, l % block_size, block_size - 1),
            small_rmq_query(right_block, 0, r % block_size)
        );
        if (left_block + 1 <= right_block - 1)
            lca = min_by_level(lca, big_rmq_query(left_block + 1, right_block - 1));
        return euler_tour[lca];
    }
};