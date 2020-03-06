#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm> 
#include <chrono>
#include <typeinfo>
#ifdef __GNUC__
    //fast log2 for int by using built_in GNU
    #define log2(x) (31 - __builtin_clz(x))
#else
    #include <math.h> 
#endif
#include "header/edge.h"
#include "LCA/Onlogn_Ologn.h"
#include "LCA/Onlogn_O1.h"
#include "LCA/On_O1.h"
template<class T>
void get_time(
    const std::vector<Edge> &edges, 
    int root,
    int q,
    const std::vector<int> &l,
    const std::vector<int> &r,
    const std::vector<int> &ans) {

    auto start_time = std::chrono::steady_clock::now();
    T tree(edges, root);
    auto current_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration<double, std::milli>(current_time - start_time).count() << ' ';
    start_time =  std::chrono::steady_clock::now();
    for (int i = 0; i < q; ++i) {
        int lca = tree.LCA(l[i], r[i]);
        if (lca != ans[i])  {
            std::cerr << typeid(T).name() << ": failed at " << i + 1 << "th query.\nExpected: " << ans[i]
            << "\nOutput: " << lca << '\n';
            exit(i + 1);
        }
    }
    current_time = std::chrono::steady_clock::now(); 
    std::cout << std::chrono::duration<double, std::milli>(current_time - start_time).count() << ' ';
}
int main() {
    //for faster cin cout, please don't use printf scanf
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); 
    int n, root;
    std::cin >> n >> root;
    std::vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges.push_back({u, v});
    }
    int q;
    std::cin >> q;
    std::vector<int> l(q), r(q), ans(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> l[i] >> r[i] >> ans[i];
    }
    get_time<LCA_nlogn_logn>(edges, root, q, l, r, ans);
    get_time<LCA_nlogn_1>(edges, root, q, l, r, ans);
    get_time<LCA_n_1>(edges, root, q, l, r, ans);
    return 0;
}