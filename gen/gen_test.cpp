#include "../header/testlib.h"
#include "../header/edge.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#ifdef __GNUC__
    //fast log2 for int by using built_in GNU
    #define log2(x) (31 - __builtin_clz(x))
#else
    #include <math.h> 
#endif

#include "../LCA/On_O1.h"
int main(int argc, char* argv[])
{
    assert(argc > 3);

    registerGen(argc, argv, 1);
    int n = atoi(argv[2]), root = rnd.next(0, n - 1);
    
    std::vector<int> parent(n);
    if (strcmp(argv[1], "line") == 0)
        std::iota(parent.begin(), parent.end(), -1); //p[i] = i - 1
    else 
        for (int i = 1; i < n; ++i)
            parent[i] = rnd.next(0, i - 1);
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());
    std::vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        if (rnd.next(2))
            edges.push_back({perm[i], perm[parent[i]]});
        else 
            edges.push_back({perm[parent[i]], perm[i]});
    }
    //for faster cin cout, please don't use printf scanf
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    std::cout << n << ' ' << root << '\n';
    for (auto [u, v] : edges)
        std::cout << u << ' ' << v << '\n';

    int q = atoi(argv[3]);
    std::cout << q << '\n';
    LCA_n_1 tree(edges, root);
    for (int i = 0; i < q; ++i) {
        int u = rnd.next(n), v = rnd.next(n);
        std::cout << u <<  ' ' << v << ' ' << tree.LCA(u, v) << '\n';
    }
    
    return 0;
}