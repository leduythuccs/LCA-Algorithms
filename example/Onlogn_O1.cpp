#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#ifdef __GNUC__
    //fast log2 for int by using built_in GNU
    #define log2(x) (31 - __builtin_clz(x))
#else
    #include <math.h> 
#endif
#include "../header/edge.h"
#include "../header/Onlogn_O1.h"

int main() {
    int n, root;
    std::cout << "Please enter n (number nodes of the tree) and r (root): ";
    std::cin >> n >> root;
    std::vector<Edge> edges;
    std::cout << "Please enter " << n - 1 << " edges of the tree:\n";
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges.push_back({u, v});
    }
    LCA_nlogn_1 tree(edges, root);
    std::cout << "Please enter number of queries: ";
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::cout << "Query " << i << "th, (u, v) = ";
        int u, v;
        std::cin >> u >> v;
        std::cout << "LCA(" << u << ", " << v << ") = " << tree.LCA(u, v) << '\n';
    }
    return 0;
}